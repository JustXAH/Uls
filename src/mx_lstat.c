//
// Created by Igor Khanenko on 10/18/20.
//

#include "uls.h"

char **mx_lstat(char **dir_content, int count, int *dirs_num) {
    struct stat lstbuf;
    char **dirs = (char **) malloc(sizeof(char *) * (count + 1));

    for (int j = 0; j <=count; dirs[j++] = NULL);

    for (int i = 0; dir_content[i] != NULL; i++) {
        lstbuf.st_mode = 0;
        lstat(dir_content[i], &lstbuf);
        if (S_ISDIR(lstbuf.st_mode)) {
           dirs[(*dirs_num)++] = mx_strdup(dir_content[i]);
        }
    }
    return dirs;
}
