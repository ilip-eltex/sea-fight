// includes
#include "types.h"


int main (int arg_q, char **args)
{
	int a = FAIL;				// Invalid data
	 a =CONTINUE;			// means that previous action was successfull
	 a =HALT;				// force stop due to partner's disconnect or another
	 a =TEST_CONNECT;		// for checking connection
	 a =TEST_CONNECT_BACK;	// answer for previous			
	 a =SEND_MAP;  			// next data transfer will be map
	 a =SHOT;				// client's request for choosen cell
	 a =HIT;				// shot was successful
	 a =WET;				// shot wasn't successful
	 a =WIN;				// you win
	 a =LOSE; 				// you lose

// parsing arguments
	
	// menu window
	
	// condition: if server choosen than run it and wait
	// else connect to server than window wait other gamer to connect 
	
	// game field config window
	// window wait for other gamer
	
	// window game
	
	// window stat
	// goto menu
	return 0;
}
