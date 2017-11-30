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
    fa_set_state_initial(&test, 1);
    fa_set_state_initial(&test, 3);
    fa_set_state_final(&test, 3);
    fa_set_state_final(&test, 4);
    fa_add_transition(&test, 0,'a',1);
    fa_add_transition(&test, 0,'b',2);
    fa_add_transition(&test, 1,'a',2);
    fa_add_transition(&test, 1,'b',2);
    fa_add_transition(&test, 2,'a',3);
   fa_add_transition(&test, 2,'b',4);
   fa_add_transition(&test, 3,'a',4);
   fa_add_transition(&test, 3,'b',4);
    fa_add_transition(&test, 4,'a',4);
        /*nbTransition=fa_count_transitions(&test);
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
        }*/

        fa_remove_state(&test,2);

        //fa_pretty_print(&test, fichier);


        /*struct graph g;
        g.size = 3;
        g.transition = calloc(g.size,sizeof(struct state));
        for(int i=0; i<g.size;i++) {
            g.transition[i] = calloc(g.size, sizeof(struct state));
        }

        for(int i=0; i<g.size;i++) {
            for (int j = 0; j < g.size; j++) {
                g.transition[i][j] = false;
                g.transition[j][i] = false;

            }
        }

        bool visited[3] = {false, false, false};

        g.transition[0][1] = true;
        g.transition[1][1] = true;
        g.transition[1][2] = true;

        graph_depth_first_search(&g, 1, visited);

        if (graph_has_path(&g, 0, 2)) {
            printf("chemin \n");
        }*/

      /* struct graph g2;
        graph_create_from_fa(&g2, &test, true);

        if (graph_has_path(&g2, 1, 3)) {
            printf("chemin 2 \n");
        }

    if(fa_is_language_empty(&test)) {
        printf("Langage non vide");
    }
    else {
        printf("Langage vide");
    }*/

   // fa_destroy(&test);

    //graph_destroy(&g2);

    return 0;
}
