#include "ai.h"

void *get_opponent_action(samurai player, samurai opponent)
{
    if(opponent.posture == 0)
        return actions.recover;
    if(opponent.x == 0)
    {
        if(opponent.x == 32 - player.x)
        {
            int r = rand() % 2;
            if(r == 0)
                return actions.attack; //1/2
            return actions.parry; //1/2
        }
        else
        {
            int r = rand() % 5;
            if(r == 4)
                return actions.move_right; //1/5
            if(r < 2)
                return actions.attack; //2/5
            return actions.parry; //2/5
        }
    }
    if(opponent.x == 1)
    {
        if(opponent.x == 32 - player.x)
        {
            int r = rand() % 5;
            if(r == 4)
                return actions.move_right; //1/5
            if(r < 2)
                return actions.attack; //2/5
            return actions.parry; //2/5
        }
        else
        {
            int r = rand() % 6;
            if(r == 5)
                return actions.move_right; //1/6
            if(r == 4)
                return actions.move_left; //1/6
            if(r < 2)
                return actions.attack; //2/6
            return actions.parry; //2/6
        }
    }
    if(opponent.x == 2)
    {
        //attack
        //move_right not if x = 32 - playerx
        //move_left
        //focus if posture < 8
    }
    if(opponent.x == 3)
    {
        //attack
        //move_right not if x = 32 - playerx
        //move_left
        //focus if posture < 8
    }
    if(opponent.x == 4)
    {
        //move_right not if x = 32 - playerx
        //move_left
        //focus if posture < 8
    }

}