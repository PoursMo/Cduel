#ifndef SAMURAI_H
#define SAMURAI_H

#include <stdio.h>

extern const char *opponent_names[10];

typedef struct samurai
{
    char name[32];
    int health;
    int posture, max_posture;
    int x;
    int is_player;
    void (*action)();
} samurai;

void reduce_health(samurai *samurai, int value);
void reduce_posture(samurai *samurai, int value);
void increase_posture(samurai *samurai, int value);

#endif