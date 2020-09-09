// includes
#include "types.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define cls() printf("\e[2J\e[H")

event_t parseCoords (char *s) // in 'XY' format, where Y is [0..9]; X is [A..O]
{
	event_t result = {-1, -1, FAIL};
	if (s == NULL)
		return result; 

	// Checking X for validity
	if ( !isalpha (s[0]) )
		return result;
	if ( islower (s[0]) )
		if ( toupper (s[0]) != s[0] )
			s[0] = toupper (s[0]);
		else return result;
	if ( !( (s[0] >= 'A') && (s[0] <= 'O') ) )
		return result;
	
 	// Checking Y for validity 		
	if ( !isdigit (s[1]) )
		return result;
	
	// Enter parsed data
	result.x = s[0] - 'A';
	result.y = s[1] - '0';
	result.data = CONTINUE;
	return result;	
}

void printBothMap ()
{
	enum WICH
	{
		USER=0,
		PARTNER=1
	};
	enum WICH wich;
	int x=0, y=0;
	printf ("\n            YOU         ");
	printf ("                     ENEMY\n\n");
	printf ("  A B C D E F G H I J K L M N O      A B C D E F G H I J K L M N O\n0 ");
	while ( y < 10 )
	{
		switch (wich)
		{
			case 0: printf ("%c ", user_map[x++][y]); break;
			case 1: printf ("%c ", partner_map[x++][y]);
		}
		if ( (x == 15) && (wich == USER) )
		{
			x = 0;
			wich = PARTNER;
			printf ("   %d ", y);
			
		} else if ( (x == 15) && (wich == PARTNER) )
		{
			x = 0;
			wich = USER;
			y++;
			if (y !=10)
				printf ("\n%d ", y);
			else printf ("\n\n");
		}	
	}
}

void printUserMap ()
{
	//printf ("\n            YOU         \n\n");
	printf ("  A B C D E F G H I J K L M N O\n");
	for (int y=0; y<10; y++)
	{
		printf ("%d ", y);
		for (int x=0; x<15; x++)
		{
			printf ("%c ", user_map[x][y]); 
		}
		printf ("\n");	
	}
}


int main (int arg_q, char **args)
{
	// choose action
	int mode; // 1 for start session; 2 for connect to active one
	cls();
	printf ("Welcome to Marine Fight!\nPlease choose action:\n(1) Create game\n(2) Connect to game\n(0) Quit\n\n>> ");
	scanf ("%d", &mode);
	if (mode == 0)
		return 0;

	// enter user ip and port
	printf ("\n\nPlease enter your IP and port (IP as 255.255.255.255):\n>> ");
	scanf ("%s %d", client_ip, &client_port);
	cls();
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
	
	cls();
	// ships configurate 
	memset (user_map, '~', 150);	
	memset (partner_map, '~', 150);
	const char *msg_buf = malloc (sizeof (char) * 128);
	char *msg = NULL;
	enum orientation_t
        {
        	HORIZONTAL,
        	VERTICAL
        };
        enum orientation_t orientation=VERTICAL;
        int senior=1, junior=3, middle=2, x, y;
	char cmd[12];
	
	enum ship_t 
	{
		SENIOR,
		MIDDLE,
		JUNIOR
	};
	enum ship_t current_ship = SENIOR;
	event_t parsed_coors;
	while (1)
	{
		cls();
		printUserMap ();
		printf ("\nYou are editing your ships map. Type next commands to configurate:\n");
		printf ("'orientation':      to switch current choosen ship orientation;\n");
		printf ("'reset':            to clear map and begin again;\n");
		printf ("'continue':         to finish configurate;\n");
		printf ("'exit':             to quit app;\n");
		printf ("'s' or 'm' or 'j':  to choose current ship;\n");
		printf ("'XY':               to place choosen ship into coordinates. X is [A..O], Y is [0..0];\n");
		if (msg != NULL)
		{
			printf ("\nError: %s\n", msg);
			msg = NULL;
		}
		printf ("\n\nInfo:\n");
		printf ("(S)enior ship - takes 5 cells. Available - %d\n", senior);
		printf ("(M)iddle ships - takes 3 cells. Available - %d\n", middle);
		printf ("(J)unior ships - takes 2 cells. Available - %d\n", junior);
		printf ("Orientation - %s\n", orientation==HORIZONTAL ? "horizontal" : "vertical");
		printf ("Current ship - ");
		switch (current_ship)
		{
			case SENIOR: printf ("senior"); break;
			case MIDDLE: printf ("middle"); break;
			case JUNIOR: printf ("junior");  
		}
		printf ("\n\n>> "); 
		scanf ("%s", cmd);
		cmd[11] = '\0';
		
		if ( !strcmp (cmd, "exit") )
			return 0;
		
		else if ( !strcmp (cmd, "reset") )
		{
			memset (user_map, '~', 150);
			senior = 1;
			middle = 2;
			junior = 3;
		}
		
		else if ( !strcmp (cmd, "continue") )
		{
			if ( senior==0 && middle==0 && junior==0 ) 
				break;
			else 
			{
				strcpy (msg_buf, "You cann't continue untill all ships placed\0");
				msg = msg_buf;
			}
		}
		
		else if ( !strcmp (cmd, "orientation") )
		{
			if (orientation == HORIZONTAL)
				orientation = VERTICAL;
			else
				orientation = HORIZONTAL;
		}
		
		else if ( cmd[0] == 's' || cmd[0] == 'm' || cmd[0] == 'j')
		{
			switch (cmd[0])
			{
				case 's': current_ship = SENIOR; break;
				case 'm': current_ship = MIDDLE; break;
				case 'j': current_ship = JUNIOR;
			}
		} 

		else if ( (parsed_coors = parseCoords (cmd)).data != FAIL ) 
		{
			int pole;
			switch  (orientation)
			{
				case HORIZONTAL: pole = parsed_coors.x; break;
				case VERTICAL: pole = parsed_coors.y;
			}
			int ship_len = 0, *current_ship_ptr=NULL;
			char ship_symbol;
			switch (current_ship)
			{
				case SENIOR: ship_len = 5; ship_symbol = 'S'; current_ship_ptr = &senior; break;
				case MIDDLE: ship_len = 3; ship_symbol = 'M'; current_ship_ptr = &middle; break;
				case JUNIOR: ship_len = 2; ship_symbol = 'J'; current_ship_ptr = &junior;
			}
			if (*current_ship_ptr == 0) 
			{
				strcpy (msg_buf, "All of this ships is already placed. Change the ship type or continue game\0");
				msg = msg_buf;
				continue;
			}
			int lim = (orientation == HORIZONTAL ? 15: 10);
			if ( (pole + ship_len) < lim )
			{
				int busy=0;
				for (int i=pole; i < (pole + ship_len); i++)
					switch (orientation)
                                        {
                                                case HORIZONTAL: 
							if (user_map[i][parsed_coors.y] != '~')
								busy = 1;
							break;
                                                case VERTICAL: 
							if (user_map[parsed_coors.x][i] != '~')
								busy = 1;
                                        }
				if (busy)
				{
					strcpy (msg_buf, "Space already busy\0");
					msg = msg_buf;
					continue;
				}
				for (int i=pole; i < (pole + ship_len); i++)
					switch (orientation)
					{
						case HORIZONTAL: user_map[i][parsed_coors.y] = ship_symbol; break;
						case VERTICAL: user_map[parsed_coors.x][i] = ship_symbol;
					}
				(*current_ship_ptr)--; 
				
			}	
			else
			{
				strcpy (msg_buf, "Choosen ship cann't be placed here due to too long\0");
				msg = msg_buf;
			}
		}
		
		else
		{
			strcpy (msg_buf, "Invalid syntax\0");
			msg = msg_buf;
		}	
	}
		
	// wait for other player
	// game

	return 0;
}
