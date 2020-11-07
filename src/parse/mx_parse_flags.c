//
// Created by Igor Khanenko on 10/5/20.
//

#include "uls.h"

static void wrong_flag_check_and_output(t_uls **uls, int j, char flag_name) {
    if (j == FLAGS_NUM) {
        mx_error_illegal_option(flag_name);
        free((*uls)->flags);
        free((*uls));
        exit(errno);
    }
}

static void check_flags(t_uls **uls, char *argv, int *count) {
    int k = 1;
    int len_argv = mx_strlen(argv);

    for (int j = 0; j <= FLAGS_NUM && k != len_argv; j++) {
       wrong_flag_check_and_output(uls, j, argv[k]);
        if (len_argv > 2) {
            if (argv[k] == FLAGS[j]) {
                (*uls)->flags = mx_realloc((*uls)->flags, (*count) + 1);
                (*uls)->flags[(*count)++] = argv[k++];
                (*uls)->flags[(*count)] = '\0';
                j = -1;
            }
        } else
            if (argv[1] == FLAGS[j]) {
                (*uls)->flags = mx_realloc((*uls)->flags, (*count) + 1);
                (*uls)->flags[(*count)++] = argv[1];
                (*uls)->flags[(*count)] = '\0';
                break;
            }
    }
}

void mx_parse_flags(t_uls **uls, char **argv, int argc, int *count_args) {
    int count = 0;
    int i = 1;
    (*uls)->count_flags = 0;

    for (i = 1; i < argc && argv[i][0] == '-'; i++) {
        if (!mx_strcmp(argv[i], "--")) {
            (*count_args) = i + 1;
            return;
        }
        if (argv[i][0] == '-')
            check_flags(uls, argv[i], &count);

        else if (argv[i][0] != '-')
            break;
    }
    (*uls)->count_flags = count;
    (*count_args) = i;
}
