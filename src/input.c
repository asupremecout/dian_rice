#include <ncurses.h>
#include <string.h>
#include "input.h"
#include "utils.h"

#define MAX_INPUT_LENGTH 1024
static char buffer[MAX_INPUT_LENGTH];
static int buf_len = 0;

int get_input(WINDOW *input_win, WINDOW *chat_win)
{
    int ch;
    buf_len = 0;
    buffer[0] = '\0';
   
    werase(input_win); 
    box(input_win, 0, 0);
    mvwprintw(input_win, 1, 1, "> ");//固定>在这里
    wrefresh(input_win);

    while (1) {
        ch = wgetch(input_win);

        if (ch == '\n') { 
            buffer[buf_len] = '\0';
            if (buf_len > 0) {
                
                wprintw(chat_win, "%s", buffer);
                wrefresh(chat_win);

                
                if (strcmp(buffer, "/exit") == 0) {
                    return 1;  //exit指令推出
                }
            }
            
            buf_len = 0;
            buffer[0] = '\0';
            
            werase(input_win);
            box(input_win, 0, 0);
            mvwprintw(input_win, 1, 1, "> ");
            wrefresh(input_win);
            return 0;
        }
        else if (ch == KEY_BACKSPACE) { 
            if (buf_len > 0) {
                buf_len--;
                buffer[buf_len] = '\0';
            }
            
            werase(input_win);
            box(input_win, 0, 0);
            mvwprintw(input_win, 1, 1, "> %s", buffer);
            wrefresh(input_win);
        }
        else { 
            buffer[buf_len] = (char)ch;
            buf_len++;
            buffer[buf_len] = '\0';
            
            werase(input_win);
            box(input_win, 0, 0);
            mvwprintw(input_win, 1, 1, "> %s", buffer);
            wrefresh(input_win);
        }
    }
}