#define DEBUG


#include "../types.h"
#include "../network/netmanager.h"

int main (int arg_q, char **args)
{
	initSocket( "127.0.0.1", 3333 );

 	char map[] =
	        "   xxx xxx  xx xxx \n\
			     x  x   x    x  \n\
			     x  xxx  x   x  \n\
			     x  x     x  x  \n\
			     x  xxx xx   x \n";
		

	while(1){
		sendMap(map);
	}
	return 0;
}
