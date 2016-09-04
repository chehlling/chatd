#include <iostream>
#include <string>
#include <string.h>
#include <ncurses.h>
#include "comm.h"
#include <pthread.h>

class chat_windows
{
public:
	chat_windows();
	void create_header();
	void create_output();
	void create_friends_list();
	void create_input();
	void put_str_to_win(WINDOW* win,int y,int x,const std::string msg);
	void clear_win_line(WINDOW* win,int y,int x);
	std::string get_str_from_win(WINDOW* win);
	WINDOW* get_header_win();
	WINDOW* get_output_win();
	WINDOW* get_friends_list_win();
	WINDOW* get_input_win();
	~chat_windows();
public:
//private:
	WINDOW* header;
	WINDOW* output;
	WINDOW* friends_list;
	WINDOW* input;
};
