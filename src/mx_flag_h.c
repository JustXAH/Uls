//
// Created by Dima Voichuck on 11/6/20.
//
#include "uls.h"

static void computation_2(double tmp_2, int *tmp, char **string_num, int size) {
    if (tmp_2 >= 0.5)
        (*tmp) += 1;
    *string_num = mx_itoa((int) size);
}

static char *computation(double size, long long size_2) {
    char *str = NULL;
    char *string_num = mx_strnew(3);
    int tmp = size;
    double tmp_2 = size - tmp;

    if (size >= 10)
        computation_2(tmp_2, &tmp, &string_num, size);
    else {
        tmp = 0;
        str = mx_itoa(size_2);
        for (tmp_2 = 0; tmp_2 < 2; tmp_2++) {
            if (tmp_2 == 1) {
                string_num[(int) tmp_2] = '.';
                tmp_2++;
            }
            string_num[(int) tmp_2] = str[tmp++];
        }
    }
    free(str);
    return string_num;
}


char *mx_flag_h(long long size, char *tmp, char *str) {
    if (size < 1000) {
        tmp = mx_itoa(size);
        str = mx_strjoin(tmp, "B");
    }
    else if (size >= 1000 && size < 1000000) {
        tmp = computation((double) size / 1000, size);
        str = mx_strjoin(tmp , "K");
    }
    else if (size >= 1000000 && size < 1000000000) {
        tmp = computation((double) size / 1000000, size);
        str = mx_strjoin(tmp , "M");
    }
    else if (size >= 1000000000 && size < 1000000000000) {
        tmp = computation((double) size / 1000000000, size);
        str = mx_strjoin(tmp , "G");
    }
    free(tmp);
    return str;
}
