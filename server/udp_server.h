#pragma once

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <map>
#include "comm.h"
#include "data_pool.h"
#include "myjson.h"

#define DEFAULT_IP "any"
#define DEFAULT_PORT 8080

class udp_server
{
public:
	udp_server(std::string _ip=DEFAULT_IP,int _port=DEFAULT_PORT);
	void init();
	ssize_t recv_data();
	void boardcast();
	~udp_server();
private:
	ssize_t send_data(struct sockaddr_in _client,std::string _in_msg);
	void add_user_to_list(struct sockaddr_in &_client);
	void del_user_from_list(struct sockaddr_in &_client,std::string &_name,std::string &_school);
private:
	std::string ip;
	int port;
	int sock;

	data_pool::data_pool msg_pool;//vector<string>
	std::map<std::string,struct sockaddr_in> online_user;
//	std::map<int,struct sockaddr_in> online_user;
};
