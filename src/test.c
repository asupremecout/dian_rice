#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
 
int main()
{
	initscr();
	move(30,15);
	printw("%s","hello world");
	refresh();
	sleep(10);
	endwin();
	exit(EXIT_SUCCESS);
}