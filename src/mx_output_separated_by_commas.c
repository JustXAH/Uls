//
// Created by Igor Khanenko on 10/28/20.
//

#include "uls.h"

static void change_in_length(t_flags *flag, t_output *opt, int *len, int i) {
    if ((flag->F || flag->p) && opt->symbol[i][0] != '\0') {
        mx_printstr(opt->symbol[i]);
        (*len) += mx_strlen(opt->filename[i]) + 1;
    }
    else
        (*len) += mx_strlen(opt->filename[i]);
}

static char get_delimiter(int *len, char *name, int win_col, bool last_obj) {
    char delimiter = ' ';

    if (last_obj == true && !isatty(1) && ((*len) + 2 + mx_strlen(name) < 80)) {
        return delimiter;
    } else if (!isatty(1) && *len + 4 + mx_s_strlen(name) > 79) {
        (*len) = 0;
        mx_printchar(' ');
        delimiter = '\n';
    } else if (!isatty(1) && *len + 2 + mx_s_strlen(name) < 80) {
        (*len) += 2;
        delimiter = ' ';
    } else if (*len + 2 + mx_strlen(name) < win_col - 1) {
        (*len) += 2;
        delimiter = ' ';
    } else {
        (*len) = 0;
        mx_printchar(' ');
        delimiter = '\n';
    }
    return delimiter;
}


void mx_output_separated_by_commas(t_flags *flag, t_output *opt) {
    struct winsize w;
    int len = 0;
    bool lst_obj = false;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (mx_strlen(opt->filename[0]) > 79)
        mx_printchar('\n');
    for (int i = 0; i < opt->file_num; i++) {
        if (i + 1 == opt->file_num)
            lst_obj = true;
        if (i != 0) {
            mx_printchar(',');
            mx_printchar(get_delimiter(&len, opt->filename[i],
                                       w.ws_col, lst_obj));
        }
        flag->G == true ? mx_colorized_output(opt->filename[i], opt->path[i])
                        : mx_printstr(opt->filename[i]);
        change_in_length(flag, opt, &len, i);
    }
    mx_printstr("\n");
}
