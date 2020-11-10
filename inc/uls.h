#pragma once

#include "libmx.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <time.h>


#define FLAGS     "@1AaCcFfGhlmpRrSTtu\0"
#define FLAGS_NUM 20
#define RED       "\x1B[31m"
#define GRN       "\x1B[32m"
#define YEL       "\x1B[33m"
#define BLU       "\x1B[34m"
#define MAG       "\x1B[35m"
#define RESET     "\x1B[0m"
#define BLK_F_RED_B "\x1B[0;30;41m"
#define BLK_F_CYAN_B "\x1B[0;30;46m"
#define BLOCK "\x1B[0;34;46m"
#define CHR "\x1B[0;34;43m"
#define DIR_T "\x1B[0;30;42m"
#define DIR_X "\033[0;30;43m"


typedef struct s_uls {
    char *flags;
    char **all_files;
    char **files;
    char **dirs;
    char **dir_content;
    char **dir_names;
    int dirs_num;
    int count_flags;
    int count_all_files;
    int count_files;
    int count_dirs;
    int wrong;
    bool flag_l;
}              t_uls;

typedef struct s_flags {
    bool at;
    bool One;
    bool A;
    bool a;
    bool С;
    bool c;
    bool F;
    bool f;
    bool G;
    bool h;
    bool l;
    bool m;
    bool p;
    bool R;
    bool r;
    bool S;
    bool T;
    bool t;
    bool u;

}              t_flags;

typedef struct s_l {
    char **file;
    char **mode;
    char **user;
    char **gid;
    char **time;
    char **name;
    char **name_2;
    char **size;
    char **link;
    char **path;
    int triger;
    int len;
    int bloks;
    bool triger_all;
    bool file_arg;
    bool many_fls;
}             t_l;

typedef struct s_size_for_l {
    int mode_len;
    int user_len;
    int gid_len;
    int time_len;
    int name_len;
    int size_len;
    int link_size;
}              t_size_for_l;

typedef struct s_output {
    char **filename;
    char **path;
    char **symbol;
    int file_num;
}              t_output;

/*
 *    PARSING
 */
void mx_arguments_parse(t_uls **uls, t_flags *flag, char **argv, int argc);
void mx_parse_flags(t_uls **uls, char **argv, int argc, int *count_args);
void mx_parse_files_and_dirs(t_uls **uls, char **argv, int argc, int count);

/*
 *    FLAGS
 */
void mx_flags_initialization(t_flags *flag);
void mx_flags_manager(t_uls *uls, t_flags *flag);
void mx_flag_l_R(t_flags *flag, t_l **flag_l,
                 char **dir_content, char *main_dir);
char *mx_flag_h(long long size, char *tmp, char *str);
void mx_malloc_for_arr(t_l **flag_l);
void mx_filling_arr(t_l **flag_l, char **str, t_flags *flag, char *main_path);
void mx_build_name(char **path, t_flags *flag, int i, t_l **flag_l);
void mx_flag_at(char *path, t_l **flag_l);
void mx_flag_l_launch_manager(t_uls *uls, t_flags *flag);
void mx_flag_l(t_l **flag_l, t_flags *flag, t_uls *uls, char *main_dir);
char *mx_for_flag_l(struct stat sb, char *path, t_l **flag_l);
void mx_space_for_flag_l(t_l **flag_l, t_size_for_l **size_for_l);
char *mx_flag_l_size(struct stat buff, t_flags *flag, t_l **flag_l);
void mx_flag_p_and_F(t_flags *flag, t_output **opt);
void mx_flag_R_launch_manager(t_uls *uls, t_flags *flag);
void mx_flag_R_recursive(t_flags *flag, char *main_dir);
void mx_flag_r(char **dir_content, int size);
char **mx_flag_S(t_flags *flag, char **dir_content,
                 char *main_dir, int dir_count);
char *mx_flag_time(struct stat buff, t_flags *flag);
char **mx_time_sort_flags(t_flags *flag, char **dir_content,
                          char *main_dir, int dir_count);

/*
 *    ULS MAIN
 */
void mx_uls_manager(t_uls *uls, t_flags *flag);
char **mx_open_dir(t_flags *flag, char *main_dir, int *count);
char **mx_lstat(char **dir_content, int count, int *dirs_num);
char **mx_dir_path_creator(t_flags *flag, char **dir_content,
                           char *main_dir, int dir_count);
void mx_uls_basic(t_flags *flag, char *open_dir);
void mx_multi_argc(t_uls *uls, t_flags *flag);

/*
 *    OUTPUT
 */
void mx_error_illegal_option(char c);
void mx_error_no_file_or_dir(char *name);
void mx_error_permission_denied(char *name_of_dir);
void mx_output_results(t_flags *flag, char **objects, char **full_path,
                       int num_in_dir);
void mx_output_dirs(t_flags *flag, char **objects, int num_in_dir);
void mx_output_by_window_size(t_flags *flag, t_output *opt);
int mx_max_len_of_filename(char **objects, int num_in_dir);
void mx_output_in_one_column(t_flags *flag, t_output *opt);
void mx_output_in_one_line(t_flags *flag, t_output *opt, int max_len);
void mx_output_multi_col(t_flags *flag, t_output *opt, int max_len, int col);
void mx_output_separated_by_commas(t_flags *flag, t_output *opt);
void mx_colorized_output(char *filename, char *path);
void mx_output_flag_l(t_l **flag_l, t_size_for_l **size_for_l, t_flags *flag);
void mx_print_dir_name_flag_l(t_l **flag_l, t_flags *flag, char *main_dir,
                  char **dir_content);

/*
 * Free memory
 */
void mx_clean_memory(t_uls *uls, t_flags *flag, int argc);
void mx_flag_l_clean_memory(t_l *flag_l);
