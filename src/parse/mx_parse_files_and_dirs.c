//
// Created by Igor Khanenko on 10/8/20.
//
#include "uls.h"

static void check_file_type(t_uls **uls, char **dont_exist,
                                          int i, struct stat sb) {
    if (S_ISFIFO(sb.st_mode))
        (*uls)->files[(*uls)->count_files++] = mx_strdup((*uls)->all_files[i]);
    else if (S_ISCHR(sb.st_mode))
        (*uls)->files[(*uls)->count_files++] = mx_strdup((*uls)->all_files[i]);
    else if (S_ISDIR(sb.st_mode))
        (*uls)->dirs[(*uls)->count_dirs++] = mx_strdup((*uls)->all_files[i]);
    else if (S_ISBLK(sb.st_mode))
        (*uls)->files[(*uls)->count_files++] = mx_strdup((*uls)->all_files[i]);
    else if (S_ISREG(sb.st_mode))
        (*uls)->files[(*uls)->count_files++] = mx_strdup((*uls)->all_files[i]);
    else if (S_ISLNK(sb.st_mode))
        (*uls)->files[(*uls)->count_files++] = mx_strdup((*uls)->all_files[i]);
    else if (S_ISSOCK(sb.st_mode))
        (*uls)->files[(*uls)->count_files++] = mx_strdup((*uls)->all_files[i]);
    else {
        (*dont_exist) = mx_strdup((*uls)->all_files[i]);
        (*uls)->wrong++;
    }
}


static void save_file_and_dirs(t_uls **uls, int diff) {
    struct stat sb;
    char **dont_exist = (char **)malloc(sizeof(char *) * diff + 1);
    int i = 0;

    (*uls)->count_dirs = 0;
    (*uls)->count_files = 0;
    (*uls)->wrong = 0;
    for (i = 0; i <= diff; dont_exist[i++] = NULL);
    for (i = 0; (*uls)->all_files[i] != NULL; i++) {
        sb.st_mode = 0;
        stat((*uls)->all_files[i], &sb);
        check_file_type(uls, &dont_exist[(*uls)->wrong], i, sb);
    }
    if (((*uls)->flags && !mx_strchr((*uls)->flags, 'f'))
        || (*uls)->flags == NULL)
        mx_bubble_sort(dont_exist, (*uls)->wrong);
    for (i = 0; i < (*uls)->wrong; i++)
        mx_error_no_file_or_dir(dont_exist[i]);
    mx_del_strarr(&dont_exist);
}


void mx_parse_files_and_dirs(t_uls **uls, char **argv, int argc, int count) {
    int diff = argc - count;
    (*uls)->count_all_files = diff;

    //allocation of memory for arrays to save the names of all types files
    (*uls)->all_files = (char **) malloc(sizeof(char *) * diff + 1);
    for (int i = 0; i <= diff; (*uls)->all_files[i++] = NULL);

    //save all types file names to an array
    for (int i = 0; count < argc; i++) {
        (*uls)->all_files[i] = mx_strdup(argv[count]);
        count++;
    }
    //allocation of memory for arrays to save the names of all files and dirs
    (*uls)->dirs = (char **) malloc(sizeof(char *) * diff + 1);
    (*uls)->files = (char **) malloc(sizeof(char *) * diff + 1);
    for (int i = 0; i <= diff; i++) {
        (*uls)->dirs[i] = NULL;
        (*uls)->files[i] = NULL;
    }
    save_file_and_dirs(uls, diff);
}
