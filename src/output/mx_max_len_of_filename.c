//
// Created by Igor Khanenko on 10/6/20.
//
#include "uls.h"

int mx_max_len_of_filename(char **objects, int num_in_dir) {
    int max_len = mx_s_strlen(objects[0]);

    for (int i = 1; i < num_in_dir; i++) {
        mx_strlen(objects[i]) > max_len ? max_len = mx_strlen(objects[i]) : i;
    }

    return max_len = max_len - max_len % 8 + 8;
}
