// #include <ncurses.h>
// #include <string.h>
// #include "input.h"
// #include "utils.h"

// #define MAX_INPUT_LENGTH 1024
// static char buffer[MAX_INPUT_LENGTH];
// static int buf_len = 0;

// char response[MAX_INPUT_LENGTH] = "429Too many Requests\n"; //定义一个响应消息

// int get_input(WINDOW *input_win, WINDOW *chat_win)
// {
//     int ch;
//     buf_len = 0;
//     buffer[0] = '\0';
   
//     werase(input_win); 
//     box(input_win, 0, 0);
//     mvwprintw(input_win, 1, 1, "> ");//固定>在这里
//     wrefresh(input_win);

//     while (1) {
//         ch = wgetch(input_win);

//         if (ch == '\n') { 
//             buffer[buf_len] = '\0';
//             if (buf_len > 0) {
                
//                 wprintw(chat_win, "%s", buffer);
//                 // if(buffer[0]!='/'){ //不是以/开头打印响应消息
//                 //     wprintw(chat_win, "%s", response);
//                 // }
//                 // else {
//                 //     wprintw(chat_win, "%s", buffer);
//                 //     move(0, 0); //将光标移动到聊天窗口的开头
//                 //     wprintw(chat_win, "\nreceived,successfully: %s", buffer);
//                 // }
//                 // wrefresh(chat_win);
//                 // mvwprintw(chat_win, 1, 1, "%s", response); //在聊天窗口打印输入的内容
//                 // wrefresh(chat_win);

                
//                 if (strcmp(buffer, "/exit") == 0) {
//                     return 1;  //exit指令推出
//                 }
//             }

//             buf_len = 0;
//             buffer[0] = '\0';
            
//             werase(input_win);
//             box(input_win, 0, 0);
//             mvwprintw(input_win, 1, 1, "> ");
//             wrefresh(input_win);
//             return 0;
//         }
//         else if (ch == KEY_BACKSPACE) { 
//             if (buf_len > 0) {
//                 buf_len--;
//                 buffer[buf_len] = '\0';
//             }
            
//             werase(input_win);
//             box(input_win, 0, 0);
//             mvwprintw(input_win, 1, 1, "> %s", buffer);
//             wrefresh(input_win);
//         }
//         else { 
//             buffer[buf_len] = ch;
//             buf_len++;
//             buffer[buf_len] = '\0';
            
//             werase(input_win);
//             box(input_win, 0, 0);
//             mvwprintw(input_win, 1, 1, "> %s", buffer);
//             wrefresh(input_win);
//         }
//     }
// }

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