//
// Created by Dima Voichuck on 10/24/20.
//

#include "uls.h"

static char *flag_T (time_t time, t_flags *flag) {
    char *str;

    if (flag->T)
        str = mx_substr(ctime(&(time)), 4, 24);
    else
        str = mx_substr(ctime(&(time)), 4, 16);
    return str;
}

static void flag_for_time(struct stat buff, t_flags *flags, time_t *time) {
    if (flags->u)
        *time = buff.st_atime;
    else if (flags->c)
        *time = buff.st_ctime;
    else
        *time = buff.st_mtime;
}

char *mx_flag_time(struct stat buff, t_flags *flag) {
    time_t sec = time(NULL);
    time_t time = 0;
    char *sub;
    char *tmp;
    char *tmp_2;

    flag_for_time(buff, flag, &time);
    if (((sec - (time)) > 15778368) && !(flag->T)) {
        sub = mx_substr(ctime(&(time)), 4, 10);
        tmp = mx_strjoin(sub, "  ");
        free(sub);
        tmp_2 = mx_substr(ctime(&(time)), 20, 24);
        sub = mx_strjoin(tmp, tmp_2);
        free(tmp_2);
        free(tmp);
        return sub;
    }

    return flag_T(time, flag);
}
