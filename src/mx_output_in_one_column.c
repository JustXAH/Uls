//
// Created by Igor Khanenko on 10/8/20.
//

#include "uls.h"

void mx_output_in_one_column(t_flags *flag, t_output *opt) {
    for (int i = 0; opt->filename[i] != NULL; i++) {
        if (flag->G == true)
            mx_colorized_output(opt->filename[i], opt->path[i]);

        else
            mx_printstr(opt->filename[i]);
        if (flag->F == true || flag->p == true)
            mx_printstr(opt->symbol[i]);
        mx_printchar('\n');
    }
}
