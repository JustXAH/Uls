//
// Created by Igor Khanenko on 10/30/20.
//

#include "uls.h"

static void flag_F(t_output **opt, struct stat lstbuf,  int i) {
    if (S_ISFIFO(lstbuf.st_mode))
        (*opt)->symbol[i] = mx_strdup("|");
    else if (S_ISDIR(lstbuf.st_mode))
        (*opt)->symbol[i] = mx_strdup("/");
    else if (S_ISLNK(lstbuf.st_mode))
        (*opt)->symbol[i] = mx_strdup("@");
    else if (S_ISSOCK(lstbuf.st_mode))
        (*opt)->symbol[i] = mx_strdup("=");
    else if ((lstbuf.st_mode & S_IXUSR) == S_IXUSR)
        (*opt)->symbol[i] = mx_strdup("*");
    else if ((lstbuf.st_mode & S_IFWHT) == S_IFWHT)
        (*opt)->symbol[i] = mx_strdup("%");
    else
        (*opt)->symbol[i] = mx_strnew(0);
}

void mx_flag_p_and_F(t_flags *flag, t_output **opt) {
    struct stat lstbuf;
    char **buf_path = (*opt)->path != NULL ? (*opt)->path : (*opt)->filename;

    (*opt)->symbol = (char **)malloc(sizeof(char *) * (*opt)->file_num + 1);
    for (int k = 0; k <= (*opt)->file_num; k++)
        (*opt)->symbol[k] = NULL;

    for (int i = 0; i < (*opt)->file_num; i++) {
        lstbuf.st_mode = 0;
        lstat(buf_path[i], &lstbuf);
        if (flag->p == true) {
            if (S_ISDIR(lstbuf.st_mode))
                (*opt)->symbol[i] = mx_strdup("/");
            else
                (*opt)->symbol[i] = mx_strnew(0);
        }
        else if (flag->F == true)
            flag_F(opt, lstbuf, i);
    }
}
