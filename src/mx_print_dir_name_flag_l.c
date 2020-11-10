//
// Created by Dima Voichuck on 11/10/20.
//

#include "uls.h"

void mx_print_dir_name_flag_l(t_l **flag_l, t_flags *flag, char *main_dir,
                              char **dir_content) {
    if ((*flag_l)->file_arg == false) {
        if ((*flag_l)->many_fls == true &&
            flag->R == false) {
            mx_printstr(main_dir);
            mx_printstr(":\n");
        }
        if (dir_content) {
            mx_printstr("total ");
            mx_printint((*flag_l)->bloks);
            mx_printstr("\n");
        }
    }
}
