#include "client_socket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, char** argv )
{
  try
  {

    ClientSocket client_socket ( "localhost", 30000 );

    std::string reply;

    while (true) {
      try
      {
        std::cout << "Enter message for client: ";
        std::cin >> reply;
        client_socket << reply;
        // client_socket >> reply;
      }
      catch ( SocketException& ) {}
    }

    // std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

  }
  catch ( SocketException& e )
  {
    std::cout << "Exception was caught:" << e.description() << "\n";
  }

  return 0;
}
