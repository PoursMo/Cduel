#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>

#include "samurai.h"
#include "colors.h"

void print_help();
void print_samurai_health(samurai samurai);
void print_samurai_posture(samurai samurai);
void print_samurai_stats(samurai samurai);
void print_samurais(samurai player, samurai opponent);
void print_controls();


#endif