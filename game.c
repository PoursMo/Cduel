#include "game.h"

void enter_continue()
{
    printf("Press enter to continue");
    fflush(stdout);
    char c;
    while (c = getchar(), c != '\n' && c != EOF);
    system("clear");
}

char get_player_input()
{
    char c = 0;
    print_controls();
    while(1)
    {
        c = getchar();
        if(c == 'h')
        {
            print_help();
            return get_player_input();
        }
        else if(c == '\n')
            continue;
        else if(!strchr("wasdf" , c))
            printf("Enter a correct key\n");
        else
            break;
    }
    return c;
}

void *get_player_action()
{
    char player_input = get_player_input();
    if(player_input == 'a')
        return actions.move_left;
    if(player_input == 'd')
        return actions.move_right;
    if(player_input == 'w')
        return actions.attack;
    if(player_input == 's')
        return actions.parry;
    if(player_input == 'f')
        return actions.focus;
    else
        return NULL;
}

void *pick_random_action()
{
    void (*action_array[])(samurai*, samurai*) = {
        actions.attack,
        actions.parry,
        actions.move_left,
        actions.move_right,
        actions.focus,
        actions.recover,
    };
    return action_array[rand() % sizeof(action_array) / sizeof(void*)];
}

void game()
{
    //setup
    system("clear");
    srand(time(NULL));
    //player creation
    samurai player = {.x = 0, .health = 3, .max_posture = 10, .posture = 10, .is_player = 1};
    get_player_name(&player);
    //game loop
    while(player.health > 0)
    {
        enter_continue();
        samurai opponent = generate_opponent(player.x);
        enter_continue();
        while(opponent.health > 0)
        {
            print_samurais(player, opponent);
            printf("\n");
            print_samurai_stats(player);
            printf("\n");
            print_samurai_stats(opponent);
            printf("\n");
            if(player.posture > 0)
                player.action = get_player_action();
            else
            {
                printf("Your posture is broken, press enter to continue");
                player.action = actions.recover;
            }
            flush_getchar();
            system("clear");
            opponent.action = pick_random_action();
            if(player.action == actions.attack)
            {
                do_action(&opponent, &player);
                do_action(&player, &opponent);
            }
            else
            {
                do_action(&player, &opponent);
                do_action(&opponent, &player);
            }
        }
    }
}

int main()
{
    game();
}