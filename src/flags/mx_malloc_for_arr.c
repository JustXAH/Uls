//
// Created by Dima Voichuck on 11/5/20.
//
#include "uls.h"

static void filling_with_NULL(t_l **flag_l) {
    for (int i = 0; i <= (*flag_l)->len; i++) {
        (*flag_l)->size[i] = NULL;
        (*flag_l)->gid[i] = NULL;
        (*flag_l)->mode[i] = NULL;
        (*flag_l)->time[i] = NULL;
        (*flag_l)->name_2[i] = NULL;
        (*flag_l)->name[i] = NULL;
        (*flag_l)->user[i] = NULL;
        (*flag_l)->link[i] = NULL;
        (*flag_l)->path[i] = NULL;
        (*flag_l)->file[i] = NULL;
    }
    (*flag_l)->bloks = 0;
}

void mx_malloc_for_arr(t_l **flag_l) {
    (*flag_l)->file = (char **) malloc(sizeof(char*) * (*flag_l)->len + 1);
    (*flag_l)->link = (char **) malloc(sizeof(char *) * (*flag_l)->len + 1);
    (*flag_l)->size = (char **) malloc(sizeof(char *) * (*flag_l)->len + 1);
    (*flag_l)->gid = (char **) malloc(sizeof(char *) * (*flag_l)->len + 1);
    (*flag_l)->mode = (char **) malloc(sizeof(char *) * (*flag_l)->len + 1);
    (*flag_l)->time = (char **) malloc(sizeof(char *) * (*flag_l)->len + 1);
    (*flag_l)->name = (char **) malloc(sizeof(char *) * (*flag_l)->len + 1);
    (*flag_l)->name_2 = (char **) malloc(sizeof(char *) * (*flag_l)->len + 1);
    (*flag_l)->user = (char **) malloc(sizeof(char *) * (*flag_l)->len + 1);
    (*flag_l)->path = (char **) malloc(sizeof(char *) * (*flag_l)->len + 1);
    filling_with_NULL(flag_l);
}
