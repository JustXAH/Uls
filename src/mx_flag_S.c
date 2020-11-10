//
// Created by Igor Khanenko on 10/28/20.
//

#include "uls.h"

static char **sort_content_by_size(char **dir_content, int dir_count,
                                      size_t *size) {
    char **tmp_content = dir_content;
    char *buffer = NULL;
    size_t tmp_size = 0;

    for (int i = 0; i < dir_count; i++) {
        for (int j = 0; j < dir_count - i - 1; j++) {
            if (size[j + 1] > size[j]) {
                tmp_size = size[j + 1];
                size[j + 1] = size[j];
                size[j] = tmp_size;
                buffer = tmp_content[j + 1];
                tmp_content[j + 1] = tmp_content[j];
                tmp_content[j] = buffer;
            }
        }
    }
    return tmp_content;
}

char **mx_flag_S(t_flags *flag, char **dir_content,
                 char *main_dir, int dir_count) {
    struct stat sb;
    size_t *size = (size_t *) malloc(sizeof(size_t) * dir_count);
    char **tmp_content = dir_content;
    char **dir_path = NULL;

    dir_path = mx_dir_path_creator(flag, dir_content, main_dir, dir_count);
    for (int i = 0; dir_path[i] != NULL; i++) {
        lstat(dir_path[i], &sb);
        size[i] = sb.st_size;
    }
    tmp_content = sort_content_by_size(tmp_content, dir_count, size);

    free(size);
    mx_del_strarr(&dir_path);
    return tmp_content;
}
