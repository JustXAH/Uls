//
// Created by Igor Khanenko on 10/18/20.
//

#include "uls.h"

static char **get_dir_content(t_flags *flag, DIR *fd, char *main_dir,
                              const int *count) {
    struct dirent *dir;
    char **dir_content = (char **) malloc(sizeof(char *) * ((*count) + 1));

    for (int k = 0; k < (*count) + 1; dir_content[k++] = NULL);
    fd = opendir(main_dir);
    // takings names of files and dirs in the dir
    for (int i = 0; (dir = readdir(fd));) {
        if (flag->f == true || flag->a == true)
            dir_content[i++] = mx_strdup(dir->d_name);
        else if (flag->A == true) {
            if (mx_strcmp(dir->d_name, ".") != 0
                && mx_strcmp(dir->d_name, "..") != 0)
                dir_content[i++] = mx_strdup(dir->d_name);
        } else {
            if (*dir->d_name != '.')
                dir_content[i++] = mx_strdup(dir->d_name);
        }
    }
    closedir(fd);
    return dir_content;
}

static void counting_dir_content(t_flags *flag, DIR *fd, int *count) {
    struct dirent *dir;

    for ((*count) = 0; (dir = readdir(fd)) != NULL;) {
        if (flag->f == true || flag->a == true)
            (*count)++;
        else if (flag->A == true) {
            if (mx_strcmp(dir->d_name, ".") != 0
                && mx_strcmp(dir->d_name, "..") != 0)
                (*count)++;
        } else
            *dir->d_name != '.' ? (*count)++ : (*count);
    }
    closedir(fd);
}

char **mx_open_dir(t_flags *flag, char *main_dir, int *count) {
    DIR *fd = opendir(main_dir);
    char **dir_cont = NULL;

    if (!(int) fd)
        mx_error_permission_denied(main_dir);
    else {
        counting_dir_content(flag, fd, count);
        if ((*count) > 0)
            dir_cont = get_dir_content(flag, fd, main_dir, count);
    }
    if (flag->f == false && dir_cont != NULL) {
        mx_bubble_sort(dir_cont, *count);
        if (flag->t == true)
            dir_cont = mx_time_sort_flags(flag, dir_cont, main_dir, *count);
        else if (flag->S == true)
            dir_cont = mx_flag_S(flag, dir_cont, main_dir, *count);
        if (flag->r == true)
            mx_flag_r(dir_cont, *count);
    }
    return dir_cont;
}
