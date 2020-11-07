//
// Created by Igor Khanenko on 10/6/20.
//

 #include "uls.h"

void mx_output_by_window_size(t_flags *flag, t_output *opt) {
    struct winsize w;
    int max_len = mx_max_len_of_filename(opt->filename, opt->file_num);

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    if (w.ws_col < max_len)
        mx_output_in_one_column(flag, opt);
    else if (w.ws_col >= max_len * opt->file_num)
        mx_output_in_one_line(flag, opt, max_len);
    else
        mx_output_multi_col(flag, opt, max_len, w.ws_col / max_len);
}
