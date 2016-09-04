chat_windows:chat_windows.o 
	g++ -o $@ $^ -lncurses -lpthread 
chat_windows.o:chat_windows.cpp
	g++ -c $^ -g #-I/home/chehlling/chatd/comm 

.PHONY:clean
clean:
	rm -f *.o chat_windows 
