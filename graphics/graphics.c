#include "graphics.h"

void wndTitle ()
{
	wmove (main_wnd, 4, 18);
	wprintw (main_wnd, "%s", wnd_title);	
}

void wndStatus ()
{
	wmove (main_wnd, 3, 2);
	wprintw (main_wnd, "%s", wnd_status);
}

int initWnd ()
{
	if ( !initscr() )
		return 1;
	// here checking terminal sizes
	main_wnd = newwin (35, 50, 1, 1);
	
	user_wnd = derwin (main_wnd, 10, 15, 6, 6);
	partner_wnd = derwin (main_wnd, 10, 15, 6, 25);
	
	info_wnd = derwin (main_wnd, 13, 19, 19, 2);	
	
	wmove (main_wnd, 2, 2);
	wprintw (main_wnd, "STATUS:");
	memset (wnd_title, '\0', 16);
	memset (wnd_status, '\0', 11);
	
	if ( user_wnd == NULL || partner_wnd == NULL || info_wnd == NULL || main_wnd == NULL )
		return 2;
	
	return 0;
}

int delWnd ()
{
	delwin (info_wnd);
	delwin (user_wnd);
	delwin (partner_wnd);
	delwin (main_wnd);
	endwin ();
}
