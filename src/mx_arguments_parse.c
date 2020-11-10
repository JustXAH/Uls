//
// Created by Igor Khanenko on 10/5/20.
//

#include "uls.h"

void mx_arguments_parse(t_uls **uls, t_flags *flag, char **argv, int argc) {
    int count = 1;
    (*uls)->flags = NULL;
    (*uls)->all_files = NULL;
    (*uls)->dirs = NULL;
    (*uls)->files = NULL;
    (*uls)->flag_l = false;

    // Check/save flags to an array or output an error if an incorrect flag is
    mx_parse_flags(uls, argv, argc, &count);

    if (argc > 1 && (*uls)->flags != NULL) {
        mx_flags_manager(*uls, flag);
    }
    //Check file types, save files and dirs to the array and output errors
    if (flag->l == true)
        (*uls)->flag_l = true;
    mx_parse_files_and_dirs(uls, argv, argc, count);
}
