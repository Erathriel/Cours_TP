//
// Created by Antoine on 15/09/2017.
//


#include <stdio.h>
#include <stdlib.h>
#include "../include/fa.h"

int main (int argc, char *argv[]) {

    // Création d'un automate "test"
    struct fa test;
    int nbTransition;
    FILE* fichier = NULL;
    fichier= fopen("Automate.txt", "w");
    fa_create(&test,2, 5);

    // Ajout d'état initiaux et finaux  dans l'automate "test"
    fa_set_state_initial(&test, 1);
    fa_set_state_initial(&test, 3);
    fa_set_state_final(&test, 3);
    fa_set_state_final(&test, 4);

    //Ajout et retrait de transitions puis d'un état sur l'automate "test"
    fa_add_transition(&test, 0,'a',1);
    fa_add_transition(&test, 0,'b',2);
    fa_add_transition(&test, 2,'a',3);
    fa_add_transition(&test, 3,'a',4);
    fa_remove_transition(&test, 3, 'a', 4);
    fa_remove_state(&test,1);

    //Affichage du nombre de transition de l'automate "test"
    nbTransition=fa_count_transitions(&test);
    printf("Nombre de transitions %d\n",nbTransition );

    //Vérification si l'automate "test" est déterministe
    if (fa_is_deterministic(&test))
    {
        printf("Est deterministe\n");
    }
    else{
        printf("N'est pas deterministe\n");
    }

    //Vérification si l'automate "test" est complet (il ne l'est pas à ce moment là)
    if (fa_is_complete(&test))
    {
        printf("Est complet\n");
    }
    else{
        printf("N'est pas complet\n");
    }


    //L'automate "test" est rendu complet
    fa_make_complete(&test);


    //On réeffectue la vérification pour voir si il est complet
    if (fa_is_complete(&test))
    {
        printf("Est complet\n");
    }
    else{
        printf("N'est pas complet\n");
    }

    //Affichage de l'automate "test" dans le fichier "Automate.txt"
    fa_pretty_print(&test, fichier);



    //Création d'un graphe
    struct graph g;
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

    // Parcours du graphe en profondeur
    graph_depth_first_search(&g, 1, visited);


    //Vérification de l'existence d'un chemin entre 2 états
    if (graph_has_path(&g, 0, 2)) {
        printf("il existe un chemin \n");
    }

    // Création d'un graphe à partir d'un automate
    struct graph g2;
    graph_create_from_fa(&g2, &test, true);

    if (graph_has_path(&g2, 1, 3)) {
        printf("il existe un chemin (graphe 2) \n");
    }

    // Vérification si l'automate ne contient que le langage vide
    if(fa_is_language_empty(&test)) {
        printf("Langage non vide \n");
    }
    else {
        printf("Langage vide \n");
    }


    // Création de deux automates "test2" et "test3" qui serviront pour le produit
    struct fa test2;
    struct fa test3;
    fa_create(&test2,2, 3);
    fa_create(&test3,2, 3);
    fa_set_state_initial(&test2, 0);
    fa_set_state_initial(&test3, 0);
    fa_set_state_initial(&test3, 1);
    fa_set_state_final(&test2, 2);
    fa_set_state_final(&test3, 2);
    fa_add_transition(&test2, 0,'a',1);
    fa_add_transition(&test2, 1,'a',0);
    fa_add_transition(&test2, 1,'b',2);
    fa_add_transition(&test2, 2,'b',2);
    fa_add_transition(&test3, 0,'a',1);
    fa_add_transition(&test3, 1,'a',2);
    fa_add_transition(&test3, 1,'b',2);
    fa_add_transition(&test3, 2,'b',1);
    struct fa test4;


    //Produit des automates "test2" et "test3" crée dans l'automate "test4"
    fa_create_product(&test4, &test2, &test3);


    //Vérification si l'intersection entre les automates "test2" et "test3" est vide
    if(fa_has_empty_intersection(&test2, &test3)) {
        printf("Intersection vide \n");
    }
    else {
        printf("Intersection non vide \n");
    }

    //Suppression des états co-accessibles et non accessibles
    fa_remove_transition(&test, 1, 'b', 2);
    fa_remove_non_accessible_states(&test2);
    fa_remove_non_co_accessible_states(&test2);

    fa_destroy(&test);
    fa_destroy(&test2);
    fa_destroy(&test3);
    fa_destroy(&test4);
    graph_destroy(&g);
    graph_destroy(&g2);

    return 0;
}