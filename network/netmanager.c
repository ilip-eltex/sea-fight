// netmanager.c

#include "netmanager.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>

const char red[] = "\e[31",
		   green[] = "\e[32",
	 	   color_null[] = "\e[0m";//,
//		   FAILED[] = "" + red + "FAILED" + color_null;

char err[255];

//типо тут все структурки объявить и пользовать

int initSocket(char _ip[16], uint8_t _port, connect_t *con)
{
	int status = 0;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(  sock_fd < 0 )
	{
#ifdef DEBUG
		sprintf(err, "socket init %sFAILED%s!\n", red, color_null);
		perror( err );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		sprintf(err, "socket init %sSUCCES%s\n", green, color_null);
		printf(err);
	}
#endif

	con.local_addr.sin_family = AF_INET;
	con.local_addr.sin_port = htons(_port);
	con.local_addr.sin_addr.s_addr = inet_addr(_ip);


	status = bind(sock_fd, (struct sockaddr*)&con.local_addr, sizeof(con.local_addr));
	if( status < 0 )
	{
#ifdef DEBUG
		sprintf(err, "bind socket is %sFAILED%s!\n", red, color_null);
		perror( err );
#endif
		return errno;	
	}
#ifdef DEBUG
	else {
		sprintf(err, "socket bind is %sSUCCES%s\n", green, color_null);
		printf(err);
	}
#endif

	return status;	
}

int connectToServer(char _ip[16], uint8_t _port, connect_t *con)
{
	int status = 0;

	con.remote_addr.sin_family = AF_INET;
	con.remote_addr.sin_port = htons(_port);
	con.remote_addr.sin_addr.s_addr = inet_addr(_ip);
	status = sendConnectionTest(con.remote_addr);
	
	if( status < 0 )
		memset((char *) &con.remote_addr, 0, sizeof(con.remote_addr));
		

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
int sendEvent(event_t* e, struct sockaddr_in *remote_addr, uint16_t sock_fd)
{
	int status = 0;

	status = sendto(sock_fd,(void*)e, sizeof(e), MSG_DONTWAIT,
					(struct sockaddr*)&remote_addr, 
					sizeof(remote_addr) );	
	if(status < 0)
	{
#ifdef DEBUG
		sprintf(err, "send event is %sFAILED%s!\n", red, color_null);
		perror( err );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		sprintf(err, "send event is %sSUCCESFULLY%s sent, wait answer...\n", green, color_null);
		printf(err);
	}
#endif

	return status;
}

int recvEvent(event_t* e, struct sockaddr_in *remote_addr, uint16_t sock_fd)
{
	int status = 0;

	status = recvfrom(sock_fd, &e, sizeof(e), MSG_WAITALL,
	 (struct sockaddr*)&remote_addr, sizeof(remote_addr));
	if(status < 0)
	{
#ifdef DEBUG
		sprintf(err, "Event is not recived %sFAILED%s!\n", red, color_null);
		perror( err );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		sprintf(err, "Event is recived %sSUCCESFULLY%s sent, wait answer...\n", green, color_null);
		printf(err);
	}
#endif
	
	return status;
}

int sendMap(char* map, struct sockaddr_in *remote_addr, uint16_t sock_fd)
{
	int status = 0;
	status = sendto(sock_fd, map, sizeof(map), 	
					(struct sockaddr*)&remote_addr, 
					sizeof(remote_addr) );	
	if(status < 0)
	{
#ifdef DEBUG
		sprintf(err, "send map is %sFAILED%s!\n", red, color_null);
		perror( err );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		sprintf(err, "send map is %sSUCCESFULLY%s sent, wait answer...\n", green, color_null);
		printf(err);
	}
#endif

	return status;
}

int sendConnectionTest(int remote_fd, struct sockaddr_in *remote_addr)
{
	int status = 0;
	event_t test_connection = {
		 		.x = TEST_CONNECT,
		 		.y = TEST_CONNECT,
				.data = (char*) malloc( sizeof(char) )
		 };

		 test_connection.data = TEST_CONNECT;

	status = sendEvent(&test_connection, remote_addr, remote_fd);
	if(status < 0)
	{
#ifdef DEBUG
		sprintf(err, "connection test is %sFAILED%s!\n", red, color_null);
		perror( err );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		sprintf(err, "connection test is %sSUCCES%s sent, wait answer...\n", green, color_null);
		printf(err);
	}
#endif
	free(test_connection.data);
	status = recvEvent(&test_connection);
	
	if( test_connection.x != TEST_CONNECT_BACK )
	{
#ifdef DEBUG
		sprintf(err, "connection test answer \
					  is not modified %sFAILED%s!\n", red, color_null);
		perror( err );
#endif
		return errno;
	}
#ifdef DEBUG
	else {
		sprintf(err, "connection test is %sSUCCES%s sent, wait answer...\n", green, color_null);
		printf(err);
	}
#endif
	
	return status;
}


int acceptConnection( int remote_fd, struct sockaddr_in *remote_addr, int local_fd)
{
	int status = 0;
	char buf[255];

		remote_fd = accept(serv_connect->local_sock_fd, 
			(struct sockaddr_in*)&serv_connect->remote_addr[i], 
			sizeof( serv_connect->remote_addr[i]));
	
		if( remote_fd < 0)
		{
#ifdef DEBUG
			sprintf(err, "accepting clieten %d is %sFAILED%s!\n", i, red, color_null);
			perror( err );
#endif
			return errno;
		}
#ifdef DEBUG
		else {
			sprintf(err, "accepting clietуn %d is %sSUCCESFULLY%s sent, wait answer...\n", i, green, color_null);
			printf(err);
		}
#endif


	

	return status;	
}
