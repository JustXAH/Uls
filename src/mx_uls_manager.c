//
// Created by Igor Khanenko on 10/19/20.
//

#include "uls.h"

void mx_uls_manager(t_uls *uls, t_flags *flag) {
    if ((flag->С == true || flag->One == true) && flag->R == false)
        uls->count_all_files > 0 ? mx_multi_argc(uls, flag)
                                 : mx_uls_basic(flag, ".");

    else if (flag->l == true) {
        mx_flag_l_launch_manager(uls, flag);
    }

    else if (flag->m == true && flag->R == false)
            uls->count_all_files > 0 ? mx_multi_argc(uls, flag)
                                     : mx_uls_basic(flag, ".");

    else if (flag->R == true && flag->l == false)
        mx_flag_R_launch_manager(uls, flag);
}
