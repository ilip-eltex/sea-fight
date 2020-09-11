#include "server.h"

#include "types.h"
#include "network/netmanager.h"

#include <stdarg.h>

int initServer(char **arg)
{
	int status = 0;

	int num_args = 2;
	va_list ap;
	char *ip;
	uint16_t port;
	va_start(ap, *arg);
	while( *arg ){
		switch( *arg ){
			case 'a':
				ip = va_arg(arg, char*);
			break;
			case 'p':
				port = va_arg(arg, int);
			break;
			default:
				perror("initServer()::bad parameter");
			break;
		}
	}
	va_end(ap);
	
	connect_t *on_serv = ( connect_t *) malloc( sizeof( connect_t ) );
	memset( on_serv, 0, sizeof(connect_t));
	status = initSocket( ip, port, on_serv);
	listen( on_serv->local_sock_fd, 2);
	
	on_serv->remote_sock_fd = ( int *) malloc( sizeof(int) * 2);


	event_t *game_event = (event_t*) malloc( sizeof(event_t) );
	
	status = waitEvent( game_event, on_serv);

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
    user_t *token = palyers[0];
	while( event != NULL )
    {
	
		int i = 0;
		switch( event )
		{
			case ACCEPT_CONNECT:
				if( users_count <= 1 )
                {
				    status = acceptConnection(serv_connect->local_sock_fd
											 , &serv_connect->remote_sock_fd[users_count]
                                             , &serv_connect->remote_addr[users_count]
											 );
					players[users_count]->fd = serv_connect->remote_sock_fd[users_count];
                    event = TEST_CONNECT;
                    users_count++; 
				}
                else{
					event = START_GAME;    
                }				
			break;
			case TEST_CONNECT:
				if( users_count <= 1 )
				{
				    status = sendConnectionTest(serv_connect->remote_sock_fd[users_count]
											   , serv_connect->remote_addr[users_count]);
					event = ACCEPT_CONNECT;
				}
				else{
					event = WAIT_MAP;
				}
			break;
			case SEND_MAP:  	
			case WAIT_MAP:
				if( users_count >= 0 )
				{
					status = sendEvent( serv_connect->remote_sock_fd[users_count]
									  , e->data = WAIT_MAP
									  , serv_connect->remote_addr[users_count]);

					status = waitMap(serv_connect->remote_sock_fd[users_count]
									, &players[users_count].map
									, serv_connect->remote_addr[users_count]);
					calculateShipPoints( players[users_count] );
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
									  , serv_connect->remote_addr[users_count]);
			case CONTINUE: 			// means that previous action was successfull
				if( users_count >= 0 && users_count <= 1 )
				{
					if( players[users_count]->hp == 0 ){
						event = LOSE;
						e->data = event;
						break;
					}

					status = waitEvent( serv_connect->remote_sock_fd[users_count]
									  , &e
									  , serv_connect->remote_addr[users_count]);
					
					event = e->data;
				}
			break;
			case FAIL:
				
			case HALT:				// force stop due to partner's disconnect or another
			
			break;		
			case SHOT:				// client's request for choosen cell
				if( users_count >= 0 && users_count <= 1 )
				{
					event = calculateShot( players[users_count], e->x, e->y);
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
									, serv_connect->remote_addr[0]);
				status = sendEvent( serv_connect->remote_sock_fd[1]
									, e
									, serv_connect->remote_addr[1]);
				event = CONTINUE;				
			break;
			case LOSE:				// you lose
				status = sendEvent( serv_connect->remote_sock_fd[users_count]
									, e
									, serv_connect->remote_addr[users_count]);
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
									, serv_connect->remote_addr[users_count]);

			break;
			default:
			break;
        }
            
	}
}


