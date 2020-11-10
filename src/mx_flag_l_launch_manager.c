//
// Created by Igor Khanenko on 10/27/20.
//

#include "uls.h"

static void dir_path_output(char *argv_dir) {
        mx_printstr(argv_dir);
        mx_printstr(":\n");
}

static void help_flag_l_launch_manager(t_uls *uls, t_l *flag_l, t_flags *flag) {
    for (int i = 0; i < uls->count_dirs; i++) {
        flag_l->file_arg = false;
        if (flag->R == true && flag_l->many_fls == true)
            dir_path_output(uls->dirs[i]);
        mx_flag_l(&flag_l, flag, uls, uls->dirs[i]);
        if (i + 1 < uls->count_dirs)
            mx_printchar('\n');
        mx_flag_l_clean_memory(flag_l);
    }
}

void mx_flag_l_launch_manager(t_uls *uls, t_flags *flag) {
    t_l *flag_l = (t_l *) malloc(sizeof(t_l));

    flag_l->many_fls = uls->count_all_files > 1 ? true : false;
    if (uls->count_all_files > 0) {
        if (uls->count_files > 0) {
                flag_l->file_arg = true;
                mx_flag_l(&flag_l, flag, uls, NULL);
                mx_flag_l_clean_memory(flag_l);
            if (uls->count_all_files - uls->count_files > 0)
                mx_printchar('\n');
        }
        if (uls->count_dirs > 0)
            help_flag_l_launch_manager(uls, flag_l, flag);
    }
    else
        mx_flag_l(&flag_l, flag, uls, ".");
    mx_flag_l_clean_memory(flag_l);
    free(flag_l);
}
