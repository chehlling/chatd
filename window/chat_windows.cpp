#include "chat_windows.h"

chat_windows::chat_windows()
{
	initscr();
	curs_set(0);
}

void chat_windows::create_header()
{
	int x=0;
	int y=0;
	int heigth=LINES/5;
	int width=COLS;
	header=newwin(heigth,width,y,x);
}

void chat_windows::create_output()
{
	int x=0;
	int y=LINES/5;
	int heigth=(LINES*3)/5;
	int width=(COLS*4)/5;
	output=newwin(heigth,width,y,x);
}

void chat_windows::create_friends_list()
{
	int x=(COLS*4)/5;
	int y=LINES/5;
	int heigth=(LINES*3)/5;
	int width=COLS/5;
	friends_list=newwin(heigth,width,y,x);
}

void chat_windows::create_input()
{
	int x=0;
	int y=(LINES*4)/5;
	int heigth=LINES/5;
	int width=COLS;
	input=newwin(heigth,width,y,x);
}

void chat_windows::put_str_to_win(WINDOW* win,int y,int x,const std::string msg)
{
	mvwaddstr(win,y,x,msg.c_str());
}

void chat_windows::clear_win_line(WINDOW* win,int y,int line)
{
	//int wmove(WINDOW *win, int y, int x);
	while(line--){
		wmove(win,y++,0);
		wclrtoeol(win);
	}
}

std::string chat_windows::get_str_from_win(WINDOW* win)
{
	char buf[SIZE];
	memset(buf,'\0',sizeof(buf));
	wgetnstr(win,buf,SIZE);
	return buf;
}

WINDOW* chat_windows::get_header_win()
{
	return header;
}

WINDOW* chat_windows::get_output_win()
{
	return output;
}

WINDOW* chat_windows::get_friends_list_win()
{
	return friends_list;
}

WINDOW* chat_windows::get_input_win()
{
	return input;
}

chat_windows::~chat_windows()
{
	delwin(header);
	delwin(friends_list);
	delwin(output);
	delwin(input);
	endwin();
}
