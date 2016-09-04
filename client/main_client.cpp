#include "udp_client.h"
#include "chat_windows.h"

udp_client* clip=NULL;

void* header_handler(void* args)
{
	chat_windows* win=(chat_windows*)args;
	int y=0;
	int x=0;
	int _y_max;
	int _x_max;
	std::string msg="welcome to udp_chat";
	
	win->create_header();
	WINDOW* header=win->get_header_win();
	getmaxyx(header,_y_max,_x_max);
	y=_y_max/2;
	x=1;
	while(1){
		box(header,0,0);
		win->put_str_to_win(header,y,x++,msg);
		x%=_x_max;
		if(x>=(_x_max-msg.size()))
			x=1;
		usleep(100000);
		wrefresh(header);
		win->clear_win_line(header,y,1);
	}
}	

void* output_handler(void* args)
{
	chat_windows* win=(chat_windows*)args;
	int y=1;
	int x=2;
	int _y_max;
	int _x_max;

	std::string _out;
	my_json json;
	std::string msg;
	std::string friends;
	std::string cmd;

	win->create_output();
	WINDOW* output=win->get_output_win();
	getmaxyx(output,_y_max,_x_max);
	while(1){
		box(output,0,0);
		wrefresh(output);
		clip->recv_data(_out);
		Json::Value rec_msg=json.recvmsg_str_to_val(_out);
		
		msg=rec_msg["name"].asString();
		msg+="-";
		msg+=rec_msg["school"].asString();
		friends=msg;
		msg+=" #";
		msg+=rec_msg["msg"].asString();
		cmd=rec_msg["cmd"].asString();

		clip->add_user_to_fri_list(friends);
		if(cmd=="QUIT"){
			clip->del_user_from_fri_list(friends);
		}

		if(y==1)
			win->clear_win_line(output,y,_y_max-2);
		
		win->put_str_to_win(output,y++,x,msg);

		wrefresh(output);
		usleep(10000);
		if(y>=(_y_max-1)){
			y=1;
		}
	}
}

void* friends_list_handler(void* args)
{
	int y=1;
	int x=2;
	int _y_max;
	int _x_max;
	int index=1;
	int size=0;
	int page;
	chat_windows* win=(chat_windows*)args;
	win->create_friends_list();
	WINDOW* friends_list=win->get_friends_list_win();
	getmaxyx(friends_list,_y_max,_x_max);
	int count=_y_max-2;
	while(1){
		box(friends_list,0,0);
		wrefresh(friends_list);

		size=(clip->fri_list).size();
		
		page=size/(count);
		if(size%(count)!=0){
			page+=1;
		}
		int tmp_count=count;

//		std::cout<<tmp_count<<std::endl;
//		std::cout<<size<<std::endl;
//		std::cout<<page<<std::endl;
//		sleep(100);

//		while(page){
//			box(friends_list,0,0);
//			while(size!=0 && tmp_count--){
//				win->put_str_to_win(friends_list,index++,x,clip->fri_list[index-1]);
//				size--;
//				index++;
//			}
//			wrefresh(friends_list);
//			sleep(3);
//			tmp_count=count;
//			page--;
//		}
		index=1;
	}
}

void* input_handler(void* args)
{
	int _y_max;
	int _x_max;
	std::string str="Please Enter #";
	my_json json;

	chat_windows* win=(chat_windows*)args;
	win->create_input();
	WINDOW* input=win->get_input_win();
	getmaxyx(input,_y_max,_x_max);
	while(1){
		clip->cmd="NULL";
		box(input,0,0);
		win->put_str_to_win(input,1,1,str);
		wrefresh(input);
		clip->msg=win->get_str_from_win(input);
		
		if(clip->msg=="q" || clip->msg=="quit")
			clip->cmd="QUIT";
			
		std::string sendmsg=json.sendmsg_val_to_str(clip->name,clip->school,clip->cmd,clip->msg);
		clip->send_data(sendmsg);
		usleep(1000);
		win->clear_win_line(input,1,_y_max-2);
		if(clip->cmd=="QUIT"){
			win->~chat_windows();
			exit(1);
		}
	}
}

int main(int argc,char *argv[])
{
	if(argc!=3){
		std::cout<<"Usage is [proc] [ip] [port]"<<std::endl;
		return -1;
	}
	udp_client clit(argv[1],atoi(argv[2]));
	clit.init();
	clip=&clit;

	std::cout<<"Please Enter name:";
	std::cin>>clit.name;
	std::cout<<"Please Enter school:";
	std::cin>>clit.school;

	chat_windows w;

	pthread_t th,to,tf,ti;
	pthread_create(&th,NULL,header_handler,(void*)&w);
	pthread_create(&to,NULL,output_handler,(void*)&w);
	pthread_create(&tf,NULL,friends_list_handler,(void*)&w);
	pthread_create(&ti,NULL,input_handler,(void*)&w);

    pthread_join(th,NULL);
	pthread_join(to,NULL);
	pthread_join(tf,NULL);
	pthread_join(ti,NULL);

	return 0;
}
