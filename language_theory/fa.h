//
// Created by Antoine on 15/09/2017.
//

#ifndef TP1TL_FA_H
#define TP1TL_FA_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct state {
    bool is_initial;
    bool is_final;
};

struct fa {
    size_t alpha_count;
    size_t state_count;
    struct state *states;
    struct state_set **transitions;
};

struct state_set {
    size_t size;
    size_t capacity;
    size_t *states;
};


void fa_create(struct fa *self, size_t alpha_count, size_t state_count);

void fa_destroy(struct fa *self);

void fa_set_state_initial(struct fa *self, size_t state);

void fa_set_state_final(struct fa *self, size_t state);

void fa_add_transition(struct fa *self,size_t from, char alpha, size_t to);

void fa_remove_transition(struct fa *self,size_t from, char alpha, size_t to);

void fa_remove_state(struct fa *self, size_t state);

size_t fa_count_transitions(const struct fa *self);

bool fa_is_deterministic(const struct fa *self);

bool fa_is_complete(const struct fa *self);

void fa_make_complete(struct fa *self);

void fa_pretty_print(const struct fa *self, FILE *out);

#endif //TP1TL_FA_H
