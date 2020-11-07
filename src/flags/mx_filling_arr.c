//
// Created by Dima Voichuck on 11/5/20.
//

#include "uls.h"

static void help_filling_arr(char **str, char *main_path,
                             t_l **flag_l, int i) {
    if (!main_path)
        (*flag_l)->path[i] = mx_strdup(str[i]);
    else
        (*flag_l)->path[i] = mx_strjoin_uls(main_path, str[i]);
}

static void help_filling_arr_2(struct stat buff,
        struct passwd *user_info, t_l **flag_l, int i) {

    if (user_info)
            (*flag_l)->user[i] = mx_strdup(user_info->pw_name);
    else
        (*flag_l)->user[i] = mx_itoa(buff.st_uid);
}

static void help_filling_arr_3(struct stat buff,
        struct group *group_info, t_l **flag_l, int i) {

    if (group_info != NULL)
        (*flag_l)->gid[i] = mx_strdup(group_info->gr_name);
    else
        (*flag_l)->gid[i] = mx_itoa(buff.st_gid);
}

void mx_filling_arr(t_l **flag_l, char **str, t_flags *flag, char *main_path) {
    struct stat buff;
    struct passwd *user_info = NULL;
    struct group *group_info;

    for (int i = 0; str[i]; i++) {
        help_filling_arr(str, main_path, flag_l, i);
        lstat((*flag_l)->path[i], &buff);
        user_info = getpwuid(buff.st_uid);
        group_info = getgrgid(buff.st_gid);
        (*flag_l)->mode[i] = mx_for_flag_l(buff, (*flag_l)->path[i], flag_l);
        (*flag_l)->link[i] = mx_itoa(buff.st_nlink);
        (*flag_l)->size[i] = mx_flag_l_size(buff, flag, flag_l);
        help_filling_arr_2(buff, user_info, flag_l, i);
        help_filling_arr_3(buff, group_info, flag_l, i);
        (*flag_l)->bloks += buff.st_blocks;
        (*flag_l)->time[i] = mx_flag_time(buff, flag);
        mx_build_name(str, flag, i, flag_l);
    }
}
