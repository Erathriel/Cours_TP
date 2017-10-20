#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "fa.h"

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
            self->transitions[i][j].states=calloc(state_count, sizeof(struct state));
        }
    }

}

void fa_destroy(struct fa *self) {
    free(self->states);
    for(int i=0; i<self->state_count;i++){
        for (int j = 0; j < self->alpha_count; j++)
        {
            free(self->transitions[i][j].states);
        }
       ///free(self->transitions[i]);
    }
    //free(self->transitions);
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
                    printf("etat 4 :%d\n", (int)self->transitions[i][j].states[4] );
                    if (self->transitions[i][j].states[k]==1)
                    {
                        printf("%d\n", (int)self->transitions[i][j].states[k] );
                        printf("taille : %d\n i : %d , j : %d, k : %d\n", (int)self->transitions[i][j].size, i, j, k);
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