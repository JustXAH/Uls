//
// Created by Igor Khanenko on 10/28/20.
//

#include "uls.h"
#include <stdio.h>

static char get_delimiter(int *len, char *name, int win_col, bool last_obj) {
    char delimiter;

    if (last_obj == true && !isatty(1) && ((*len) + 2 + mx_strlen(name) < 80))
        return delimiter = ' ';
    if (!isatty(1) && ((*len) + 4 + mx_strlen(name) > 79)) {
        (*len) = 0;
        mx_printchar(' ');
        delimiter = '\n';
    }
    else if (*len + 2 + mx_strlen(name) < win_col - 1) {
        (*len) += 2;
        delimiter = ' ';
    }
    else {
        (*len) = 0;
        mx_printchar(' ');
        delimiter = '\n';
    }
    return delimiter;
}


void mx_output_separated_by_commas(t_flags *flag, t_output *opt) {
    struct winsize win;
    int len = 0;
    bool lst_obj = false;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    for (int i = 0; i < opt->file_num; i++) {
        if (i + 1 == opt->file_num)
            lst_obj = true;
        if (i != 0) {
            mx_printchar(',');
            mx_printchar(get_delimiter(&len, opt->filename[i],
                                       win.ws_col, lst_obj));
        }
        flag->G == true ? mx_colorized_output(opt->filename[i], opt->path[i])
                        : mx_printstr(opt->filename[i]);
        if ((flag->F == true || flag->p == true) && opt->symbol[i][0] != '\0') {
            mx_printstr(opt->symbol[i]);
            len += mx_strlen(opt->filename[i]) + 1;
        }
        else
            len += mx_strlen(opt->filename[i]);
    }
    mx_printstr("\n");
}
