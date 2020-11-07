//
// Created by Igor Khanenko on 10/7/20.
//

#include "uls.h"

static char **path_creator(t_flags *flag, char **dir_content,
                           char *main_dir, int num_content)  {
    char **dirs_path = NULL;
    int i = 0;

    dirs_path = (char **)malloc(sizeof(char *) * num_content + 1);
    for (i = 0; i <= num_content; dirs_path[i++] = NULL);
    for (i = 0; i < num_content; i++) {
            dirs_path[i] = mx_strjoin_uls(main_dir, dir_content[i]);
    }
    return dirs_path;
}

void mx_uls_basic(t_flags *flag, char *open_dir) {
    char **dir_content = NULL;
    char **full_path = NULL;
    int count = 0;

    dir_content = mx_open_dir(flag, open_dir, &count);
    if (flag->p || flag->F || flag->G) {
        full_path = path_creator(flag, dir_content, open_dir, count);
        mx_output_results(flag, dir_content, full_path, count);
    }
    else
        mx_output_results(flag, dir_content, NULL, count);
    if (malloc_size(dir_content))
        mx_del_strarr(&dir_content);
    if (malloc_size(full_path))
        mx_del_strarr(&full_path);
}
