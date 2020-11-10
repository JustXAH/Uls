//
// Created by Igor Khanenko on 10/26/20.
//

#include "uls.h"

static void clean_memory(t_uls *uls, char **dir_content, char **dirs_path) {
    mx_del_strarr(&dir_content);
    if (malloc_size(dirs_path))
        mx_del_strarr(&dirs_path);
    if (malloc_size(uls->dir_names))
        mx_del_strarr(&uls->dir_names);
}

static void path_output(char *argv_dir, int count_all_files,
                            int count_files, bool many_dirs) {
    if (count_all_files > 1) {
        if (count_files > 0 || many_dirs == false)
            mx_printstr("\n");
        mx_printstr(argv_dir);
        mx_printstr(":\n");
    }
}

static void flag_R_path_manager(t_uls *uls, t_flags *flag, char *main_dir,
                                bool many_dirs) {
    char **dir_content = NULL;
    char **dirs_path = NULL;
    int dir_count = 0;

    dir_content = mx_open_dir(flag, main_dir, &dir_count);
    path_output(main_dir, uls->count_all_files, uls->count_files, many_dirs);
    if (!mx_strcmp(main_dir, "/"))
        dirs_path = mx_dir_path_creator(flag, dir_content, NULL, dir_count);
    else
        dirs_path = mx_dir_path_creator(flag, dir_content, main_dir, dir_count);
    if ((flag->p == true || flag->F == true) && !mx_strcmp(main_dir, "."))
        mx_output_results(flag, dir_content, NULL, dir_count);
    else
        mx_output_results(flag, dir_content, dirs_path, dir_count);
    uls->dir_names = mx_lstat(dirs_path, dir_count, &uls->dirs_num);
    for (int i = 0; uls->dir_names[i] != NULL; i++)
        mx_flag_R_recursive(flag, uls->dir_names[i]);

    clean_memory(uls, dir_content, dirs_path);
}

void mx_flag_R_launch_manager(t_uls *uls, t_flags *flag) {
    bool many_dirs =  uls->count_dirs > 1 ? true : false;

    if (uls->count_all_files > 0) {
        if (uls->count_files > 0) {
            mx_output_results(flag, uls->files, NULL, uls->count_files);
        }
        for (int i = 0; i < uls->count_dirs; i++) {
            flag_R_path_manager(uls, flag, uls->dirs[i], many_dirs);
            uls->dirs_num = 0;
            if (many_dirs == true)
                many_dirs = false;
        }
    }
    else
        flag_R_path_manager(uls, flag, ".", many_dirs);
}
