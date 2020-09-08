#ifndef SEA-FIGHT_GAME_H
#define SEA-FIGHT_GAME_H

#include "types.h"

typedef struct user
{
	uint16_t port;
	char ip[16];
	char *map;
}user_t;

typedef struct sea_fight
{
	char **map; // char** malloc ( sizeof(char*)* 2 );
		// char* malloc( sizeof(char) * ( 10 * 10 ) ); // address of cell is map[playerNum][ x + 1 * y]
	int player1; // 
	int player2;
}game_t;

int claculateShipPoints(game_t *fight, char **map, uint16_t player_num );
int calculatShot(game_t *fight, char **map, uint16_t player_num );
#endif
