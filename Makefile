ROOT_PATH=$(shell pwd)

ROOT_COMM=$(ROOT_PATH)/comm
ROOT_JSON_LIB=$(ROOT_PATH)/libs/jsoncpp-lib
ROOT_SERVER=$(ROOT_PATH)/server
ROOT_CLIENT=$(ROOT_PATH)/client
ROOT_DATA_POOL=$(ROOT_PATH)/data_pool
ROOT_WINDOW=$(ROOT_PATH)/window

CC=g++
FLAGS=
DLFLAGS=-lpthread -L$(ROOT_JSON_LIB)/libs/linux-gcc-4.4.7 -ljson_linux-gcc-4.4.7_libmt #-static
INCLUDE=-I$(ROOT_COMM) -I$(ROOT_DATA_POOL) -I$(ROOT_JSON_LIB)/include -I$(ROOT_WINDOW)

SERVER_BIN=udp_server
CLIENT_BIN=udp_client

COMM_SRC=$(shell ls -R $(ROOT_COMM) | grep -E '*\.cpp')
DATA_POOL_SRC=$(shell ls -R $(ROOT_DATA_POOL) | grep -E '*\.cpp')
WINDOW_SRC=$(shell ls -R $(ROOT_WINDOW) | grep -E '*\.cpp')
SERVER_SRC=$(shell ls -R $(ROOT_SERVER) | grep -E '*\.cpp')
SERVER_SRC+=$(COMM_SRC)
SERVER_SRC+=$(DATA_POOL_SRC)
CLIENT_SRC=$(shell ls -R $(ROOT_CLIENT) | grep -E '*\.cpp')
CLIENT_SRC+=$(COMM_SRC)
CLIENT_SRC+=$(WINDOW_SRC)

COMM_OBJ=$(COMM_SRC:.cpp=.o)
SERVER_OBJ=$(SERVER_SRC:.cpp=.o)
CLIENT_OBJ=$(CLIENT_SRC:.cpp=.o)
DATA_POOL_OBJ=$(DATA_POOL_SRC:.cpp=.o)
WINDOW_OBJ=$(WINDOW_SRC:.cpp=.o)
#COMM_OBJ=$(patsubst %.cpp,%.o,$(COMM_SRC))
#SERVER_OBJ=$(patsubst %.cpp,%.o,$(SERVER_SRC))
#CLIENT_OBJ=$(patsubst %.cpp,%.o,$(CLIENT_SRC))
#DATA_POOL_OBJ=$(patsubst %.cpp,%.o,$(DATA_POOL_SRC))


.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)
$(SERVER_BIN):$(SERVER_OBJ)
	@$(CC) -o $@ $^ $(DLFLAGS)
	@echo "Linking [$^] to [$@] ...done"
$(CLIENT_BIN):$(CLIENT_OBJ)
	@$(CC) -o $@ $^ $(DLFLAGS) -lncurses
	@echo "Linking [$^] to [$@] ...done"
%.o:$(ROOT_COMM)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [$(shell basename $<)] to [$@] ...done"
%.o:$(ROOT_SERVER)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [$(shell basename $<)] to [$@] ...done"
%.o:$(ROOT_CLIENT)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [$(shell basename $<)] to [$@] ...done"
%.o:$(ROOT_DATA_POOL)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [$(shell basename $<)] to [$@] ...done"
%.o:$(ROOT_WINDOW)/%.cpp
	@$(CC) -c $< $(INCLUDE)
	@echo "Compling [$(shell basename $<)] to [$@] ...done"
#after 6 line error,can't 递归找下面子目录中的文件，只能找到当前目录下的文件
#$(SERVER_OBJ):$(SERVER_SRC)
#	$(CC) -c $< $(INCLUDE) 
#$(CLIENT_OBJ):$(CLIENT_SRC)
#	$(CC) -c $< $(INCLUDE)
#$(COMM_OBJ):$(COMM_SRC)
#	$(CC) -c $< $(INCLUDE)

.PHONY:output
output:$(SERVER_BIN) $(CLIENT_BIN)
	@mkdir -p output/server/log 
	@mkdir -p output/client 
	@cp $(SERVER_BIN) output/server
	@cp $(CLIENT_BIN) output/client
	@cp -rf conf output/server
	@cp plugin/server_ctl.sh output/server
	

.PHONY:clean
clean:
	rm -rf output/ *.o $(SERVER_BIN) $(CLIENT_BIN)
	@echo clean ...done


.PHONY:debug
debug:
	@echo $(COMM_SRC)
	@echo $(SERVER_SRC)
	@echo $(CLIENT_SRC)
	@echo $(COMM_OBJ)
	@echo $(SERVER_OBJ)
	@echo $(CLIENT_OBJ)
	@echo $(INCLUDE)
	@echo $(ROOT_JSON_LIB)/include -ljson_
