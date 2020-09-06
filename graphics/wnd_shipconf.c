/*
	Body of ship config window

Errors:
1: Map is already full

*/
#include "wnd_shipconf.h"

int term_x=15, term_y=10;


int wndShipconf (char ** map)
{
	if (map != NULL)
		return 1;
	
	printw ("Edit map\n");
	WINDOW *win = newwin (term_y, term_x, 6, 6);
	      // *win2 = newwin (term_y, term_x, 6, term_x+10);
	/*
	wmove (win, 1, 1);
	wprintw (win, "A");
	wmove (win2, 1, 1);
	wprintw (win2, "B");
	*/
	char res[term_x][term_y];
	memset (res, '~', term_y * term_x);
	for (int line=0; line < term_y; line++)
		for (int col=0; col < term_x; col++)
		{
			wmove (win, line, col);
			wprintw (win, "%c", res[line][col]);
		}
	
	/*for (int row=0; row < term_y; row++)
                for (int col=0; col < term_x; col++)
                {
                        wmove (win2, row, col);
                        wprintw (win2, "%c", res[row][col]);
                }
	*/
	refresh ();
	wrefresh (win);
	//wrefresh (win2);
	
	wgetch (win);
	
	delwin (win);
	//delwin (win2);
	endwin ();
	
	return 0;
}
