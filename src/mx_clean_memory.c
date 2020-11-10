#include "uls.h"

void mx_clean_memory(t_uls *uls, t_flags *flag, int argc) {
    if (argc > 1) {
        mx_strdel(&uls->flags);
        mx_del_strarr(&uls->dirs);
        mx_del_strarr(&uls->files);
        mx_del_strarr(&uls->all_files);
    }
    if (uls->dir_content)
        mx_del_strarr(&uls->dir_content);
    if (malloc_size(uls->dir_names))
        mx_del_strarr(&uls->dir_names);
    free(uls);
}
