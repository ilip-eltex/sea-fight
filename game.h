#ifndef SEA_FIGHT_GAME_H
#define SEA_FIGHT_GAME_H

#include "types.h"

typedef struct user{
int fd; //файловый дескриптор юзера
uint8_t hp; //кол-во лодок на поле
char map[15][10];
}user_t;

int calculateShipPoints(user_t *player);
int calculateShot(user_t *player, uint16_t x, uint16_t y);
#endif
