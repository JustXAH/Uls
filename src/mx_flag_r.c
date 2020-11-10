//
// Created by Igor Khanenko on 10/18/20.
//

 #include "uls.h"

void mx_flag_r(char **dir_content, int size) {
    char **tmp_content = dir_content;
    char *tmp;
    int j = size - 1;

    for (int i = 0; i < j; i++) {
        tmp = tmp_content[i];
        tmp_content[i] = tmp_content[j];
        tmp_content[j--] = tmp;
    }
}
