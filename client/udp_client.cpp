#include "udp_client.h"

udp_client::udp_client(std::string _ip,int _port)
	:ip(_ip)
	,port(_port)
	,sock(-1)
	,cmd("NULL")
{
//	fri_list.resize(FRIENDS_COUNTS);
}

void udp_client::init()
{
	//             协议族PF_INET
	sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		print_log(strerror(errno),__FUNCTION__,__LINE__); 
		exit(1);
	}
}

void udp_client::add_user_to_fri_list(std::string &friends)
{
	std::vector<std::string>::iterator item=fri_list.begin();
	while(item!=fri_list.end()){
		if((*item)==friends)
			return;
		item++;
	}
	fri_list.push_back(friends);
}

void udp_client::del_user_from_fri_list(std::string &friends)
{
	std::vector<std::string>::iterator item=fri_list.begin();
	while(item!=fri_list.end()){
		if((*item)==friends){
			fri_list.erase(item);
		}
		item++;
	}
}

ssize_t udp_client::send_data(std::string &_in)
{
	sockaddr_in remote;
	remote.sin_family=AF_INET;//地址族
	remote.sin_port=htons(port);
	remote.sin_addr.s_addr=inet_addr(ip.c_str());
	socklen_t len=sizeof(remote);

	ssize_t _size=sendto(sock,_in.c_str(),_in.size(),0,(struct sockaddr*)&remote,len);
	if(_size<0){
		print_log(strerror(errno),__FUNCTION__,__LINE__); 
	}
	return _size;
}

ssize_t udp_client::recv_data(std::string &_out)
{
	sockaddr_in remote;
	remote.sin_family=AF_INET;
	remote.sin_port=htons(port);
	remote.sin_addr.s_addr=inet_addr(ip.c_str());
	socklen_t len=sizeof(remote);

	char buf[SIZE];
	memset(buf,'\0',sizeof(buf));
	ssize_t _size=recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
	buf[_size]='\0';
	_out=buf;
	return _size;
}

udp_client::~udp_client()
{
	close(sock);
}
