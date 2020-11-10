#include "uls.h"

int main(int argc, char *argv[]) {
    t_uls *uls = (t_uls *)malloc(sizeof(t_uls));
    t_flags flag;
    uls->dir_content = NULL;

    mx_flags_initialization(&flag);
    if (argc > 1) {
        mx_arguments_parse(&uls, &flag, argv, argc);
    }
    if (flag.f == false && flag.t == false) {
        mx_bubble_sort(uls->dirs, uls->count_dirs);
        mx_bubble_sort(uls->files, uls->count_files);
    }
    mx_uls_manager(uls, &flag);
    mx_clean_memory(uls, &flag, argc);

    exit(errno);
}
