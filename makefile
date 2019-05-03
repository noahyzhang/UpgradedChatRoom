cc=g++
server=ChatServer
client=ChatClient
INCLUDE=-I ./include 
LIB_PATH=-L ./libs
LDFLAGS=-std=c++11 -lpthread -ljsoncpp


.PHONY:all
all:$(server) $(client)
	

$(server):ChatServer.cc
	$(cc) $^ -o $@ $(INCLUDE) $(LIB_PATH)  $(LDFLAGS) -static

$(client):ChatClient.cc
	$(cc) -o $@ $^ $(INCLUDE) $(LIB_PATH)   $(LDFLAGS)  -lncurses

.PHONY:clean
clean:
	rm -f $(server) $(client)
