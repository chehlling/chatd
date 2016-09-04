#include "data_pool.h"

data_pool::data_pool()
	:capacity(CAP)
	,msg_pool(CAP)//vector
	,put_index(0)
	,get_index(0)
{
	sem_init(&put_sem,0,CAP);
	sem_init(&get_sem,0,0);
}

void data_pool::data_put(std::string _out_msg)
{
	sem_wait(&put_sem);
	msg_pool[put_index++]=_out_msg;
	put_index%=capacity;
	sem_post(&get_sem);
//	std::cout<<_out_msg<<"has been put into datapool"<<std::endl;
}

void data_pool::data_get(std::string &_in_msg)
{
	sem_wait(&get_sem);
	_in_msg=msg_pool[get_index++];
	get_index%=capacity;
	sem_post(&put_sem);
}

data_pool::~data_pool()
{
	sem_destroy(&put_sem);
	sem_destroy(&get_sem);
}
