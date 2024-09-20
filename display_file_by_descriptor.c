#include <string.h>
#include <errno.h>


#include "display_file_by_descriptor.h"
#include "error_exit.h"
#include "time_to_str.h"

void display_file_by_descriptor(FILE *file_handle)
{
    for (int c;(c = fgetc(file_handle)) != EOF;printf("%c", c))
        ;

    if (ferror(file_handle))
        error_exit("%s:%s:%s:%s\n", __func__, "fgetc", strerror(errno), time_to_str());
}
