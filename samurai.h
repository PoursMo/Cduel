#ifndef SAMURAI_H
#define SAMURAI_H

const char *opponent_names[10] = {"Jean", "Claude", "Pierre", "Roger", "Alain", "Louis", "Gaston", "Benoit", "Nicolas", "Henri"};

typedef struct
{
    char name[32];
    int health, max_health;
    int poise, max_poise;
    int power;
    int x;
} samurai;

#endif