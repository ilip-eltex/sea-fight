#include "server.h"

#include "types.h"
#include "network/netmanager.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int initServer(char **arg)
{
	int status = 0;

	int num_args = 2;
	char *ip = arg[0];
	
	uint16_t port = atoi( arg[1]);/*
	int opt;
	while ((opt = getopt(num_args, arg, ":a:p:")) != -1) {
		switch (opt) 
		{
			case 'a':
				ip = (char*) malloc( sizeof(char)*strlen(optarg) );
                strcpy( ip, optarg);
                break;
            case 'p':
				port = atoi(optarg);
                break;
			default:  '?'// 
               fprintf(stderr, "Usage: initServer [-a 127.0.0.1] [-p 333] \n" );
               exit(EXIT_FAILURE);
		}
    }	*/
	connect_t *on_serv = ( connect_t *) malloc( sizeof( connect_t ) );
	memset( on_serv, 0, sizeof(connect_t));
	on_serv->local_sock_fd = SERVER;
	status = initSocket( ip, port, on_serv);
	listen( on_serv->local_sock_fd, 2);
	
	on_serv->remote_sock_fd = ( int *) malloc( sizeof(int) * 2);
	on_serv->remote_addr = (struct sockaddr_in*) malloc( sizeof( struct sockaddr_in) * 2);

	event_t *game_event = (event_t*) malloc( sizeof(event_t) );
	
	status = waitEvent( game_event, on_serv);
	
	close( on_serv->local_sock_fd );
	for( int i = 0; i < 1; i++)
	{
		close(on_serv->remote_sock_fd[i]);

	}
	if( on_serv->remote_addr != NULL )
	{
		free(on_serv->remote_addr);
	}

	if( on_serv != NULL )
		free(on_serv);

	return status;	
}

int waitEvent(event_t *e, connect_t* serv_connect)
{
	int status = 0;
	char err[255];
	int i = 0;
	
	uint16_t event = ACCEPT_CONNECT;
	uint16_t users_count = 0;
    user_t *players = (user_t*) malloc( sizeof(user_t) * 2);
	while( event != NULL )
    {
	
		int i = 0;
		switch( event )
		{
			case ACCEPT_CONNECT:
				srv_ready = 1;
				if( users_count <= 1 )
                {
				    status = acceptConnection(serv_connect->local_sock_fd
											 , serv_connect->remote_sock_fd[users_count]
                                             , &serv_connect->remote_addr[users_count]
											 );
					players[users_count].fd = serv_connect->remote_sock_fd[users_count];
                    event = TEST_CONNECT;
                    users_count++; 
				}
                else{
					event = WAIT_MAP;    
                }				
			break;
			case TEST_CONNECT:
				if( users_count <= 1 )
				{
				    status = sendConnectionTest(serv_connect->remote_sock_fd[users_count]
											   , &serv_connect->remote_addr[users_count]);
					event = ACCEPT_CONNECT;
				}
				else{
					event = WAIT_MAP;
					e->data = event;
				}
			break;
			case SEND_MAP:  	
			case WAIT_MAP:
				if( users_count >= 0 )
				{
					status = sendEvent( serv_connect->remote_sock_fd[users_count]
									  , e
									  , &serv_connect->remote_addr[users_count]);

					status = waitMap(serv_connect->remote_sock_fd[users_count]
										, (char**) players[users_count].map
									, &serv_connect->remote_addr[users_count]);
					calculateShipPoints( &players[users_count] );
					users_count--;
					event = WAIT_MAP;
				}
				else{
					event = START_GAME;
					e->data = START_GAME;
					users_count = 0;
				}
			break;
			case START_GAME:
				status = sendEvent( serv_connect->remote_sock_fd[users_count]
									  , e
									  , &serv_connect->remote_addr[users_count]);
			case CONTINUE: 			// means that previous action was successfull
				if( users_count >= 0 && users_count <= 1 )
				{
					if( players[users_count].hp == 0 ){
						event = LOSE;
						e->data = event;
						break;
					}

					status = recvEvent( serv_connect->remote_sock_fd[users_count]
									  , e
									  , &serv_connect->remote_addr[users_count]);
					
					event = e->data;
				}
			break;
			
			break;		
			case SHOT:				// client's request for choosen cell
				if( users_count >= 0 && users_count <= 1 )
				{
					event = calculateShot( &players[users_count], e->x, e->y);
					e->data = event;
				}
			break;
			case WET:				// shot wasn't successful
				if( users_count == 0 )
				{
					users_count = 1;
				}
				else{
					users_count = 0;
				}
			case HIT:				// shot was successful
				status = sendEvent( serv_connect->remote_sock_fd[0]
									, e
									, &serv_connect->remote_addr[0]);
				status = sendEvent( serv_connect->remote_sock_fd[1]
									, e
									, &serv_connect->remote_addr[1]);
				event = CONTINUE;				
			break;
			case LOSE:				// you lose
				status = sendEvent( serv_connect->remote_sock_fd[users_count]
									, e
									, &serv_connect->remote_addr[users_count]);
				if( users_count == 0 )
				{
					users_count = 1;
				}
				else{
					users_count = 0;
				}
				
			case WIN:				// you win
				e->data = WIN;
				status = sendEvent( serv_connect->remote_sock_fd[users_count]
									, e
									, &serv_connect->remote_addr[users_count]);

			break;
			case FAIL:
				if( users_count == 0 )
				{
					users_count = 1;
				}
				else{
					users_count = 0;
				}	
			case HALT:				// force stop due to partner's disconnect or another
			default:
				status = sendEvent( serv_connect->remote_sock_fd[users_count]
									, e
									, &serv_connect->remote_addr[users_count]);
			break;
        }
            
	}
	return 0;
}


