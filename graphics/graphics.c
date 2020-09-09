#include "graphics.h"

void wndTitle ()
{
	move (4, 18);
	printw ("%s", wnd_title);	
}

void wndStatus ()
{
	move (3, 2);
	printw ("%s", wnd_status);
}

void update ()
{
	//wrefresh (main_wnd);
	wrefresh (user_wnd);
	wrefresh (partner_wnd);
	wrefresh (info_wnd);
	doupdate ();
}

int initWnd ()
{
	if ( !initscr() )
		return 1;
	// here checking terminal sizes
	/*main_wnd = newwin (35, 50, 1, 1);
	
	if (main_wnd == NULL)
		return 2; */
	
	user_wnd = newwin (10, 15, 6, 6);
	if (user_wnd == NULL)
		return 3;
	
	partner_wnd = newwin (10, 15, 6, 25);
	if (partner_wnd == NULL)
		return 4;
	
	info_wnd = newwin (13, 19, 19, 2);	
	if (info_wnd == NULL)
		return 5;	

	move (2, 2);
	printw ("STATUS:");
	memset (wnd_title, '\0', 16);
	memset (wnd_status, '\0', 11);
	refresh ();		
	
	return 0;
}

int delWnd ()
{
	delwin (info_wnd);
	delwin (user_wnd);
	delwin (partner_wnd);
	//delwin (main_wnd);
	endwin ();
}
