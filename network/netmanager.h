// netmanager.h

#ifndef NETMANAGER_H
#define NETMANAGER_H

#include "../types.h"


typedef struct connect
{
	uint16_t local_sock_fd;
	int *remote_sock_fd;
	struct sockaddr_in local_addr;
	struct sockaddr_in *remote_addr; // min 2 players;
}connect_t;

int initSocket(char _ip[16], uint8_t _port, connect_t *con);
int connectToServer(char _ip[16], uint8_t _port, connect_t *con);

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
int sendEvent(event_t* e, struct sockaddr_in *remote_addr, uint16_t sock_fd);
int sendMap(char* map, struct sockaddr_in *remote_addr);
int sendConnectionTest(struct sockaddr_in *remote_addr);
int waitConnection(struct sockaddr_in *remote_addr);
int recvEvent(event_t* e, struct sockaddr_in *remote_addr);

#endif
