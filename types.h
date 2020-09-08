#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef enum data_val
{
	FAIL,				// Invalid data
	CONTINUE,			// means that previous action was successfull
	HALT,				// force stop due to partner's disconnect or another
	TEST_CONNECT,			// for checking connection
	TEST_CONNECT_BACK,		// answer for previous			
	SEND_MAP,  			// next data transfer will be map
	SHOT,				// client's request for choosen cell
	HIT,				// shot was successful
	WET,				// shot wasn't successful
	WIN,				// you win
	LOSE				// you lose
}data_val_t;

typedef struct event
{
	int16_t x;
	int16_t y;
	char* data; //data_val_t data;
} event_t;

char client_ip[16], server_ip[16];

uint16_t client_port, server_port;

int srv_ready;

//uint8_t main_wnd_col, main_wnd_lines;

char user_map[15][10], partner_map[15][10]; 

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
