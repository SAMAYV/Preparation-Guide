# Makefile for the socket programming example
#

all : server.o client.o

Socket.o :
	g++ -o Socket.o Socket.cpp -c

server_socket.o : Socket.o
	g++ -o server_socket.o server_socket.cpp -c

client_socket.o: Socket.o
	g++ -o client_socket.o client_socket.cpp -c

server.o: server_socket.o
	g++ -o server.o server_socket.o Socket.o server.cpp 

client.o: client_socket.o
	g++ -o client.o client_socket.o Socket.o client.cpp

clean:
	rm -f *.o 