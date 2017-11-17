//
// Created by Antoine on 15/09/2017.
//


#include <stdio.h>
#include <stdlib.h>
#include "fa.h"

int main (int argc, char *argv[]) {
    struct fa test;
    int nbTransition;
    FILE* fichier = NULL;
    fichier= fopen("Automate.txt", "w");
    fa_create(&test,2, 5);
    fa_set_state_initial(&test, 0);
    //fa_set_state_initial(&test, 1);
    //fa_set_state_final(&test, 1);
    fa_set_state_final(&test, 4);
    // Uniquement avec un caractère minuscule à modifier plus tard...
    /*fa_add_transition(&test,0,'a',1);
    fa_add_transition(&test,0,'a',2);
    fa_add_transition(&test,0,'a',3);
    fa_add_transition(&test,1,'a',3);
    fa_add_transition(&test,2,'a',3);
    fa_add_transition(&test,2,'b',4);
    fa_add_transition(&test,3,'a',3);
    fa_add_transition(&test,3,'b',4);
    fa_add_transition(&test,4,'a',4);
    fa_add_transition(&test,4,'b',4);
    fa_remove_transition(&test,4,'b',4);*/
    //fa_remove_state(&test,1);
    fa_add_transition(&test, 0,'a',1);
    fa_add_transition(&test, 0,'b',2);
    fa_add_transition(&test, 1,'a',2);
    fa_add_transition(&test, 1,'b',3);
    fa_add_transition(&test, 2,'a',3);
    fa_add_transition(&test, 2,'b',4);
    fa_add_transition(&test, 3,'a',4);
    fa_add_transition(&test, 3,'b',4);
    //fa_add_transition(&test, 4,'a',4);
   // fa_add_transition(&test, 4,'b',3);
    nbTransition=fa_count_transitions(&test);
    printf("%d\n",nbTransition );
    if (fa_is_deterministic(&test))
    {
        printf("Est deterministe\n");
    }
    else{
        printf("N'est pas deterministe\n");
    }
    if (fa_is_complete(&test))
    {
        printf("Est complet\n");
    }
    else{
        printf("N'est pas complet\n");
    }

    fa_make_complete(&test);

    if (fa_is_complete(&test))
    {
        printf("Est complet\n");
    }
    else{
        printf("N'est pas complet\n");
    }
    
    fa_pretty_print(&test, fichier);
    fa_destroy(&test);
    return 0;
}
