#ifndef GRAPHICS
#define GRAPHICS

#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdint.h>

uint8_t user_wnd_x, user_wnd_y;

uint8_t partner_wnd_x, partner_wnd_y;

int initWnd (); // checks terminal parameters (not less 70x50), calls initscr()  

#endif
