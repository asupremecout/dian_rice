#ifndef INPUT_H
#define INPUT_H

#define MAX_INPUT_LENGTH 1024
#include <ncurses.h>

int get_input(WINDOW *input_win, WINDOW *chat_win);

#endif