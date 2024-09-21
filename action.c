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
    player = player; //Useless
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

const struct actions_t actions = {do_attack, do_parry, do_move_left, do_move_right, do_focus, do_recover};

void do_action(samurai *doer, samurai *other)
{
    doer->action(doer, other);
}

void do_recover(samurai *doer, samurai *other)
{
    other = other; //Useless
    printf("%s is recovering from broken posture\n", doer->name);
    increase_posture(doer, 3);
}

void do_focus(samurai *doer, samurai *other)
{
    other = other; //Useless
    printf("%s focuses\n", doer->name);
    increase_posture(doer, 3);
}

void do_attack(samurai *doer, samurai *other)
{
    reduce_posture(doer, 2);
    if((doer->is_player && other->x <= 1) || (!doer->is_player && doer->x <= 1))
    {
        if(other->action == actions.parry)
        {
            printf("%s's attack got parried\n", doer->name);
            reduce_posture(doer, 2);
            reduce_posture(other, 2);
        }
        else if(other->action == actions.attack)
        {
            printf("%s's blade bounced on %s's blade\n", doer->name, other->name);
        }
        else
        {
            printf("%s swings his blade and hits %s\n", doer->name, other->name);
            reduce_health(other, 1);
        }
    }
    else
        printf("%s attacks but is too far from %s\n", doer->name, other->name);
}

void do_parry(samurai *doer, samurai *other)
{
    other = other; //Useless
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