#ifndef ACTION_H
#define ACTION_H

#include <stdio.h>
#include <stdlib.h>
#include "samurai.h"

struct actions_t {
    void (*attack)(samurai*, samurai*);
    void (*parry)(samurai*, samurai*);
    void (*move_left)(samurai*, samurai*);
    void (*move_right)(samurai*, samurai*);
    void (*focus)(samurai*, samurai*);
    void (*recover)(samurai*, samurai*);
};

extern const struct actions_t actions;

void *pick_random_action();
void do_action(samurai *doer, samurai *other);
void do_recover(samurai *doer, samurai *other);
void do_focus(samurai *doer, samurai *other);
void do_attack(samurai *doer, samurai *other);
void do_parry(samurai *doer, samurai *other);
void do_move_left(samurai *doer, samurai *other);
void do_move_right(samurai *doer, samurai *other);

#endif