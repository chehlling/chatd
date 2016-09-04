#include "udp_server.h"


void* recvfunc(void* args)
{
	udp_server* s=(udp_server*)args;
	while(1){
		ssize_t _size=s->recv_data();
	}
}

void* boardfunc(void* args)
{
	udp_server* s=(udp_server*)args;
	while(1){
		s->boardcast();
	}
}

int main(int argc,char* argv[])
{
	if(argc!=3){
		std::cout<<"Usage is [proc] [ip] [port]"<<std::endl;
		return -1;
	}

	udp_server s(argv[1],atoi(argv[2]));
	s.init();

//	daemon(0,0);

	pthread_t tr,tb;
	pthread_create(&tr,NULL,recvfunc,(void*)&s);
	pthread_create(&tb,NULL,boardfunc,(void*)&s);

	pthread_join(tr,NULL);
	pthread_join(tb,NULL);

	return 0;
}
