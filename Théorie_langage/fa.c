#include <stddef.h>
#include <stdlib.h>
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

};

void fa_destroy(struct fa *self) {
    free(self->states);
    for(int i=0; i<self->state_count;i++){
        free(self->transitions[i]);
    }
    free(self->transitions);
    //free(self);
};

void fa_set_state_initial(struct fa *self, size_t state) {
    self->states[state].is_initial=true;
}

void fa_set_state_final(struct fa *self, size_t state){
    self->states[state].is_final=true;
}

void fa_add_transition(struct fa *self,size_t from, char alpha, size_t to) {
    self->transitions[from][(int)alpha-(int)'A'].size++;
    self->transitions[from][(int)alpha-(int)'A'].capacity=self->state_count;
    self->transitions[from][(int)alpha-(int)'A'].states[to]=1;
}