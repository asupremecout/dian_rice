

#include <ncurses.h>
#include <string.h>
#include "input.h"
#include "utils.h"

#include<stdio.h>
#include<ncurses.h>
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include<string.h>
#include<input.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "utils.h"
#include "input.h"

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
        ch = wgetch(input_win) ;

        if (ch == '\n') { 
            buffer[buf_len] = '\0';
            if (buf_len > 0) {
                
                wprintw(chat_win, "%s", buffer);
                wrefresh(chat_win);

                if(buffer[0]!='/'){ 
                    char response[MAX_INPUT_LENGTH] = "429Too many Requests\n,服务器繁忙，请稍后再试\n"; 
                    wprintw(chat_win, "%s", response);
                    wrefresh(chat_win);

                    
                }
                else {
                    char new_response[MAX_INPUT_LENGTH] = "received,successfully:\n ";
                    wprintw(chat_win, "%s", new_response);
                    wrefresh(chat_win);

                    char dest1[6];
                    strncpy(dest1, buffer, 5);
                    dest1[5] = '\0';

                    char dest2[7];
                    strncpy(dest2, buffer, 6);
                    dest2[6] = '\0';

                    if(strcmp(dest1, "/read") == 0) {
                        //首先需要把buffer中的/read去掉，剩下的就是文件名以及有可能有的数字了
                        char *filename = buffer + 6; 
                        //判断filename里面有没有空格,有则有数字
                        char *space_str = strchr(filename, ' ');
                        if (space_str != NULL) {
                            *space_str = '\0'; 
                            char *number_str = space_str + 1; //数字部分
                        }
                        FILE *fp = fopen(filename, "r");
                        if (fp == NULL) {
                            wprintw(chat_win, "empty\n");
                            wrefresh(chat_win);
                        } else {
                            // 文件读取
                            char line[MAX_INPUT_LENGTH];
                            while (fgets(line, sizeof(line), fp) != NULL) 
                            {
                                wprintw(chat_win, "%s", line); 
                                wrefresh(chat_win); 
                            }
                            fclose(fp);
                        }

                        return 0;
                    }
                    if(strcmp(dest2, "/write")==0){
                        
                        

                        char *filename = buffer + 7; 
                        //判断filename里面有没有空格,有则有数字
                        char *space_str = strchr(filename, ' ');
                        if (space_str != NULL) {
                            *space_str = '\0'; 
                            //char *number_str = space_str + 1; 
                        }
                        FILE *fp = fopen(filename, "a");//追加
                        
                            // 文件读取
                            char line[MAX_INPUT_LENGTH];
                            while (fgets(line, sizeof(line), fp) != NULL) 
                            {
                                wprintw(chat_win, "%s", line); 
                                wrefresh(chat_win); 
                            }
                            fclose(fp);
                        

                        return 0;
                    }

                }
                
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
        else if (ch == KEY_BACKSPACE|| ch == 127) {  
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
            buffer[buf_len] = ch;
            buf_len++;
            buffer[buf_len] = '\0';
            
            werase(input_win);
            box(input_win, 0, 0);
            mvwprintw(input_win, 1, 1, "> %s", buffer);
            wrefresh(input_win);
        }
    }
}