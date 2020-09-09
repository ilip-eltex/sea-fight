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
	SHOT = 'x',				// client's request for choosen cell
	HIT = '*',				// shot was successful
	WET = '.',				// shot wasn't successful
	BOAT = 'B'
}data_val_t;

typedef struct event
{
	int16_t x;
	int16_t y;
	char* data; //data_val_t data;
} event_t;

char client_ip[16], server_ip[16];
uint16_t client_port, server_port;

uint16_t term_x, term_y;

uint8_t main_wnd_col, main_wnd_lines;

#endif

#ifdef DEBUG

/**
 * @status 
 * \ref if status < 0 return FAILED message, else succes message
 * @succesMsg
 * @failedMsg
 *
*/
/*
void inline isSuccesMsg( int16_t status, const char* succesMsg, const char* failedMsg )
{
	char tmpMsg[255] = "
	if( status < 0 )
}
*/
#endif
