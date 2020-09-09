#ifndef SEA-FIGHT_GAME_H
#define SEA-FIGHT_GAME_H

#include "types.h"

typedef struct user{
int fd; //файловый дескриптор юзера
uint8_t hp; //кол-во лодок на поле
char map[15][10];
}user_t;

int claculateShipPoints(user_t *player);
int calculatShot(user_t *player, uint16_t x, uint16_t y);
#endif