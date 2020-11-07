//
// Created by Igor Khanenko on 10/27/20.
//

#include "uls.h"

void mx_flag_l_clean_memory(t_l *flag_l) {
    if (malloc_size(flag_l->name))
        mx_del_strarr(&flag_l->name);
    if (malloc_size(flag_l->name_2))
        mx_del_strarr(&flag_l->name_2);
    if (malloc_size(flag_l->time))
        mx_del_strarr(&flag_l->time);
    if (malloc_size(flag_l->user))
        mx_del_strarr(&flag_l->user);
    if (malloc_size(flag_l->mode))
        mx_del_strarr(&flag_l->mode);
    if (malloc_size(flag_l->gid))
        mx_del_strarr(&flag_l->gid);
    if (malloc_size(flag_l->size))
        mx_del_strarr(&flag_l->size);
    if (malloc_size(flag_l->link))
        mx_del_strarr(&flag_l->link);
    if (malloc_size(flag_l->path))
        mx_del_strarr(&flag_l->path);
    if (malloc_size(flag_l->file))
        mx_del_strarr(&flag_l->file);
}
