#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "my_tail_basic.h"
#include "display_file_by_descriptor.h"
#include "error_exit.h"
#include "time_to_str.h"

void my_tail_basic(const char *file_name, ssize_t count, int print_head, void (*file_pos_mover)(FILE *file_handle, long offset, int origin))
{
    errno = 0;

    if (!count)
        return;



    FILE *file_handle = fopen(file_name, "r+");
    if (!file_handle){

        if (errno == ENOENT){
            printf("my_tail_basic: cannot open \'%s\' for reading: %s\n", file_name, strerror(errno));
            return;
        }

        error_exit("%s:%s:%s:%s", __func__, "fopen", strerror(errno), time_to_str());
    }

    if (print_head)
        printf("==> %s <==\n", file_name);

    (*file_pos_mover)(file_handle, count, count < 0 ? SEEK_END : SEEK_SET);

    display_file_by_descriptor(file_handle);

    fclose(file_handle);
}
