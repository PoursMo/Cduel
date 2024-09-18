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

void print_samurai_name(samurai samurai)
{
    if(samurai.is_player)
        printf(BLUE);
    else
        printf(MAGENTA);
    printf("%s" RESET, samurai.name);
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
    printf("------------------------------------------\n");
    print_samurai_name(samurai);
    printf("\n");
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

void get_player_name(samurai *player)
{
    char name[32];
    printf("Type in your samurai name (max 32 characters):\n");
    fflush(stdout);
    scanf("%s", name);
    while (getchar() != '\n');
    if(strlen(name) > 32)
    {
        printf("Too many characters\n");
        get_player_name(player);
        return;
    }
    strcpy(player->name, name);
    printf("Your name is ");
    print_samurai_name(*player);
    printf("\n");
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

void flush_getchar()
{
    while(getchar() != '\n');
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
            if(opponent.posture > 0)
                opponent.action = pick_random_action();
            else
                opponent.action = actions.recover;
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