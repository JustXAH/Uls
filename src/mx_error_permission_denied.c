//
// Created by Igor Khanenko on 10/9/20.
//
#include "uls.h"

void mx_error_permission_denied(char *name_of_dir) {
    for (int i = mx_strlen(name_of_dir); i >= 0; i--) {
        if (name_of_dir[i] == '/') {
            name_of_dir += i + 1;
            break;
        }
    }
    errno = 1;
    mx_printerr("uls: ");
    mx_printerr(name_of_dir);
    mx_printerr(": Permission denied\n");
}
