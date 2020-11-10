//
// Created by Volodymyr Aivazovskyi on 10/6/20.
//
#include "uls.h"

void mx_output_in_one_line(t_flags *flag, t_output *opt, int max_len) {
    for (int i = 0; i < opt->file_num; i++) {
        if (flag->G == true)
            mx_colorized_output(opt->filename[i], opt->path[i]);
        else
            mx_printstr(opt->filename[i]);
        if (flag->F == true || flag->p == true)
            mx_printstr(opt->symbol[i]);
        for (int j = mx_strlen(opt->filename[i]); j < max_len; j++)
            mx_printchar(' ');
    }
    opt->file_num > 0 ? mx_printchar(10) : mx_printstr("");
}
