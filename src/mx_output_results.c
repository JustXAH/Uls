//
// Created by Igor Khanenko on 10/8/20.
//

#include "uls.h"

void mx_output_results(t_flags *flag, char **objects,char **full_path,
                       int num_in_dir) {
    t_output *opt = (t_output *)malloc(sizeof(t_output));

    opt->filename = objects;
    opt->path = full_path != NULL ? full_path : objects;
    opt->file_num = num_in_dir;
    if (opt->filename) {
        if (flag->F == true || flag->p == true)
            mx_flag_p_and_F(flag, &opt);

        if ((!isatty(1) && flag->m == false) || flag->One == true)
            mx_output_in_one_column(flag, opt);
        else if (flag->m == true || (!isatty(1) && flag->One == false))
            mx_output_separated_by_commas(flag, opt);
        else
            mx_output_by_window_size(flag, opt);
    }

    if (malloc_size(opt->symbol))
        mx_del_strarr(&opt->symbol);
    free(opt);
}
