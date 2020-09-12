#ifndef SERVER_H
#define SERVER_H

#include "types.h"
#include "game.h"
#include "network/netmanager.h"

typedef struct assoc_event_action
{
	event_t *event;
	void (**action)();
}assoc_event_action_t;

int initServer(char *arg);
int waitEvent(event_t *e, connect_t *serv_connect);
/*
int onShot(event_t *e );
char* getMapFromUser( char *userMap, char* sevMap);
int calculateShot(event_t *e);
int doAction( event_t *e );
int addAction( event_t *e, void (*action)());
int removAction( event_t *e, int num);
*/

#endif
 
