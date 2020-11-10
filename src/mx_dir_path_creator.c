//
// Created by Igor Khanenko on 10/27/20.
//

#include "uls.h"

char **mx_dir_path_creator(t_flags *flag, char **dir_content,
                           char *main_dir, int dir_count) {
    char **dir_path = NULL;
    int i = 0;
    int j = 0;

    dir_path = (char **)malloc(sizeof(char *) * dir_count + 1);
    for (i = 0; i <= dir_count; dir_path[i++] = NULL);
    for (i = 0; i < dir_count; i++) {
        if (dir_content[i] != NULL && dir_content[i + 1] != NULL) {
            if (flag->a && (mx_strcmp(dir_content[i], ".") == 0
                            && mx_strcmp(dir_content[i + 1], "..") == 0))
                i += 2;
            else if (flag->r && flag->a &&
                     (mx_strcmp(dir_content[i], "..") == 0
                      && mx_strcmp(dir_content[i + 1], ".") == 0))
                i += 2;
        }
        if (dir_content[i])
            dir_path[j++] = mx_strjoin_uls(main_dir, dir_content[i]);
    }
    return dir_path;
}
