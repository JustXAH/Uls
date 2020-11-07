//
// Created by Dima Voichuck on 11/4/20.
//

#include "uls.h"

static void create_link(char *tmp, t_l **flag_l, int i) {
    char *link = NULL;
    char *str = NULL;
    char *vector = " -> ";

    link = mx_strnew(1024);
    readlink((*flag_l)->path[i], link, 1024);
    str = mx_strjoin(tmp, vector);
    (*flag_l)->name_2[i] = mx_strjoin(str, link);
    free(str);
    mx_strdel(&link);
}

static void flag_p(char **path, int i, t_l **flag_l) {
    if ((*flag_l)->mode[i][0] == 'd')
        (*flag_l)->name_2[i] = mx_strdup("/");
    else if ((*flag_l)->mode[i][0] == 'l')
        create_link(NULL, flag_l, i);
    else
        (*flag_l)->name_2[i] = mx_strdup("");
    (*flag_l)->name[i] = mx_strdup(path[i]);
}

static void flag_F(char **path, int i, t_l **flag_l) {
    if ((*flag_l)->mode[i][0] == 'p')
        (*flag_l)->name_2[i] = mx_strdup("|");
    else if ((*flag_l)->mode[i][0] == 'd')
        (*flag_l)->name_2[i] = mx_strdup("/");
    else if ((*flag_l)->mode[i][0] == 's')
        (*flag_l)->name_2[i] = mx_strdup( "=");
    else if ((*flag_l)->mode[i][0] == 'l')
        create_link("@", flag_l, i);
    else if ((*flag_l)->mode[i][3] == 'x')
        (*flag_l)->name_2[i] = mx_strdup("*");
    else
        (*flag_l)->name_2[i] = mx_strdup("");
    (*flag_l)->name[i] = mx_strdup(path[i]);
}

void mx_build_name(char **path, t_flags *flag, int i, t_l **flag_l) {
    if (flag->p) {
        flag_p(path, i, flag_l);
    }
    else if (flag->F) {
        flag_F(path, i, flag_l);
    }
    else {
        if ((*flag_l)->mode[i][0] == 'l')
            create_link(NULL, flag_l, i);
        else
            (*flag_l)->name_2[i] = mx_strdup("");
        (*flag_l)->name[i] = mx_strdup(path[i]);
    }
}
