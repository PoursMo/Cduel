#include "samurai.h"

static void on_posture_break(samurai *samurai)
{
    printf("%s's posture is broken", samurai->name);
}

static void on_death(samurai *samurai)
{
    printf("%s is dead", samurai->name);
}

const char *opponent_names[10] = {"Jean", "Claude", "Pierre", "Roger", "Alain", "Louis", "Gaston", "Benoit", "Nicolas", "Henri"};

void reduce_health(samurai *samurai, int value)
{
    if(samurai->health - value < 0)
        samurai->health = 0;
    else
        samurai->health -= value;
    if(samurai->health == 0)
        on_death(samurai);
}

void reduce_posture(samurai *samurai, int value)
{
    if(samurai->posture - value < 0)
        samurai->health = 0;
    else
        samurai->posture -= value;
    if(samurai->posture == 0)
        on_posture_break(samurai);
}

void increase_posture(samurai *samurai, int value)
{
    if(samurai->posture + value > samurai->max_posture)
        samurai->posture = samurai->max_posture;
    else
        samurai->posture += value;
}