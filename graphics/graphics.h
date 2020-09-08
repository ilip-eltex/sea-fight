#ifndef GRAPHICS
#define GRAPHICS

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdint.h>


WINDOW  *main_wnd,      // main 50x35 application window 
        *user_wnd,      // user ships window
        *partner_wnd,   // partner ships window
        *info_wnd;      // information window

char wnd_title[16], wnd_status[11];

void wndTitle ();
void wndStatus ();
int initWnd (); // checks terminal parameters (not less 70x50), calls initscr()  
int delWnd ();
#endif
