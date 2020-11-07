//
// Created by Igor Khanenko on 10/8/20.
//
#include "uls.h"

void mx_output_dirs(t_flags *flag, char **objects, int num_in_dir) {
    for (int i = 0; i < num_in_dir; ) {
        mx_printstr(objects[i]);
        mx_printstr(":\n");
        mx_uls_basic(flag, objects[i]);
        ++i != num_in_dir ? mx_printchar(10) : mx_printstr("");
    }
}
