//
// Created by Igor Khanenko on 10/6/20.
//
#include "uls.h"

void mx_output_multi_col(t_flags *flag, t_output *opt, int max_len, int col) {
    int amount = opt->file_num;
    int row = !(amount % col) ? amount / col : amount / col + 1;
    int tmp;

    for (int i = 0; i < row; mx_printchar(10)) {
        for (int j = i++; j < amount; j += row) {
            if (flag->G == true)
                mx_colorized_output(opt->filename[j], opt->path[j]);
            else
                mx_printstr(opt->filename[j]);
            if (flag->F == true || flag->p == true)
                mx_printstr(opt->symbol[j]);
            tmp = (max_len - mx_strlen(opt->filename[j])) / 8;
            (max_len - mx_strlen(opt->filename[j])) % 8 != 0 ? tmp++ : tmp;
            for (int k = 0; k++ < tmp; mx_printchar('\t'));
        }
    }
}
