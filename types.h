#include <stdint.h>

enum data_val
{
	FAIL,				// Invalid data
	CONTINUE,			// means that previous action was successfull
	HALT,				// force stop due to partner's disconnect or another
	TEST_CONNECT,		// for checking connection
	TEST_CONNECT_BACK	// answer for previous			
	SEND_MAP,  			// next data transfer will be map
	SHOT,				// client's request for choosen cell
	HIT,				// shot was successful
	WET,				// shot wasn't successful
	WIN,				// you win
	LOSE,				// you lose
};

typedef struct event
{
	int16_t x;
	int16_t y;
	data_val data;
} event_t;

char client_ip[16], server_ip[16];
uint16_t client_port, server_port;

uint16_t term_x, term_y;


