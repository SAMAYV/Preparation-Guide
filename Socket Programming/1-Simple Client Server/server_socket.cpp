// Implementation of the ServerSocket class

#include "server_socket.h"
#include "SocketException.h"
#include <iostream>

ServerSocket::ServerSocket ( int port )
{
  if ( ! Socket::create() )
  {
    throw SocketException ( "Could not create server socket." );
  }

  if ( ! Socket::bind ( port ) )
  {
    throw SocketException ( "Could not bind to port." );
  }

  if ( ! Socket::listen() )
  {
    throw SocketException ( "Could not listen to socket." );
  }

}

ServerSocket::~ServerSocket()
{
}


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
  if ( ! Socket::send ( s ) )
  {
    throw SocketException ( "Could not write to socket." );
  }

  return *this;

}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
  int v = Socket::recv(s);
  if (v == -1)
  {
    throw SocketException ( "Could not read from socket." );
  }
  else if (v == 0) {
    std::cout << "Client disconnected\n";
    throw SocketException ( "Could not read from socket." );
  }

  return *this;
}

void ServerSocket::accept ( ServerSocket& sock )
{
  if ( ! Socket::accept ( sock ) )
  {
    throw SocketException ( "Could not accept socket." );
  }
  std::cout << "New client connected\n";
}
