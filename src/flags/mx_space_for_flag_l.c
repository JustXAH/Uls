//
// Created by Dima Voichuck on 10/22/20.
//

#include "uls.h"

static void initialization(t_size_for_l **size_for_l) {
    (*size_for_l)->name_len = 0;
    (*size_for_l)->size_len = 0;
    (*size_for_l)->time_len = 0;
    (*size_for_l)->gid_len = 0;
    (*size_for_l)->link_size = 0;
    (*size_for_l)->mode_len = 0;
    (*size_for_l)->user_len = 0;
}

void mx_space_for_flag_l(t_l **flag_l, t_size_for_l **size_for_l) {
    initialization(size_for_l);
    for (int i = 0; (*flag_l)->name[i]; i++) {
        if (mx_strlen((*flag_l)->name[i]) > (*size_for_l)->name_len)
            (*size_for_l)->name_len = mx_strlen((*flag_l)->name[i]);
        if ((*flag_l)->triger_all)
            (*size_for_l)->size_len = 8;
        else if (mx_strlen((*flag_l)->size[i]) > (*size_for_l)->size_len)
            (*size_for_l)->size_len = mx_strlen((*flag_l)->size[i]);
        if (mx_strlen((*flag_l)->time[i]) > (*size_for_l)->time_len)
            (*size_for_l)->time_len = mx_strlen((*flag_l)->time[i]);
        if (mx_strlen((*flag_l)->gid[i]) > (*size_for_l)->gid_len)
            (*size_for_l)->gid_len = mx_strlen((*flag_l)->gid[i]);
        if (mx_strlen((*flag_l)->link[i]) > (*size_for_l)->link_size)
            (*size_for_l)->link_size = mx_strlen((*flag_l)->link[i]);
        if (mx_strlen((*flag_l)->mode[i]) > (*size_for_l)->mode_len)
            (*size_for_l)->mode_len = mx_strlen((*flag_l)->mode[i]);
        if (mx_strlen((*flag_l)->user[i]) > (*size_for_l)->user_len)
            (*size_for_l)->user_len = mx_strlen((*flag_l)->user[i]);
    }
}
