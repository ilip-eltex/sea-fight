// netmanager.h

#ifndef NETMANAGER_H
#define NETMANAGER_H

#include "../types.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>

typedef enum sock_type
{
	SERVER,
	CLIENT
}sock_type_t;


typedef struct connect
{
	int local_sock_fd;
	int *remote_sock_fd;
	struct sockaddr_in local_addr;
	struct sockaddr_in *remote_addr; // min 2 players;
}connect_t;

///////////\remote_fd/////\msg////////\size/////
// send(int sockfd, const void *buf, size_t len, int flags);
//      
// sendto(int sockfd, const void *buf, size_t len, int flags,
//                    const struct sockaddr *dest_addr, socklen_t addrlen);
////////////\local_fd/////
// listen(int sockfd, int backlog);
/////////\remote_fd//////\msg////////////
// recv(int sockfd, void *buf, size_t len, int flags);
//
// recvfrom(int sockfd, void *buf, size_t len, int flags,
//          struct sockaddr *src_addr, socklen_t *addrlen);
//
int initSocket(char _ip[16], uint16_t _port, connect_t *con);
int connectToServer(char _ip[16], uint16_t _port, connect_t *con);

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
int sendEvent( int remote_fd, event_t* e, struct sockaddr_in* remote_addr);
int recvEvent(int remote_fd, event_t* e, struct sockaddr_in *remote_addr);
int sendMap(int remote_fd, char* map, struct sockaddr_in *remote_addr);
int waitMap(int remote_fd, char** map, struct sockaddr_in *remote_addr);
int sendConnectionTest(int remote_fd, struct sockaddr_in *remote_addr);
int acceptConnection(int local_fd, int *remote_fd, struct sockaddr_in *remote_addr);

#endif
