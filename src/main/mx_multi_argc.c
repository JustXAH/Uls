//
// Created by Igor Khanenko on 10/9/20.
//

#include "uls.h"

void mx_multi_argc(t_uls *uls, t_flags *flag) {
    //first, if we have files - print all files specified in the argv
    if (uls->count_files > 0) {
        mx_output_results(flag, uls->files, NULL, uls->count_files);
        uls->count_dirs > 0 ? mx_printchar(10) : mx_printstr("");
    }
    //second, if we have dirs - print contents of dirs specified in the argv
    if (uls->count_dirs > 0) {
        if (uls->count_dirs == 1 && !uls->count_files)
            mx_uls_basic(flag, uls->dirs[0]);
        else
            mx_output_dirs(flag, uls->dirs, uls->count_dirs);
    }
}
