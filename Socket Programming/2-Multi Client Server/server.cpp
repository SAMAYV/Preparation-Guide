#include "server_socket.h"
#include "SocketException.h"
#include <string>
#include <iostream>

int main ( int argc, char* argv[] )
{
	std::cout << "Server running at port 30000....\n";

	try
	{
		// Create the socket
		ServerSocket server ( 30000 );
		server.set_non_blocking(true);
		server.allow_multiple_connections();

		while (true) {
			server.reset();

			int activity = select( server.mx_sd + 1 , server.get_fds() , NULL , NULL , NULL);
			if ((activity < 0) && (errno != EINTR)) { // TO DO
				printf("select error\n");
				exit(0);
			}

			server.check_for_new_client();
			server.read_pending_msgs();
		}
	}
	catch ( SocketException& e )
	{
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}

	return 0;
}