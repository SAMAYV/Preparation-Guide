#include "server_socket.h"
#include "SocketException.h"
#include <string>
#include <iostream>

int main ( int argc, char* argv[] )
{
	std::cout << "Server running at port 3000....\n";

	try
	{
		// Create the socket
		ServerSocket server ( 30000 );

		while ( true )
		{

			ServerSocket new_sock;
			server.accept ( new_sock );

			try
			{
				while ( true )
				{
					std::string data;
					new_sock >> data;
					std::cout << "Client Message: " << data << "\n";
					new_sock << data + "$" + data;
				}
			}
			catch ( SocketException& ) {}

		}
	}
	catch ( SocketException& e )
	{
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}

	return 0;
}