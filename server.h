#ifndef SERVER_H
#define SERVER_H

#include "types.h"
#include "network/netmanager.h"

typedef struct assoc_event_action
{
	event_t *event;
	void (**action)();
}assoc_event_action_t;

int initServer(char **arg);
int waitEvent(*e, void (**action)(int x, int y, char *data));

int onShot(event_t *e );
char* getMapFromUser( char *userMap, char* sevMap);
int calculateShot(event_t *e);
int doAction( event_t *e );
int addAction( event_t *e, void (*action)());
int removAction( event_t *e, int num);


#endif
 
