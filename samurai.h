#ifndef SAMURAI_H
#define SAMURAI_H

extern const char *opponent_names[10];

typedef struct
{
    char name[32];
    int health;
    int poise, max_poise;
    int x;
    int is_player;
    void (*action)();
} samurai;

#endif