//
// Created by Antoine on 15/09/2017.
//


#include <stdio.h>
#include "fa.h"

int main (int argc, char *argv[]) {
    struct fa test;
    fa_create(&test,2, 4);
    fa_set_state_initial(&test, 1);
    fa_set_state_final(&test, 1);
    fa_add_transition(&test,1,1,2);
    fa_destroy(&test);
    return 0;
}
