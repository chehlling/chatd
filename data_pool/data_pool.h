#pragma once

#include <iostream>
#include <vector>
#include <semaphore.h>

#define CAP 256

class data_pool
{
public:
	data_pool();
	void data_put(std::string _out_msg);
	void data_get(std::string &_in_msg);
	~data_pool();
private:
	int capacity;
	std::vector<std::string> msg_pool;
	
	sem_t put_sem;
	sem_t get_sem;
	int put_index;
	int get_index;
};
