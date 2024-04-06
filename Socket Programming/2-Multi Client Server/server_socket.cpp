// Implementation of the ServerSocket class

#include "server_socket.h"
#include "SocketException.h"
#include <queue>
#include <cstring>

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

  memset(client_socket, false, sizeof(client_socket));

  conn = 1;

  mx_sd = m_sock;
}

ServerSocket::~ServerSocket()
{
  FD_ZERO(&readfds);
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
  if (v == -1 )
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
}

void ServerSocket::allow_multiple_connections() {
  int opt = 1;
  if ( setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                  sizeof(opt)) < 0 ) {
    std::cout << "Unable to set-up multiple connections\n";
    exit(EXIT_FAILURE);
  }
  return;
}

int ServerSocket::get_conn() {
  return conn;
}

fd_set* ServerSocket::get_fds() {
  return &readfds;
}

void ServerSocket::check_for_new_client() {
  if (FD_ISSET(m_sock, &readfds)) {
    add_client();
  }
}

void ServerSocket::read_pending_msgs() {
  for (int i = 1; i < conn; i++) {
    Client* tmp_client = clients.front();
    clients.pop();
    if (FD_ISSET(tmp_client->fd, &readfds)) {
      //Check if it was for closing , and also read the
      //incoming message

      char buf [ MAXRECV + 1 ];

      std::string s = "";

      memset ( buf, 0, MAXRECV + 1 );

      int status = ::recv ( tmp_client->fd, buf, MAXRECV, 0 );

      if ( status == -1 )
      {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
      }
      else if ( status == 0 )
      {
        remove_client(tmp_client);
      }
      else
      {
        s = buf;
        std::cout << "Message from client ID: " << tmp_client->id << " || " << s << "\n";
        // ::send(tmp_client->fd, buffer, strlen(buffer), 0);
        clients.push(tmp_client);
      }
    }
    else {
      clients.push(tmp_client);
    }
  }
}

void ServerSocket::reset() {
  FD_ZERO(&readfds);
  FD_SET(m_sock, &readfds);
  mx_sd = m_sock;

  for (int i = 0; i < MAXCONNECTIONS; i++) {
    int fd = client_socket[i];

    if (fd > 0) {
      FD_SET(fd, &readfds);
    }

    if (fd > mx_sd) {
      mx_sd = fd;
    }
  }
}