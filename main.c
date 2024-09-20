#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "my_tail_basic.h"
#include "file_position_movers.h"
#include "disp_file.h"
#include "error_exit.h"
#include "time_to_str.h"

#define HELP_OPT (2)
#define VERSION_OPT (3)

int main(int argc, char **argv)
{
    int *disp_flag = &(int){0};
    int *print_flag = &(int){0};
    int *terminating_character_gotten = &(int){'\n'};

    ssize_t line_count = -10lu;
    ssize_t byte_count = 0lu;

    struct option options[] = {
        {.name = "bytes", .has_arg = required_argument, .flag = NULL, .val = 'c'},
        {.name = "lines", .has_arg = required_argument, .flag = NULL, .val = 'n'},
        {.name = "quiet", .has_arg = no_argument, .flag = print_flag, .val = 'q'},
        {.name = "silent", .has_arg = no_argument, .flag = print_flag, .val = 'q'},
        {.name = "zero-terminated", .has_arg = no_argument, .flag = terminating_character_gotten, .val = '\0'},
        {.name = "verbose", .has_arg = no_argument, .flag = print_flag, .val = 'v'},
        {.name = "help", .has_arg = no_argument, .flag = disp_flag, .val = HELP_OPT},
        {.name = "version", .has_arg = no_argument, .flag = disp_flag, .val = VERSION_OPT},
        {0, 0, 0, 0}
    };


    for (int c;(c = getopt_long(argc, argv, "c:n:qzv", options, NULL)) != -1;){

        if (c == '?')
            exit(EXIT_FAILURE);

        if (c == VERSION_OPT){
            printf("1.00v\n");
            return 0;
        }

        if (c == HELP_OPT){
            disp_file("help.txt");
            return 0;
        }

        *terminating_character_gotten = c == 'z' ? '\0' : *terminating_character_gotten;
        *print_flag = c == 'v' ? 'v' : c == 'q' ? 'q' : *print_flag;
        char *end = &(char){'\0'};

        if (c == 'n'){
            line_count = *optarg == '+' ? strtol(optarg, &end, 0) : -strtol(optarg, &end, 0);
            byte_count = 0;
        }

        else if (c == 'c'){
            line_count = 0;
            byte_count = *optarg == '+' ? strtol(optarg, &end, 0) : -strtol(optarg, &end, 0);
        }

        if (*end)
            error_exit("Please enter an integer argument for %c\n", c);
    }

    ssize_t count = line_count ? line_count : byte_count;

    void (*file_pos_mover)(FILE *file_handle, long offset, int origin) = byte_count ? &fseek_checked : *terminating_character_gotten == '\n' ? &move_n_lines : &move_n_nuls;

    int print_header = *print_flag == 'q' ? 0 : *print_flag == 'v' ? 1 : optind != argc - 1;

    for (int i = optind;i < argc;++i){
        my_tail_basic(*(argv + i), count, print_header, file_pos_mover);

        if (i != argc - 1)
            printf("\n");
    }

}
