#include "samurai.h"

static void on_death(samurai *samurai)
{
    printf("%s is dead\n", samurai->name);
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
        samurai->posture = 0;
    else
        samurai->posture -= value;
}

void increase_posture(samurai *samurai, int value)
{
    if(samurai->posture + value > samurai->max_posture)
        samurai->posture = samurai->max_posture;
    else
        samurai->posture += value;
}

samurai generate_opponent(int playerx)
{
    samurai opponent = {.x = 32 - playerx, .health = rand() % 2 + 1, .max_posture = 10, .posture = 10};
    strcpy(opponent.name, opponent_names[rand() % 10]);
    // print_samurai_name(opponent);
    printf(" has entered the dojo\n");
    return opponent;
}