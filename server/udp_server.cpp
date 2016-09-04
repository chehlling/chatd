#include "udp_server.h"

udp_server::udp_server(std::string _ip,int _port)
	:ip(_ip)
	,port(_port)
	,sock(-1)
{}

void udp_server::init()
{
	//              协议族
	sock=socket(PF_INET,SOCK_DGRAM,0);
	if(sock<0){
		print_log(strerror(errno),__FUNCTION__,__LINE__); 
		exit(1);
	}
	sockaddr_in local;
	local.sin_family=AF_INET;//地址族
	local.sin_port=htons(port);
	if(ip=="any"){
		local.sin_addr.s_addr=htonl(INADDR_ANY);
	}else{
		local.sin_addr.s_addr=inet_addr(ip.c_str());
	}
	socklen_t len=sizeof(local);
	
	if(bind(sock,(sockaddr*)&local,len)<0){
		print_log(strerror(errno),__FUNCTION__,__LINE__); 
		exit(1);
	}
}

void udp_server::add_user_to_list(struct sockaddr_in &_client)
{
	std::map<std::string,struct sockaddr_in>::iterator item = online_user.find(inet_ntoa(_client.sin_addr));
	if(item==online_user.end()){
		online_user.insert(std::pair<std::string,struct sockaddr_in>(inet_ntoa(_client.sin_addr),_client));
		std::cout<<"new member... "<<std::endl;
	}
	return;
}

void udp_server::del_user_from_list(struct sockaddr_in &_client,std::string &_name,std::string &_school)
{
	std::map<std::string,struct sockaddr_in>::iterator item = online_user.find(inet_ntoa(_client.sin_addr));
	online_user.erase(item);
	std::cout<<_name<<"-"<<_school<<"  quit!"<<std::endl;
}

//void udp_server::add_user_to_list(struct sockaddr_in &_client)
//{
//	std::map<int,struct sockaddr_in>::iterator item = online_user.find(_client.sin_port);
//	if(item==online_user.end()){
//		online_user.insert(std::pair<int,struct sockaddr_in>(_client.sin_port,_client));
//		std::cout<<"new member... "<<std::endl;
//	}
//	return;
//}
//void udp_server::del_user_from_list(struct sockaddr_in &_client,std::string &_name,std::string &_school)
//{
//	std::map<int,struct sockaddr_in>::iterator item = online_user.find(_client.sin_port);
//	online_user.erase(item);
//	std::cout<<_name<<"-"<<_school<<"  quit!"<<std::endl;
//}

ssize_t udp_server::recv_data()
{
	sockaddr_in client;
	socklen_t len=sizeof(client);

	char buf[SIZE];
	buf[0]='\0';
	ssize_t _size=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
	if(_size<0){
		print_log(strerror(errno),__FUNCTION__,__LINE__); 
	}else{
		buf[_size]='\0';
		std::cout<<"server have recv success!  size:"<<_size<<"   buf:"<<buf;
		std::string _out=buf;
		my_json json;
		Json::Value root=json.recvmsg_str_to_val(_out);
		std::string cmd=root["cmd"].asString();
		std::string name=root["name"].asString();
		std::string school=root["school"].asString();
		
		add_user_to_list(client);
		if(cmd=="QUIT")
			del_user_from_list(client,name,school);
		msg_pool.data_put(_out);
	}
	return _size;
}

ssize_t udp_server::send_data(struct sockaddr_in _client,std::string _in_msg)
{
	ssize_t _size=sendto(sock,_in_msg.c_str(),_in_msg.size(),0,(struct sockaddr*)&_client,sizeof(_client));
	if(_size<0){
		print_log(strerror(errno),__FUNCTION__,__LINE__);
	}
	return _size;
}

void udp_server::boardcast()
{
	std::string _in;
	msg_pool.data_get(_in);
	std::map<std::string,struct sockaddr_in>::iterator item=online_user.begin(); 
//	std::map<int,struct sockaddr_in>::iterator item=online_user.begin(); 
	while(item!=online_user.end()){
		send_data((*item).second,_in);
		item++;
	}
}

udp_server::~udp_server()
{
	close(sock);
}
