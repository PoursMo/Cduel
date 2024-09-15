#include "game.h"
#include "samurai.h"
#include "colors.h"

void print_samurai_health(samurai samurai)
{
    int size = 50;
    int perc = samurai.health * size / samurai.max_health;
    int i = 0;
    printf("%s's health\t|", samurai.name);
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

void print_samurai_poise(samurai samurai)
{
    int size = 50;
    int perc = samurai.poise * size / samurai.max_poise;
    int i = 0;
    printf("%s's poise\t|", samurai.name);
    while(i < size)
    {
        if(i < perc)
            printf("@");
        else
            printf(" ");
        i++;
    }
    printf("|\n");
}

void move_player_left(samurai *player, samurai *opponent, int value)
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

void move_player_right(samurai *player, samurai *opponent, int value)
{
    if(opponent->x - value < 0)
        value = opponent->x;
    player->x += value;
    opponent->x -= value;
}

void move_opponent_left(samurai *player, samurai *opponent, int value)
{
    if(opponent->x - value < 0)
        opponent->x = 0;
    else
        opponent->x -= value;
}

void move_opponent_right(samurai *player, samurai *opponent, int value)
{
    if(opponent->x + player->x + value > 32)
        opponent->x = 32 - player->x;
    else
        opponent->x += value;
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

void setup()
{
    srand(time(NULL));
}

int main()
{
    setup();
    samurai player, opponent;
    player.x = 5;
    opponent.x = 5;
    player.max_health = 20;
    player.health = 8;
    player.max_poise = 30;
    player.poise = 26;
    get_player_name(&player);
    strcat(opponent.name, RED);
    strcat(opponent.name, opponent_names[rand() % 10]);
    strcat(opponent.name, RESET);
    printf("%s has entered the dojo", opponent.name);
    char input;
    while(scanf(" %c",&input))
    {
        system("clear");
        if(input == 'a')
            move_player_left(&player, &opponent, 1);
        if(input == 'd')
            move_player_right(&player, &opponent, 1);
        print_samurais(player, opponent);
        printf("\n");
        print_samurai_health(player);
        print_samurai_poise(player);
    }
    
}