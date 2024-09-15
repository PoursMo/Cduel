#include "game.h"
#include "samurai.h"
#include "colors.h"
#include "action.h"

void enter_continue()
{
    printf("Press enter to continue");
    fflush(stdout);
    char c;
    while (c = getchar(), c != '\n' && c != EOF);
    system("clear");
}

void print_samurai_health(samurai samurai)
{
    int i = 0;
    printf("%s's health:\t", samurai.name);
    while(i++ < samurai.health)
        printf("@ ");
    printf("\n");
}

void print_samurai_poise(samurai samurai)
{
    int size = 50;
    int perc = samurai.poise * size / samurai.max_poise;
    int i = 0;
    printf("%s's poise:\t|", samurai.name);
    while(i < size)
    {
        if(i < perc)
            printf("#");
        else
            printf(" ");
        i++;
    }
    printf("|\n");
}

void print_samurais(samurai player, samurai opponent)
{
    int right_wall = 32 - player.x - opponent.x;
    printf(" ________________________________________\n");
    printf("|%*s ^   %*s ^ %*s|\n", player.x, "", opponent.x, "", right_wall, "");
    printf("|%*s O   %*s O %*s|\n", player.x, "", opponent.x, "", right_wall, "");
    printf("|%*s/|\\/%*s\\/|\\%*s|\n", player.x, "", opponent.x, "", right_wall, "");
    printf("|%*s/ \\ %*s / \\%*s|\n", player.x, "", opponent.x, "", right_wall, "");
    printf("==========================================\n");
}

void get_player_name(samurai *player)
{
    char name[32];
    printf("Type in your character name (max 19 characters):\n");
    fflush(stdout);
    scanf("%s", name);
    while (getchar() != '\n');
    if(strlen(name) > 19)
    {
        printf("Too many characters\n");
        get_player_name(player);
        return;
    }
    strcat(player->name, GREEN);
    strcat(player->name, name);
    strcat(player->name, RESET);
    printf("Your name is %s\n", player->name);
}

samurai generate_opponent(int playerx)
{
    samurai opponent = {.x = 32 - playerx, .health = 2, .max_poise = 10, .poise = 10};
    strcat(opponent.name, RED);
    strcat(opponent.name, opponent_names[rand() % 10]);
    strcat(opponent.name, RESET);
    return opponent;
}

int main()
{
    srand(time(NULL));
    samurai player = {.x = 0, .health = 3, .max_poise = 10, .poise = 10, .is_player = 1};
    get_player_name(&player);
    enter_continue();
    samurai opponent = generate_opponent(player.x);
    printf("%s has entered the dojo\n", opponent.name);
    enter_continue();
    char c;
    while(1)
    {
        print_samurais(player, opponent);
        print_samurai_health(opponent);
        print_samurai_poise(opponent);
        print_samurai_health(player);
        print_samurai_poise(player);
        printf("\na: move left  d: move right  w: attack  s: parry\n");
        c = getchar();
        system("clear");
        if(c == 'a')
            player.action = actions.move_left;
        else if(c == 'd')
            player.action = actions.move_right;
        else if(c == 'w')
            player.action = actions.attack;
        else if(c == 's')
            player.action = actions.parry;
        else
        {
            printf("Use a correct key\n");
            continue;
        }
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