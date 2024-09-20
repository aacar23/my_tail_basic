#if !defined MY_TAIL_BASIC_H
#define MY_TAIL_BASIC_H

#include <stdio.h>
#include <sys/types.h>

void my_tail_basic(const char *file_name, ssize_t count, int print_head, void (*file_pos_mover)(FILE *file_handle, long offset, int origin));
#endif
