#include<stdio.h>
#include<ncurses.h>
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include<string.h>
//编译命令：gcc -I include -o tui src/tui.c src/utils.c -lncurses
//执行命令：./tui
#define PATH_MAX 4096
int main()
{

    initscr();            //初始化屏幕,stdscr作为主窗口

    WINDOW *status_win=create_newwin(3, COLS, 0, 0); //创建状态窗口，来保持状态栏
    WINDOW *main_win=create_newwin(LINES-5, COLS, 3, 0); //创建主窗口

    wprintw(main_win, "Hello, World!"); //在主窗口打印文本
    wrefresh(main_win); //刷新主窗口
    sleep(3);
    char cwd[PATH_MAX];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        //这里检查当前工作目录是否在/home下，如果是，则将/home替换为~
        if(strncmp(cwd, "/home/", 6) == 0) {
            char new_cwd[PATH_MAX];
            new_cwd[0]='~'; //将/home替换为~
            strncpy(new_cwd + 1, cwd + 6, sizeof(new_cwd) - 1); //将剩余的路径复制到new_cwd中
            new_cwd[sizeof(new_cwd) - 1] = '\0'; 
            //一定要确保字符串以空字符结尾，不然有问题！！！
            wprintw(status_win, "\nCurrent working directory: %s", new_cwd); //在状态窗口打印工作目录
        } 
        wprintw(status_win, "\nCurrent working directory: %s", cwd); //在状态窗口打印工作目录
    } else {
        wprintw(status_win, "\ncannot get current working directory");
    }

    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    wprintw(status_win, "\nCurrent time: %s", asctime(timeinfo)); //在状态窗口打印当前时间
    wrefresh(status_win); //刷新状态窗口
    sleep(3);

    wprintw(status_win, "Status: Running"); //在状态窗口打印状态信息
    wrefresh(status_win); //刷新状态窗口
    sleep(3);
    refresh();            //刷新屏幕显示
    getch();              //等待用户按键，否则程序退出
    endwin();             //结束窗口

    return 0;
}
