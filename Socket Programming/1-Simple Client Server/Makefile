# Makefile for the socket programming example
#

all : server.o client.o

Socket.o :
	g++ -o Socket.o Socket.cpp -c

server_socket.o : Socket.o
	g++ -o server_socket.o server_socket.cpp -c

client_socket.o: Socket.o
	g++ -o client_socket client_socket.cpp -c

server.o: server_socket.o
	g++ -o server.o server.cpp server_socket.cpp Socket.cpp 

client.o: client_socket.o
	g++ -o client.o client.cpp client_socket.cpp Socket.cpp

clean:
	rm -f *.o server.o client.o