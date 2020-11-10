//
// Created by Dima Voichuck on 10/18/20.
//

#include "uls.h"

static void printspace(t_l **flag_l, t_size_for_l **size_for_l,
                        int key, int f) {
    int i;
    int j;
    if (key == 1) {
        j = (*size_for_l)->mode_len - mx_strlen((*flag_l)->mode[f]);
        for (i = 0; i < j; i++)
            mx_printchar(' ');
    }
    if (key == 2) {
        j = (*size_for_l)->link_size - mx_strlen((*flag_l)->link[f]);
        for (i = 0; i < j + 1; i++)
            mx_printchar(' ');
    }
    if (key == 3) {
        j = (*size_for_l)->user_len - mx_strlen((*flag_l)->user[f]);
        for (i = 0; i < j; i++)
            mx_printchar(' ');
    }

}

static void printspace_2(t_l **flag_l, t_size_for_l **size_for_l,
                         int key, int f) {
    int i;
    int j;
    if (key == 4) {
        j = (*size_for_l)->gid_len - mx_strlen((*flag_l)->gid[f]);
        for (i = 0; i < j; i++)
            mx_printchar(' ');
    }
    if (key == 5) {
        j = (*size_for_l)->size_len - mx_strlen((*flag_l)->size[f]);
        for (i = 0; i < j; i++)
            mx_printchar(' ');
    }
}

static void output_flag_l(t_l **flag_l, t_size_for_l **size_for_l, int i) {
    mx_printstr((*flag_l)->mode[i]);
    printspace(flag_l, size_for_l, 1, i);
    printspace(flag_l, size_for_l, 2, i);
    mx_printstr((*flag_l)->link[i]);
    mx_printchar(' ');
    mx_printstr((*flag_l)->user[i]);
    mx_printchar(' ');
    printspace(flag_l, size_for_l, 3, i);
    mx_printchar(' ');
    mx_printstr((*flag_l)->gid[i]);
    printspace_2(flag_l, size_for_l, 4, i);
    mx_printchar(' ');
    printspace_2(flag_l, size_for_l, 5, i);
    mx_printchar(' ');
}

void mx_output_flag_l(t_l **flag_l, t_size_for_l **size_for_l, t_flags *flag) {
    for (int i = 0; (*flag_l)->name[i]; i++) {
        output_flag_l(flag_l, size_for_l, i);
        if ((*flag_l)->size[i][5] == 'x')
            mx_printchar(' ');
        mx_printstr((*flag_l)->size[i]);
        mx_printchar(' ');
        mx_printstr((*flag_l)->time[i]);
        mx_printchar(' ');
        if (flag->G)
            mx_colorized_output((*flag_l)->name[i], (*flag_l)->path[i]);
        else
            mx_printstr((*flag_l)->name[i]);
        if ((*flag_l)->name_2[i])
            mx_printstr((*flag_l)->name_2[i]);
        if (flag->at && (*flag_l)->mode[i][10] == '@')
            mx_flag_at((*flag_l)->path[i], flag_l);
        mx_printchar('\n');
    }
}
