#include "myjson.h"

my_json::my_json()
{}

void my_json::serialize(Json::Value& root,std::string& str)
{
#ifdef _DEBUG_
	Json::StyledWriter writer;
#else
	Json::FastWriter writer;
#endif
	str=writer.write(root);
}

void my_json::deserialize(std::string& str,Json::Value& root)
{
	Json::Reader reader;
	reader.parse(str,root,true);
}

std::string my_json::sendmsg_val_to_str(std::string name,std::string school,std::string cmd,std::string msg)
{
	Json::Value root;
	std::string str;
	root["name"]=name;
	root["school"]=school;
	root["cmd"]=cmd;
	root["msg"]=msg;
	serialize(root,str);
	return str;
}

Json::Value my_json::recvmsg_str_to_val(std::string str)
{
	Json::Value root;
	deserialize(str,root);
	return root;
}

my_json::~my_json()
{}


//int main()
//{
////	my_json str;
////	std::string sendmsg=str.sendmsg_val_to_str("chehlling","xpu","null");
////	std::cout<<sendmsg<<std::endl;
//
//	my_json str;
//	std::string msg_str="{\"cmd\":\"null\",\"name\":\"chehlling\",\"school\":\"xpu\"}";
//	Json::Value recvmsg=str.recvmsg_str_to_val(msg_str);
//	std::cout<<recvmsg["name"];
//	std::cout<<recvmsg["school"];
//	std::cout<<recvmsg["cmd"];
//
//	return 0;
//}

//int main()
//{
//	//serialize
//	my_json str;
//	Json::Value val;
//	val["name"]="chehlling";
//	val["school"]="xpu";
//	val["cmd"]="null";
//	std::string out;
//	str.var_to_str();
//	str.serialize(val,out);
//	std::cout<<out<<std::cout;
//
//	//deserialize
////	my_json str;
////	std::string in="{\"hobby\" : \"coding\", \"name\" : \"chehlling\", \"school\" : \"xpu\"}";
////	Json::Value val;
////	str.deserialize(in,val);
////	std::cout<<val["name"];
////	std::cout<<val["school"];
////	std::cout<<val["hobby"];
//
//	return 0;
//}
