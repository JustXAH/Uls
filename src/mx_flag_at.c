//
// Created by Dima Voichuck on 11/2/20.
//

#include "uls.h"

void mx_flag_at(char *path, t_l **flag_l) {
    char l[1024];
    mx_printchar('\n');
    if (listxattr(path, l, 1024, 1)) {
        ssize_t attr_2 = getxattr(path, l, 0, 1024, 0, 1);
        mx_printchar('\t');
        mx_printstr(l);
        mx_printchar('\t');
        mx_printstr("   ");
        mx_printint(attr_2);
        mx_printchar(' ');
    }
}
