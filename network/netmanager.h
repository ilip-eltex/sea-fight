// netmanager.h

#ifndef NETMANAGER_H
#define NETMANAGER_H

#include "../types.h"

int initSocket(char _ip[16], uint8_t _port);
int connectToServer(char _ip[16], uint8_t _port);

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
int sendEvent(event_t* e);
int sendMap(char* map);
int sendConnectionTest();

#endif
