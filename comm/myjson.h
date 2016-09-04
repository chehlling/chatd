#pragma once
#include <iostream>
#include "json/json.h"
#include <string>

class my_json
{
public:
	my_json();
	std::string sendmsg_val_to_str(std::string name,std::string school,std::string cmd="NULL",std::string msg="NULL");
	Json::Value recvmsg_str_to_val(std::string str);
	~my_json();
private:
	void serialize(Json::Value& root,std::string& str);
	void deserialize(std::string& str,Json::Value& root);
private:
};
