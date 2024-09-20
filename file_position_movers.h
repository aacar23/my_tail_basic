#if !defined FILE_POSITION_MOVERS_H
#define FILE_POSITION_MOVERS_H

#include <stdio.h>

void fseek_checked(FILE *file_handle, long offset, int origin);
void move_n_nuls(FILE *file_handle, long offset, int origin);
void move_n_lines(FILE *file_handle, long offset, int origin);

#endif
