//
// Created by Dima Voichuck on 10/18/20.
//

#include "uls.h"

static void first_char(struct stat sb, char *type, t_l **flag_l) {
    if ((sb.st_mode & S_IFDIR) == S_IFDIR)
        type[0] = 'd';
    if ((sb.st_mode & S_IFIFO) == S_IFIFO)
        type[0] = 'p';
    if ((sb.st_mode & S_IFCHR) == S_IFCHR) {
        type[0] = 'c';
        (*flag_l)->triger = 1;
    }
    if ((sb.st_mode & S_IFBLK) == S_IFBLK) {
        type[0] = 'b';
        (*flag_l)->triger = 1;
    }
    if ((sb.st_mode & S_IFREG) == S_IFREG)
        type[0] = '-';
    if ((sb.st_mode & S_IFLNK) == S_IFLNK) {
        type[0] = 'l';
        (*flag_l)->triger = 2;
    }
    if ((sb.st_mode & S_IFSOCK) == S_IFSOCK)
        type[0] = 's';
}

static void other_char_2(struct stat sb, char *type) {
    if ((sb.st_mode & S_IXGRP) == S_IXGRP)
        type[6] = 'x';
    if ((sb.st_mode & S_ISGID) == S_ISGID)
        type[6] = (type[6] = 'x') ? 's' : 'S';
    if ((sb.st_mode & S_IROTH) == S_IROTH)
        type[7] = 'r';
    if ((sb.st_mode & S_IWOTH) == S_IWOTH)
        type[8] = 'w';
    if ((sb.st_mode & S_IXOTH) == S_IXOTH)
        type[9] = 'x';
    if ((sb.st_mode & S_ISVTX) == S_ISVTX)
        type[9] = (type[9] = 'x') ? 't' : 'T';
}

static void other_char(struct stat sb, char *type) {
    if ((sb.st_mode & S_IRUSR) == S_IRUSR)
        type[1] = 'r';
    if ((sb.st_mode & S_IWUSR) == S_IWUSR)
        type[2] = 'w';
    if ((sb.st_mode & S_IXUSR) == S_IXUSR)
        type[3] = 'x';
    if ((sb.st_mode & S_ISUID) == S_ISUID)
        type[3] = (type[3] = 'x') ? 's' : 'S';
    if ((sb.st_mode & S_IRGRP) == S_IRGRP)
        type[4] = 'r';
    if ((sb.st_mode & S_IWGRP) == S_IWGRP)
        type[5] = 'w';
    other_char_2(sb, type);
}

char *mx_for_flag_l(struct stat sb, char *path, t_l **flag_l) {
    char *type = mx_strnew(11);
    (*flag_l)->triger = 0;
    acl_t acl = NULL;
    ssize_t attr = 0;
    attr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
    acl = acl_get_file(path, ACL_TYPE_EXTENDED);
    for (int i = 0; i < 10; i++) {
        type[i] = '-';
    }
    type[10] = ' ';
    if (attr > 0) {
        type[10] = '@';
    }
    else if (acl != NULL)
        type[10] = '+';
    first_char(sb, type, flag_l);
    other_char(sb, type);
    acl_free(acl);
    return type;
}
