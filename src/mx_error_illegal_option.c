//
// Created by Igor Khanenko on 10/6/20.
//
#include "uls.h"

void mx_error_illegal_option(char c) {
    mx_printerr("uls: illegal option -- ");
    mx_printchar_error(c);
    mx_printerr("\nusage: uls [-");
    mx_printerr(FLAGS);
    mx_printerr("] [file ...]\n");
    errno = 1;
}
