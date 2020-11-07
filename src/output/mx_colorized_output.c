//
// Created by Igor Khanenko on 11/6/20.
//

#include "uls.h"

static void print_dir(struct stat sb) {
    if ((sb.st_mode & S_IWOTH) == S_IWOTH
        && (sb.st_mode & S_ISVTX) == S_ISVTX)
        mx_printstr(DIR_T);
    else if ((sb.st_mode & S_IWOTH) == S_IWOTH
             && (sb.st_mode & S_IXOTH) == S_IXOTH)
        mx_printstr(DIR_X);
    else
        mx_printstr(BLU);
}

static void print_reg_file(struct stat sb) {
    if ((sb.st_mode & S_ISUID) == S_ISUID)
        mx_printstr(BLK_F_RED_B );
    else if ((sb.st_mode & S_ISGID) == S_ISGID)
        mx_printstr(BLK_F_CYAN_B);
    else if ((sb.st_mode & S_IXUSR) == S_IXUSR)
        mx_printstr(RED);
    else
        mx_printstr(RESET);
}

void mx_colorized_output(char *filename, char *path) {
    struct stat sb;

    lstat(path, &sb);
    if (S_ISFIFO(sb.st_mode))
        mx_printstr(YEL);
    else if (S_ISCHR(sb.st_mode))
        mx_printstr(CHR);
    else if (S_ISDIR(sb.st_mode))
        print_dir(sb);
    else if (S_ISBLK(sb.st_mode))
        mx_printstr(BLOCK);
    else if (S_ISREG(sb.st_mode))
        print_reg_file(sb);
    else if (S_ISLNK(sb.st_mode))
        mx_printstr(MAG);
    else if (S_ISSOCK(sb.st_mode))
        mx_printstr(GRN);

    mx_printstr(filename);
    mx_printstr(RESET);
}
