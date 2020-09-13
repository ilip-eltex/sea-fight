// netmanager.c

#include "netmanager.h"


const char red[] = "\e[31",
		   green[] = "\e[32",
	 	   color_null[] = "\e[0m";//,
//		   FAILED[] = "" + red + "FAILED" + color_null;

char err[255];

//типо тут все структурки объявить и пользовать

int initSocket(char _ip[16], uint16_t _port, connect_t *con)
{
	int status = 0;
	data_val_t sock_t = con->local_sock_fd;
	con->local_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	printf ("initSocket(): start with (%s:%d)\n", _ip, _port);
	if(  con->local_sock_fd < 0 )
	{
#ifdef DEBUG
		sprintf(err, "socket init FAILED!\n");
		perror( err );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		sprintf(err, "socket init SUCCES\n");
		printf(err);
	}
#endif
	if (sock_t == SHOT)
		printf ("initSocket(): Working as client\n");
	if (sock_t == SERVER)
	{
	con->local_addr.sin_family = AF_INET;
	con->local_addr.sin_port = htons(_port);
	con->local_addr.sin_addr.s_addr = inet_addr(_ip);
	}
	if( sock_t == SERVER){
			status = bind(con->local_sock_fd, (struct sockaddr*)&con->local_addr, sizeof(con->local_addr));
		if( status < 0 )
		{
	#ifdef DEBUG
			sprintf(err, "bind socket is FAILED!\n");
			perror( err );
	#endif
			return errno;	
		}
	#ifdef DEBUG
		else {
			sprintf(err, "socket bind is SUCCES\n");
			printf(err);
		}
	#endif
	}
	return status;	
}

int connectToServer(char _ip[16], uint16_t _port, connect_t *con)
{
	int status = 0;

	if( con->remote_sock_fd == NULL)
		con->remote_sock_fd = (int*) malloc( sizeof(int));
    
	if( con->remote_addr == NULL)
		con->remote_addr = (struct sockaddr_in*) malloc( sizeof( struct sockaddr_in));
		
	(con->remote_addr)->sin_family = AF_INET;
	(con->remote_addr)->sin_port = htons(_port);
	(con->remote_addr)->sin_addr.s_addr = inet_addr(_ip);
	status = connect (con->local_sock_fd, 
        (struct sockaddr_in*)con->remote_addr, sizeof(*(con->remote_addr)));
	
	if( status < 0 )
		perror("connectToServer()"); //memset((char *) &con->remote_addr, 0, sizeof(con->remote_addr));
		

	return status;	
}

/***
 * @reference:
 	if (
	event_t your_event = {
		.x = 5, //example
		.y = 5,   //example
		char = 'x' //example
	}
	 is event for / from User

	if (
	event_t your_event = {
		.x = FAIL, // then 
		.y = 5,   // other fields
		char = 'x' // does not matter
	}
	 it is technical event
***/
int sendEvent( int remote_fd, event_t* e, struct sockaddr_in *remote_addr)
{
	int status = 0;

	status = sendto(remote_fd,(void*)e, sizeof(e), MSG_DONTWAIT,
					(struct sockaddr*)&remote_addr, 
					sizeof(remote_addr) );	
	if(status < 0)
	{
#ifdef DEBUG
		//sprintf(err, "send event is %sFAILED%s!\n", red, color_null);
		perror( "sendEvent failed\n" );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		//sprintf(err, "send event is %sSUCCESFULLY%s sent, wait answer...\n", green, color_null);
		printf("Event sent, wait answer..\n");
	}
#endif

	return status;
}

int recvEvent(int remote_fd, event_t* e, struct sockaddr_in *remote_addr)
{
	int status = 0;

	status = recvfrom(remote_fd, &e, sizeof(e), MSG_WAITALL,
	 (struct sockaddr*)&remote_addr, sizeof(remote_addr));
	if(status < 0)
	{
#ifdef DEBUG
		//sprintf(err, "Event is not recived %sFAILED%s!\n", red, color_null);
		perror( "Event isn't recived\n");
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		//sprintf(err, "Event is recived %sSUCCESFULLY%s\n", green, color_null);
		printf("Event recived\n");
	}
#endif
	
	return status;
}

int sendMap(int remote_fd, char* map, struct sockaddr_in *remote_addr)
{
	int status = 0;
	status = sendto(remote_fd, map, sizeof(map), MSG_DONTWAIT,
					(struct sockaddr*)&remote_addr, 
					sizeof(remote_addr) );	
	if(status < 0)
	{
#ifdef DEBUG
		//sprintf(err, "send map is %sFAILED%s!\n", red, color_null);
		perror( "sendMap failed\n" );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		//sprintf(err, "send map is %sSUCCESFULLY%s sent, wait answer...\n", green, color_null);
		printf("Map send, wait answer...\n");
	}
#endif

	return status;
}

int waitMap(int remote_fd, char** map, struct sockaddr_in *remote_addr)
{
	int status = 0;

	status = recvfrom(remote_fd, &map, sizeof(map), MSG_WAITALL,
	 (struct sockaddr*)&remote_addr, sizeof(remote_addr));
	if(status < 0)
	{
#ifdef DEBUG
		//sprintf(err, "Map is not recived %sFAILED%s!\n", red, color_null);
		perror( "Map isn't recived\n" );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		//sprintf(err, "Map is recived %sSUCCESFULLY%s \n", green, color_null);
		printf ("Map recived\n");
	}
#endif
	
	return status;
}

int sendConnectionTest(int remote_fd, struct sockaddr_in *remote_addr)
{
	int status = 0;
	event_t test_connection = {
		 		.x = -1,
		 		.y = -1,
				.data = TEST_CONNECT
		 };


	status = sendEvent(remote_fd, &test_connection, remote_addr);
	if(status < 0)
	{
#ifdef DEBUG
		//sprintf(err, "connection test is %sFAILED%s!\n", red, color_null);
		perror( "sendConnectionTest failed\n" );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		//sprintf(err, "connection test is SUCCES sent, wait answer...\n");
		printf("sendConnectionTest done\n");
	}
#endif

	status = recvEvent(remote_fd, &test_connection, remote_addr);
	
	if( test_connection.x != TEST_CONNECT_BACK )
	{
#ifdef DEBUG
		//sprintf(err, "connection test answer \
					  is not modified FAILED!\n");
		perror( "sendConnectionTest answer (TEST_CONNECT_BACK) is worth\n");
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		sprintf(err, "connection test is SUCCES sent, wait answer...\n");
		printf(err);
	}
#endif
	
	return status;
}


int acceptConnection(int local_fd, int *remote_fd, struct sockaddr_in *remote_addr)
{
	int status = 0;
	char buf[255];

		*remote_fd = accept(local_fd, 
			(struct sockaddr_in*)&remote_addr, 
			sizeof(remote_addr));
	
		if( remote_fd < 0)
		{
#ifdef DEBUG
			sprintf(err, "accepting clieten is FAILED!\n");
			perror( err );
#endif
			return errno;
		}
#ifdef DEBUG
		else {
			sprintf(err, "accepting clietуn is SUCCESFULLY sent, wait answer...\n");
			printf(err);
		}
#endif
	return status;	
}
