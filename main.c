// includes
#include "types.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void printBothMap ()
{
	enum WICH
	{
		USER=0,
		PARTNER=1
	};
	enum WICH wich;
	int x=0, y=0;
	printf ("\n      YOU         ");
	printf ("     ENEMY\n");
	while ( y < 10 )
	{
		switch (wich)
		{
			case 0: printf ("%c", user_map[x++][y]); break;
			case 1: printf ("%c", partner_map[x++][y]);
		}
		if ( (x == 15) && (wich == USER) )
		{
			x = 0;
			wich = PARTNER;
			printf ("   ");
			
		} else if ( (x == 15) && (wich == PARTNER) )
		{
			x = 0;
			wich = USER;
			y++;
			printf ("\n");
		}	
	}
}

void printUserMap ()
{
	
}


int main (int arg_q, char **args)
{
	// choose action
	int mode; // 1 for start session; 2 for connect to active one
	printf ("Welcome to Marine Fight!\nPlease choose action:\n(1) Create game\n(2) Connect to game\n(0) Quit\n\n>> ");
	scanf ("%d", &mode);
	if (mode == 0)
		return 0;

	// enter user ip and port
	printf ("\n\nPlease enter your IP and port (IP as 255.255.255.255):\n>> ");
	scanf ("%s %d", client_ip, &client_port);
	
	// if server is choosen then start server thread
	if (mode == 1)
	{
		printf ("\nEnter your IP and server port (IP as 255.255.255.255)\n>> ");
		char **srv_arg = malloc (sizeof(char*) * 2);
		srv_arg[0] = malloc (sizeof(char) * 16);
		srv_arg[1] = malloc (sizeof(char) * 7);
		memset (srv_arg[0], '\0', 16);
		memset (srv_arg[1], '\0', 7);
		scanf ("%s %s", srv_arg[0], srv_arg[1]);
		pthread_t srv;
		srv_ready = 0;
		//pthread_create (&srv, NULL, initServer, (void*) srv_arg); 		!! UNCOMMENT IT
		printf ("Wait for server... ");
		int sec=0;
		while ( !srv_ready )
		{
			sleep (1);
			printf ("\b%d", ++sec);
			if (sec == 30)
				return 0; 
		}
		// connect to server via socket		
	}
	
	// connect to active game
	else if (0) //									!! DELETE CONDITION
	{
		printf ("\nEnter server IP and port (IP as 255.255.255.255)\n>> ");
		scanf ("%s %d", server_ip, &server_port);
		// connect to server via socket
	}
	
	//wait for server command to start ships configure
	
	// ships configurate 
	memset (user_map, '~', 150);	
	memset (partner_map, '~', 150);
	partner_map[5][5] = 'X';
	user_map[10][9] = 'A';
	printBothMap ();
	// wait for other player
	// game

	return 0;
}
