// Definition of the ServerSocket class

#ifndef ServerSocket_class
#define ServerSocket_class

#include "Socket.h"
#include <queue>
#include <iostream>
#include <cstring>

class ServerSocket : public Socket
{
    fd_set readfds; // set of socket descriptors
    int client_socket[MAXCONNECTIONS];
    int conn = 1;

    struct Client {
        int id;
        int fd; // file descriptor of the socket
        Client(int idx, int fd): id(idx), fd(fd) {}
    };

    std::queue<Client*>clients; // list of clients server is connected to.

    bool add_client() {
        if (conn == MAXCONNECTIONS) {
            std::cout << "MAXCONNECTIONS Reached\n";
            return false;
        }
        int addr_length = sizeof ( m_addr );
        int fd = ::accept ( m_sock, ( sockaddr * ) &m_addr, ( socklen_t * ) &addr_length );

        if ( fd <= 0 )
            return false;

        mx_sd = std::max(mx_sd, fd);

        for (int i = 0; i < MAXCONNECTIONS; i++) {
            if (client_socket[i] == 0) {
                Client* new_client = new Client(i, fd);
                client_socket[i] = fd;
                clients.push(new_client);
                std::cout << "New client connected. Client ID: " << i << "\n";
                break;
            }
        }
        conn++;
        return true;
    }

    bool remove_client(Client* tmp_client) {
        // in case you have to remove you always pop out
        client_socket[tmp_client->id] = 0;
        std::cout << "Client ID: " << tmp_client->id << " disconnected\n";
        close(tmp_client->fd);
        delete tmp_client;
        conn--;
        return true;
    }

public:
    int mx_sd = 0;

    ServerSocket ( int port );
    ServerSocket () {};
    virtual ~ServerSocket();

    const ServerSocket& operator << ( const std::string& ) const;
    const ServerSocket& operator >> ( std::string& ) const;

    int get_conn();
    fd_set* get_fds();
    void accept ( ServerSocket& );
    void allow_multiple_connections();
    void check_for_new_client();
    void read_pending_msgs();
    void reset();

};


#endif