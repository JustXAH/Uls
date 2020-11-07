//
// Created by Igor Khanenko on 10/19/20.
//

#include "uls.h"

static char **dir_path_creator(t_flags *flag, char *main_dir,
                               int *content_amount) {
    char **dir_content = NULL;
    char **dirs_path = NULL;
    int i = 0;
    int j = 0;

    dir_content = mx_open_dir(flag, main_dir, content_amount);
    dirs_path = (char **)malloc(sizeof(char *) * (*content_amount) + 1);
    for (i = 0; i <= (*content_amount); dirs_path[i++] = NULL);
    for (i = 0; i < (*content_amount); i++) {
        if (flag->a == true && (mx_strcmp(dir_content[i], ".") == 0
                                && mx_strcmp(dir_content[i + 1], "..") == 0))
            i += 2;
        if (dir_content[i])
            dirs_path[j++] = mx_strjoin_uls(main_dir, dir_content[i]);
    }
    mx_output_results(flag, dir_content, dirs_path, (*content_amount));

    if (malloc_size(dir_content))
        mx_del_strarr(&dir_content);
    return dirs_path;
}


void mx_flag_R_recursive(t_flags *flag, char *main_dir) {
    char **dir_names = NULL;
    char **dirs_path = NULL;
    int dir_count = 0;
    int content_amount = 0;

    if (main_dir == NULL)
        return;
    mx_printchar('\n');
    mx_printstr(main_dir);
    mx_printstr(":\n");
    dirs_path = dir_path_creator(flag, main_dir, &content_amount);
    dir_names = mx_lstat(dirs_path, content_amount, &dir_count);
    if (dir_count > 0) {
        for (int i = 0; i < dir_count; i++)
            mx_flag_R_recursive(flag, dir_names[i]);
    }
    if (malloc_size(dirs_path))
        mx_del_strarr(&dirs_path);
    if (malloc_size(dir_names))
        mx_del_strarr(&dir_names);
}
