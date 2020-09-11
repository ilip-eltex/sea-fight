#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef enum data_val
{
/* -10 */	FAIL = -10,				// Invalid data
/* -9 */CONTINUE,			// means that previous action was successfull
/* -8 */HALT,				// force stop due to partner's disconnect or another
/* -7 */TEST_CONNECT,		// for checking connection
/* -6 */TEST_CONNECT_BACK,	// answer for previous			
/* -5 */SEND_MAP,  		// next data transfer will be map
/* -4 */WIN,				// you win
/* -3 */LOSE,				// you lose
/* -2 */WAIT_MAP,
/* -1 */START_GAME,
/* NULL do not use */
	SHOT = 'x',				// client's request for choosen cell. Also sends for player as enemy's move
	HIT = '*',				// shot was successful
	WET = '.',				// shot wasn't successful
	SEA = '~',
	BOAT = 'B',
	NONE
}data_val_t;

typedef struct event
{
	int16_t x;
	int16_t y;
	data_val_t data;
} event_t;

char client_ip[16], server_ip[16];

uint16_t client_port, server_port;

int srv_ready;
int serv_ready;
int initServer;

char user_map[15][10], partner_map[15][10]; 

#endif
