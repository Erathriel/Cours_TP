#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/fa.h"

//
// Created by Antoine on 15/09/2017.
//
void fa_create(struct fa *self, size_t alpha_count, size_t state_count) {
    self->alpha_count = alpha_count;
    self->state_count = state_count;

    self->states = calloc(state_count,sizeof(struct state));
    self->transitions=calloc(state_count, sizeof(struct state_set));

    for(int i=0; i<self->state_count;i++){
        self->transitions[i]=calloc(alpha_count, sizeof(struct state_set));
        for(int j=0; j<alpha_count;j++){
            self->transitions[i][j].states=calloc(state_count, sizeof(size_t));
        }
    }

}

void fa_destroy(struct fa *self) {
    if (self->states == NULL && self->transitions == NULL) {
        return;
    }
    free(self->states);
    for(int i=0; i<self->state_count;i++){
        for (int j = 0; j < self->alpha_count; j++)
        {
            free(self->transitions[i][j].states);
        }
    }
    for (int i=0;i<self->state_count;i++){
        free(self->transitions[i]);
    }
    free(self->transitions);
    self->states = NULL;
    self->transitions = NULL;

}

void fa_set_state_initial(struct fa *self, size_t state) {
    self->states[state].is_initial=true;
}

void fa_set_state_final(struct fa *self, size_t state){
    self->states[state].is_final=true;
}

void fa_add_transition(struct fa *self,size_t from, char alpha, size_t to) {
    self->transitions[from][(int)alpha-(int)'a'].size++;
    self->transitions[from][(int)alpha-(int)'a'].capacity=self->state_count;
    self->transitions[from][(int)alpha-(int)'a'].states[to]=1;

}

void fa_remove_transition(struct fa *self,size_t from, char alpha, size_t to) {
    self->transitions[from][(int)alpha-(int)'a'].states[to]=0;
    self->transitions[from][(int)alpha-(int)'a'].capacity=self->state_count;
    self->transitions[from][(int)alpha-(int)'a'].size--;
}

void fa_remove_state(struct fa *self, size_t state){
    for (int i = 0; i < self->state_count; ++i)
    {
        for (int j = 0; j < self->alpha_count; ++j)
        {
            unsigned char c = (unsigned char) (j+'a');
            if (self->transitions[state][j].states[i] != 0)
            {
                fa_remove_transition(self, state, c, i);          
            }
            /*if (i<state && self->transitions[i][j].states[state]==1)
            {
                fa_remove_transition(self, i, c, state);
                fa_add_transition(self, i, c, state+1);
            }*/
        }
    }
    // a commenter pour 2nd soluce
    /*for (int i = state; i < self->state_count-1; ++i)
    {
        self->states[i]=self->states[i+1];
        for (int j = 0; j < self->alpha_count; ++j)
        {
            self->transitions[i][j].states = self->transitions[i+1][j].states;
        }
    }
    self->state_count--;*/
}

size_t fa_count_transitions(const struct fa *self){
    int transitionNumber=0;
    for (int i = 0; i < self->state_count; ++i)
    {
        for (int j = 0; j < self->alpha_count; ++j)
        {
            for (int k = 0; k < self->transitions[i][j].capacity; ++k)
            {
                if (self->transitions[i][j].states[k]==1)
                {
                    transitionNumber+=1;
                }
            }
        }
    }
    return transitionNumber;
}

bool fa_is_deterministic(const struct fa *self){
    bool deterministic=true;
    int countInit=0;
    int countFinal=0;
    int countTransitionLetter=0;
    for(int i=0; i<self->state_count;i++){
        if(self->states[i].is_initial == true){
            countInit++;
        }
    }
    for(int i=0; i<self->state_count;i++){
        if(self->states[i].is_final == true){
            countFinal++;
        }
    }
    if (countInit>1 || countFinal>1)
    {
        printf("1");
        deterministic=false;
    }
    for (int i = 0; i < self->state_count; ++i)
    {
        for (int j = 0; j < self->alpha_count; ++j)
        {
                    countTransitionLetter=0;
                    for (int k = 0; k < self->transitions[i][j].capacity; ++k)
                    {
                        if (self->transitions[i][j].states[k]==1)
                        {
                            countTransitionLetter++;
                        }
                        if (self->transitions[k][j].states[i]==1)
                        {
                            countTransitionLetter++;
                        }
                        if (countTransitionLetter>1)
                        {
                    deterministic=false;
                            printf("2");
                    return deterministic;
                }
            }
        }
    }
}

bool fa_is_complete(const struct fa *self) {
    bool complete=true;
    int countTransitionLetter=0;

    for (int i = 0; i < self->state_count; ++i)
    {
        for (int j = 0; j < self->alpha_count; ++j)
        {
            countTransitionLetter=0;
            for (int k = 0; k < self->transitions[i][j].capacity; ++k)
            {
                if (self->transitions[i][j].states[k]==1)
                {
                    countTransitionLetter++;
                }
            }
            if (countTransitionLetter<1)
            {
                complete=false;
                return complete;
            }
        }
    }
}

void fa_make_complete(struct fa *self) {
    int countTransitionLetter=0;
    int s = 0;
    if (fa_is_complete(self)) {
        printf("L'automate est déjà complet");
    }
    else {

        self->state_count = self->state_count+1;

                        self->states = realloc(self->states, self->state_count *sizeof(struct state));
                        self->transitions=realloc(self->transitions, self->state_count * sizeof(struct state_set));

                        for(int i=0; i<self->state_count;i++){
                            self->transitions[i]=realloc(self->transitions[i], self->alpha_count * sizeof(struct state_set));
                            for(int j=0; j<self->alpha_count;j++){
                                self->transitions[i][j].states=realloc(self->transitions[i][j].states, self->state_count * sizeof(size_t));
                            }
                        }



                        for (int i = 0; i < self->state_count; ++i)
                        {
                            for (int j = 0; j < self->alpha_count; ++j)
                            {
                                countTransitionLetter=0;
                                for (int k = 0; k < self->transitions[i][j].capacity; ++k)
                                {
                                    if (self->transitions[i][j].states[k]==1)
                                    {
                                        countTransitionLetter++;
                    }
                    s=k;
                }
                if (countTransitionLetter<1)
                {
                    fa_add_transition(self, i,(char)(j+97),self->state_count-1);
                }
            }
        }
    }
}


void fa_pretty_print(const struct fa *self, FILE *out){
    if(out != NULL){
        fprintf(out, "Initial states:\n        ");
        for(int i=0; i<self->state_count;i++){
            if(self->states[i].is_initial == true){
                fprintf(out, "%d ", i);
            }
        }
        fprintf(out, "\nFinal states:\n        ");
        for(int i=0; i<self->state_count;i++){
            if(self->states[i].is_final == true){
                fprintf(out, "%d ", i);
            }
        }
        fprintf(out, "\nTransitions:\n        ");
        for (int i = 0; i < self->state_count ; i++)
        {
            fprintf(out, "For state %d:\n        ", i);
            for (int j = 0; j < self->alpha_count; j++)
            {
                unsigned char c = (unsigned char) ( j + (int) 'a');
                fprintf(out, "        For letter %c:", c);
                for (int k = 0; k < self->transitions[i][j].capacity; k++)
                {
                    if (self->transitions[i][j].states[k]==1)
                    {
                        fprintf(out, "%d ", k);
                    }
                }

                fprintf(out,"\n        ");
            }
        }
        fclose(out);
    }
    else
    {
        printf("Can't open the file...\n");
    }
}

void graph_depth_first_search(const struct graph *self, size_t state, bool* visited) {
    visited[state] = true;
    for(int i = 0; i < self->size; i++) {
        if (self->transition[state][i] == true) {
            if (visited[i] == false) {
                graph_depth_first_search(self, i, visited);
            }
        }
    }
}

bool graph_has_path(const struct graph *self,  size_t from, size_t to) {
    bool visited[self->size];
    for (int i =0; i < self->size; i++) {
        visited[i] = false;
    }
    graph_depth_first_search(self, from, visited);
    if (visited[to]) {
        return true;
    }
    else {
        return false;
    }
}

void graph_create_from_fa(struct graph *self, const struct fa *fa , bool inverted) {
    self->size = fa->state_count;
    self->transition = calloc(self->size, sizeof(size_t));
    for (int i = 0; i < self->size; i++) {
        self->transition[i] = calloc(self->size, sizeof(bool));
    }
    for (int i = 0; i < self->size-1; i++) {
        for (int j = 0; j < fa->alpha_count; j++) {
            for (int k = 0; k < self->size-1; k++) {
                if (fa->transitions[i][j].states[k] == 1) {
                    self->transition[i][k] = true;
                }
            }
        }
    }
}

void graph_destroy(struct graph *self) {
    if (self->transition == NULL) {
        return;
    }
    for (int i=0;i<self->size;i++){
        free(self->transition[i]);
    }
    free(self->transition);
    self->transition = NULL;
}

bool fa_is_language_empty(const struct fa *self) {
    struct graph g;
    graph_create_from_fa(&g, self, true);
    for (int i = 0; i < self->state_count; i++) {
        if (self->states[i].is_initial == true ) {
            for (int j = 0; j < self->state_count; j++) {
                if (self->states[j].is_final == true) {
                   if(graph_has_path(&g, i, j)) {                       return true;
                   }
                }
            }
        }
    }
    return false;
}