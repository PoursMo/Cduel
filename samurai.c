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
    const char *name = opponent_names[rand() % 10];
    char new[sizeof(name)];
    strcpy(new, name);
    strcpy(opponent.name, add_format_to_string(new, OPPONENT_COLOR));
    printf("%s has entered the dojo\n", opponent.name);
    return opponent;
}

void get_player_name(samurai *player)
{
    char name[32];
    size_t max_char = sizeof(name) - 1 - 8 - 4;
    printf("Type in your samurai name (max %ld characters):\n", max_char);
    fflush(stdout);
    scanf("%s", name);
    while (getchar() != '\n');
    if(strlen(name) > max_char)
    {
        printf("Too many characters\n");
        get_player_name(player);
        return;
    }
    strcpy(player->name, add_format_to_string(name, PLAYER_COLOR));
    printf("Your samurai name is %s\n", player->name);
}