//
// Created by Dima Voichuck on 10/8/20.
//

#include "uls.h"

static void free_memory(char **dir_content, t_size_for_l *size_for_l) {
    if (malloc_size(dir_content))
        mx_del_strarr(&dir_content);
    if (malloc_size(size_for_l))
        free(size_for_l);

}

static void help_flag_l(char **dir_content, char *main_dir, t_l **flag_l, t_flags *flag) {
    if (dir_content != NULL) {
        mx_malloc_for_arr(flag_l);
        if (mx_strcmp(main_dir, ".") != 0)
            mx_filling_arr(flag_l, dir_content, flag, main_dir);
        else
            mx_filling_arr(flag_l, dir_content, flag, NULL);
    }
}

static void help_2_flag_l(t_l **flag_l, t_flags *flag, t_uls *uls) {
    if ((*flag_l)->file_arg == true) {
        (*flag_l)->len = uls->count_files;
        mx_malloc_for_arr(flag_l);
        mx_filling_arr(flag_l, uls->files, flag, NULL);
    }
}

void mx_flag_l(t_l **flag_l, t_flags *flag, t_uls *uls, char *main_dir) {
    t_size_for_l *size_for_l = (t_size_for_l *)malloc(sizeof(t_size_for_l));
    char **dir_content = NULL;

    (*flag_l)->triger_all = false;
    (*flag_l)->len = 0;
    if ((*flag_l)->file_arg == false) {
        dir_content = mx_open_dir(flag, main_dir, &(*flag_l)->len);
        help_flag_l(dir_content, main_dir, flag_l, flag);
    }
    mx_print_dir_name_flag_l(flag_l, flag, main_dir, dir_content);
    help_2_flag_l(flag_l, flag, uls);
    if (((*flag_l)->file_arg == true && dir_content == NULL) ||
        ((*flag_l)->file_arg == false && dir_content != NULL)) {
        mx_space_for_flag_l(flag_l, &size_for_l);
        mx_output_flag_l(flag_l, &size_for_l, flag);
    }
    mx_flag_l_R(flag, flag_l, dir_content, main_dir);
    free_memory(dir_content, size_for_l);
}
