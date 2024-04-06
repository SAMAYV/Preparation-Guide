// Definition of the Socket class

#ifndef Socket_class
#define Socket_class

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <cerrno>
#include <sys/time.h>

const int MAAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

class Socket {
public:
	Socket();
	virtual ~Socket();

	// Server Initialization
	bool create();
	bool bind ( const int port );
	bool listen() const;
	bool accept (Socket&) const;

	// Client Initialization
	bool connect ( const std::string host, const int port );

	// Data Transmission
	bool send ( const std::string ) const;
	int recv (std::string& ) const;

	void set_non_blocking (const bool );
	bool is_valid() const { return m_sock != -1; }

	int m_sock; // socket descriptor
	sockaddr_in m_addr;
private:

};

#endif