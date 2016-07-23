#ifndef TCP_Client_h
#define TCP_Client_h

#include <netdb.h>
#include <cstring>
//#include <sys/socket.h>
#include <iostream>

//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <sys/types.h>
//#include <netinet/in.h>

#include <sockLib.h>

//! Opens a TCP connection to an url and port pair.
/*!
	\param url the url to connect to.
	\param TCP port to connect to.
	\return socket descriptor
*/
int TCP_Client( const char* url, const char* port );

#endif
