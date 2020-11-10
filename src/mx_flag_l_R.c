//
// Created by Dima Voichuck on 11/7/20.
//

#include "uls.h"

static void free_memory(char **dir_names, char **dir_path) {
    if (malloc_size(dir_names))
        mx_del_strarr(&dir_names);
    if (malloc_size(dir_path))
        mx_del_strarr(&dir_path);
}

static void print_dir_name(char *dir_name) {
    mx_printstr("\n");
    mx_printstr(dir_name);
    mx_printstr(":\n");
}

void mx_flag_l_R(t_flags *flag, t_l **flag_l,
                 char **dir_content, char *main_dir) {
    char **dir_path = NULL;
    char **dir_names = NULL;
    int dir_count = 0;

    if (flag->R == true && (*flag_l)->file_arg == false) {
        if (!mx_strcmp(main_dir, "/"))
            dir_path = mx_dir_path_creator(flag, dir_content, NULL,
                                           (*flag_l)->len);
        else
            dir_path = mx_dir_path_creator(flag, dir_content, main_dir,
                                           (*flag_l)->len);
        dir_names = mx_lstat(dir_path, (*flag_l)->len, &dir_count);
        for (int i = 0; dir_names[i] != NULL; i++) {
            mx_flag_l_clean_memory((*flag_l));
            print_dir_name(dir_names[i]);
            mx_flag_l(flag_l, flag, NULL, dir_names[i]);
        }
    }
    free_memory(dir_names, dir_path);
}
