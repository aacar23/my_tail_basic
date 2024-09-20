#include <string.h>
#include <errno.h>

#include "file_position_movers.h"
#include "error_exit.h"
#include "time_to_str.h"

static int get_character_from_file_and_go_back(FILE *file_handle)
{

    long previous_position = ftell(file_handle);

    int c;

    if (fseek(file_handle, -1l, SEEK_CUR))
        return -1;


    if ((c = fgetc(file_handle)) == EOF)
        return -1;

    if (!previous_position)
        return -1;

    if (fseek(file_handle, -1l, SEEK_CUR))
        return -1;


    return c;
}

static void move_n_chars(FILE *file_handle, long offset, int origin, int ch)
{
    errno = 0;

    static int (*getter)(FILE *file_handle) = &fgetc;

    if (offset < 0){
       getter = &get_character_from_file_and_go_back;
       offset = -offset;
    }

    if (fseek(file_handle, origin == SEEK_END ? -1 : 0, origin))
        goto FAIL;

    if (!offset)
        return;

    int c;
    for (long i = 0l;ftell(file_handle) > 0 && (c = (*getter)(file_handle)) != EOF && (i += c == ch) < offset;)
        ;

    if (errno)
        goto FAIL;

    if (ftell(file_handle) > 0 && fgetc(file_handle) != '\n')
        if (fseek(file_handle, -1, SEEK_CUR))
            goto FAIL;

    if (ferror(file_handle))
        goto FAIL;


    return;

    FAIL:
    error_exit("%s:%s:%s", __func__, strerror(errno), time_to_str());
}

void fseek_checked(FILE *file_handle, long offset, int origin)
{
    if (fseek(file_handle, offset, origin))
        error_exit("%s:%s:%s:%s", __func__, "fseek", strerror(errno), time_to_str());
}

void move_n_nuls(FILE *file_handle, long offset, int origin)
{
    move_n_chars(file_handle, offset, origin, '\0');
}

void move_n_lines(FILE *file_handle, long offset, int origin)
{
    move_n_chars(file_handle, offset, origin, '\n');
}
