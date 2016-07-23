#include "TCP_Client.h"

int TCP_Client( const char* url, const char* port ) {
	// Variables
	int connection;
	struct addrinfo host_info, *host_info_list;

	// Purify data structure and initialize
	memset( &host_info, 0, sizeof host_info );
	
	// Open Socket
	connection = socket( AF_INET, SOCK_STREAM, 0 );
	if ( connection < 0 ) {
		std::cout << "ERROR opening socket\n";
		return -1;
	}
	
	// Get server info
	if ( getaddrinfo( url, port, &host_info, &host_info_list ) != 0 ) {
		std::cout << "ERROR getting host info\n";
		return -1;
	}

	// Connect to server
	if ( connect( connection, host_info_list->ai_addr, host_info_list->ai_addrlen ) == -1 ) {
		std::cout << "ERROR connecting to host\n";
		return -1;
	}
	
	return connection;
}
