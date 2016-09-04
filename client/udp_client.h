#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "comm.h"
#include "myjson.h"

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 8080
#define FRIENDS_COUNTS 10
class udp_client
{
public:
	udp_client(std::string _ip=DEFAULT_IP,int _port=DEFAULT_PORT);
	void init();
	void add_user_to_fri_list(std::string &friends);
	void del_user_from_fri_list(std::string &friends);
	ssize_t send_data(std::string &_in);
	ssize_t recv_data(std::string &_out);
	~udp_client();
public:
	std::string name;
	std::string school;
	std::string msg;
	std::string cmd;

	std::vector<std::string> fri_list;

private:
	std::string ip;
	int port;
	int sock;

//	chat_windows* win;//####################
};
