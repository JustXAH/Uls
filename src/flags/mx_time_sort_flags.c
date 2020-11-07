//
// Created by Igor Khanenko on 10/28/20.
//

#include "uls.h"

static char **sort_content_by_time(char **dir_content, int dir_count,
                                      time_t *time) {
    char **tmp_content = dir_content;
    char *buffer = NULL;
    time_t tmp_time = 0;

    for (int i = 0; i < dir_count; i++) {
        for (int j = 0; j < dir_count - i - 1; j++) {
            if (time[j + 1] > time[j]) {
                tmp_time = time[j + 1];
                time[j + 1] = time[j];
                time[j] = tmp_time;
                buffer = tmp_content[j + 1];
                tmp_content[j + 1] = tmp_content[j];
                tmp_content[j] = buffer;
            }
        }
    }
    return tmp_content;
}

char **mx_time_sort_flags(t_flags *flag, char **dir_content,
                 char *main_dir, int dir_count) {
    struct stat sb;
    time_t *time = (time_t *) malloc(sizeof(time_t) * dir_count);
    char **tmp_content = dir_content;
    char **dir_path = NULL;

    dir_path = mx_dir_path_creator(flag, dir_content, main_dir, dir_count);
    for (int i = 0; dir_path[i] != NULL; i++) {
        lstat(dir_path[i], &sb);
        if (flag->u == true)
            time[i] = sb.st_atime;
        else if (flag->c == true)
            time[i] = sb.st_ctime;
        else
            time[i] = sb.st_mtime;
    }
    tmp_content = sort_content_by_time(tmp_content, dir_count, time);

    free(time);
    mx_del_strarr(&dir_path);
    return tmp_content;
}
