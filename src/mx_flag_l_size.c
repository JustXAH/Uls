//
// Created by Dima Voichuck on 10/24/20.
//

#include "uls.h"

static char *minor_build(unsigned int m) {
    char *tmp_3;
    char *tmp;
    char *tmp_2;
    int j;

    tmp = mx_nbr_to_hex(m);
    j = 8 - mx_strlen(tmp);
    tmp_2 = mx_strndup("0x00000000", j + 2);
    tmp_3 = mx_strjoin(tmp_2, tmp);
    free(tmp);
    free(tmp_2);

    return tmp_3;
}

static char *minor_build_2(unsigned int m) {
    char *tmp_3;
    char *tmp_2;
    int j;

    tmp_3 = mx_strnew(4);
    tmp_2 = mx_itoa(m);
    j = mx_strlen(tmp_2);
    m = j - 1;
    for (int i = 0; i < 3; i++)
        tmp_3[i] = ' ';
    for (int i = 2; i >= 3 - j; i--) {
        tmp_3[i] = tmp_2[m];
        m--;
    }
    free(tmp_2);
    return tmp_3;
}

static char *mm_l(struct stat buff) {
    char *str = NULL;
    char *tmp = NULL;
    char *tmp_2 = NULL;
    char *tmp_3 = NULL;
    unsigned int m;

    m = major(buff.st_rdev);
    str = mx_itoa(m);
    m = minor(buff.st_rdev);
    tmp = mx_strjoin(str, ",");
    free(str);
    str = mx_strjoin(tmp, " ");
    free(tmp);
    tmp_3 = m > 255 ? minor_build(m) : minor_build_2(m);
    tmp_2 = mx_strjoin(str, tmp_3);
    free(str);
    free(tmp_3);
    return tmp_2;
}

char *mx_flag_l_size(struct stat buff, t_flags *flag, t_l **flag_l) {
    char *str = NULL;
    char *tmp = NULL;
    long long size = buff.st_size;

    if ((*flag_l)->triger == 1) {
        (*flag_l)->triger_all = true;
        return mm_l(buff);
    }
    else if (flag->h == true) {
        return mx_flag_h(size, tmp, str);
    }
    else {
        str = mx_itoa(size);
        return str;
    }
}
