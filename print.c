#include "print.h"

void print_help()
{
    printf(BOLD "Actions :\n" RESET);
    printf("move left : your character moves to the left by 2 units\n");
    printf("move right : your character moves to the right by 2 units\n");
    printf("attack : spend some posture to swing your blade with a range of 1 unit, can get parried which makes the attacker lose more posture\n");
    printf("parry : prevents taking damage from an eventual attack, inflicting posture damage to the attacker\n");
    printf("focus : regenerates posture\n");
    printf("\n");
    printf(BOLD "Mechanics :\n" RESET);
    printf("posture : once it reaches 0, you skip a turn. It regenerates a bit every turn, but you get more by using the focus action\n");
    printf("health : once it reaches 0, you lose\n");
}

void print_samurai_health(samurai samurai)
{
    int i = 0;
    printf(BOLD "HEALTH\n" RESET BOLD_RED);
    while(i++ < samurai.health)
        printf("@");
    printf(RESET "\n");
}

void print_samurai_posture(samurai samurai)
{
    int size = 40;
    int perc = samurai.posture * size / samurai.max_posture;
    int i = 0;
    printf(BOLD "POSTURE" RESET "\n[" BOLD_YELLOW);
    while(i < size)
    {
        if(i < perc)
            printf("#");
        else
            printf(" ");
        i++;
    }
    printf(RESET "]\n");
}

void print_samurai_stats(samurai samurai)
{
    printf("------------------------------------------\n%s\n", samurai.name);
    print_samurai_health(samurai);
    print_samurai_posture(samurai);
    printf("------------------------------------------\n");
}

void print_samurais(samurai player, samurai opponent)
{
    int right_wall = 32 - player.x - opponent.x;
    printf(" ________________________________________\n");
    printf("|%*s" PLAYER_COLOR " ^   " RESET "%*s" OPPONENT_COLOR " ^ " RESET "%*s|\n", player.x, "", opponent.x, "", right_wall, "");
    printf("|%*s" PLAYER_COLOR " O   " RESET "%*s" OPPONENT_COLOR " O " RESET "%*s|\n", player.x, "", opponent.x, "", right_wall, "");
    printf("|%*s" PLAYER_COLOR "/|\\/" RESET "%*s" OPPONENT_COLOR "\\/|\\" RESET "%*s|\n", player.x, "", opponent.x, "", right_wall, "");
    printf("|%*s" PLAYER_COLOR "/ \\ " RESET "%*s" OPPONENT_COLOR " / \\" RESET "%*s|\n", player.x, "", opponent.x, "", right_wall, "");
    printf("==========================================\n");
}

void print_controls()
{
    printf("\na: move left\td: move right\nw: attack\ts: parry\nf: focus\th: show help\n");
}