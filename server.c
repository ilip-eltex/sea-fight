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


	event_t *game_event = (evetn_t*) malloc( sizeof(event_t) );
	
	status = wateEvent( game_event, on_serv);

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
											 , &serv_connect->remote_sock_fd
                                             , &serv_connect->remote_addr
											 );
				    status = sendConnectionTest(serv_connect->remote_sock_fd, serv_connect->remote_addr);
                    
                    event = TEST_CONNECT;
                    users_count++; 
				}
                else{
                    
                }
				
			break;
			case TEST_CONNECT:
				e.x = TEST_CONNECT;
				action[0](NULL, NULL, NULL);
				sendEvent( e );
			break;
			case FAIL:
				
			case CONTINUE: 			// means that previous action was successfull
			case HALT:				// force stop due to partner's disconnect or another
			case SEND_MAP:  	
				for(i=0; i < 2; i++){
					getMapFromUser( player[1], map);
				}
			break;		
			case SHOT:				// client's request for choosen cell
			case HIT:				// shot was successful
			case WET:				// shot wasn't successful
			case WIN:				// you win
			case LOSE:				// you lose
				sendEvent(e);
			break;
			default:
				if( e.x >= 0 )
				{
					calculateShot(e);
				}
				sendEvent(e);
			break;
        }
            
	}
}

int calculateShot( event_e *e )
{
	char *map;

	if( map[e.x+1*e.y] == BOAT )
	{
		map[e.x+1*e.y] = HIT;
		return HIT;
	}
	else
	{
		map[e.x+1*e.y] = WET;
		return WET;
	}
	return 0;
}
