//
// Created by Igor Khanenko on 10/14/20.
//
#include "uls.h"

void checking_output_changes_flags(t_uls *uls, t_flags *flag, int i) {
    if (uls->flags[i] == 'a' && flag->a == false)
        flag->a = true;
    else if (uls->flags[i] == 'A' && flag->A == false)
        flag->A = true;
    else if (uls->flags[i] == 'F') {
        flag->F = true;
        flag->p = false;
    }
    else if (isatty(1) && uls->flags[i] == 'G')
        flag->G = true;
    else if (uls->flags[i] == 'p') {
        flag->p = true;
        flag->F = false;
    }
}

void checking_long_format_flags(t_uls *uls, t_flags *flag, int i) {
    if (uls->flags[i] == '@')
        flag->at = true;
    else if (uls->flags[i] == 'h')
        flag->h = true;
    else if (uls->flags[i] == 'T')
        flag->T = true;
}

void checking_sort_flags (t_uls *uls, t_flags *flag, int i) {
    if (uls->flags[i] == 'f' && flag->f == false) {
        flag->f = true;
        flag->a = true;
        flag->r = false;
        flag->S = false;
        flag->t = false;
    }
    if (flag->f == false) {
        if (uls->flags[i] == 'r')
            flag->r = true;
        else if (uls->flags[i] == 't') {
            flag->t = true;
            flag->S = false;
        }
        else if (uls->flags[i] == 'S') {
            flag->S = true;
            flag->t = false;
        }
    }
}

void checking_output_format_flags(t_uls *uls, t_flags *flag, int k) {
        if (uls->flags[k] == 'C' && flag->m == false) {
            flag->С = true;
            flag->One = false;
            flag->l = false;
        }
        else if (uls->flags[k] == '1') {
            flag->One = true;
            flag->С = false;
            flag->m = false;
            flag->l = false;
        }
        else if (uls->flags[k] == 'l') {
            flag->l = true;
            flag->One = false;
            flag->С = false;
            flag->m = false;
        }
        else if (uls->flags[k] == 'm') {
            flag->m = true;
            flag->One = false;
            flag->С = false;
            flag->l = false;
        }
}

void mx_flags_manager(t_uls *uls, t_flags *flag) {
    for (int k = 0; k < uls->count_flags; k++)
        checking_output_format_flags(uls, flag, k);
    for (int i = 0; i < uls->count_flags; i++) {
        checking_output_format_flags(uls, flag, i);
        checking_sort_flags(uls, flag, i);
        checking_output_changes_flags(uls, flag, i);
        if (flag->l == true)
            checking_long_format_flags(uls, flag, i);
        if (uls->flags[i] == 'R')
            flag->R = true;
        else if (uls->flags[i] == 'u' && flag->u == false) {
            flag->u = true;
            flag->c = false;
        }
        else if (uls->flags[i] == 'c' && flag->c == false) {
            flag->c = true;
            flag->u = false;
        }
    }
}
