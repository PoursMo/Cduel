#include "action.h"

static void move_player_left(samurai *player, samurai *opponent, int value)
{
    if(player->x - value < 0)
    {
        opponent->x += player->x;
        player->x = 0;
    }
    else
    {
        player->x -= value;
        opponent->x += value;
    }
}

static void move_player_right(samurai *player, samurai *opponent, int value)
{
    if(opponent->x - value < 0)
        value = opponent->x;
    player->x += value;
    opponent->x -= value;
}

static void move_opponent_left(samurai *player, samurai *opponent, int value)
{
    if(opponent->x - value < 0)
        opponent->x = 0;
    else
        opponent->x -= value;
}

static void move_opponent_right(samurai *player, samurai *opponent, int value)
{
    if(opponent->x + player->x + value > 32)
        opponent->x = 32 - player->x;
    else
        opponent->x += value;
}

const struct actions_t actions = {do_attack, do_parry, do_move_left, do_move_right};

void *pick_random_action()
{
    void (*action_array[])(samurai*, samurai*) = {
        actions.attack,
        actions.parry,
        actions.move_left,
        actions.move_right,
    };
    return action_array[rand() % sizeof(action_array) / sizeof(void*)];
}

void do_action(samurai *doer, samurai *other)
{
    doer->action(doer, other);
}

void do_attack(samurai *doer, samurai *other)
{
    if((doer->is_player && other->x <= 1) || (!doer->is_player && doer->x <= 1))
    {
        if(other->action == actions.parry)
        {
            printf("%s's attack got parried\n", doer->name);
            doer->poise -= 3;
        }
        else
        {
            printf("%s swings his blade\n", doer->name);
            other->health -= 1;
        }
    }
    else
        printf("%s attacks but is too far from %s\n", doer->name, other->name);
}

void do_parry(samurai *doer, samurai *other)
{
    printf("%s parries\n", doer->name);
}

void do_move_left(samurai *doer, samurai *other)
{
    printf("%s moves to the left\n", doer->name);
    if(doer->is_player)
        move_player_left(doer, other, 2);
    else
        move_opponent_left(other, doer, 2);
}

void do_move_right(samurai *doer, samurai *other)
{
    printf("%s moves to the right\n", doer->name);
    if(doer->is_player)
        move_player_right(doer, other, 2);
    else
        move_opponent_right(other, doer, 2);
}