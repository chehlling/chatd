ROOT_PATH=$(shell pwd)

ROOT_JSON_LIB=$(shell pwd)/../libs/jsoncpp-lib
INCLUDE=-I$(ROOT_JSON_LIB)/include
LDFLAGS=-L$(ROOT_JSON_LIB)/libs/linux-gcc-4.4.7 -ljson_linux-gcc-4.4.7_libmt #-static 
FLAGS=#-D_DEBUG_


MYJSON_BIN=myjson
MYJSON_SRC=$(shell pwd)/myjson.cpp
MYJSON_OBJ=$(MYJSON_SRC:.cpp=.o)

CC=g++

$(MYJSON_BIN):$(MYJSON_OBJ)
	@$(CC) -o $@ $< $(LDFLAGS)  
	@echo "linking..."
$(MYJSON_OBJ):$(ROOT_PATH)/myjson.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS) 
	@echo "compling..."

.PHONY:clean
clean:
	rm -f *.o $(MYJSON_BIN)

	
.PHONY:debug
debug:
	@echo $(ROOT_PATH)
	@echo $(MYJSON_BIN)
	@echo $(MYJSON_OBJ)
	@echo $(MYJSON_SRC)
	@echo $(ROOT_JSON_LIB)
	@echo $(INCLUDE)
	@echo $(LDFLAGS)

