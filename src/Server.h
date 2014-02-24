#ifndef _SERVER_H
#define _SERVER_H

#include <winsock2.h>
#include <string>

#include "ProcessPool.h"

struct ClientData{
	SOCKET socket;
	SOCKADDR_IN addr;
};

class Server{
public:
	Server(int port);
	virtual ~Server();

	void getIOStatus(unsigned long *in,unsigned long *out);

	virtual void run();

protected:
	virtual bool onConnect(ClientData &client) = 0;

	virtual bool setup();
	virtual void cleanup();

	virtual int send(SOCKET sock,void *data,unsigned int length);
	virtual int recv(SOCKET sock,void *data,unsigned int length, bool complete=true);

	virtual void printError(const char *msg);

protected:
	SOCKET socket;
	SOCKADDR_IN addr;

	int port;

	ProcessPool<ClientData> workers;

	unsigned long totalIn, totalOut;
};


#endif //_SERVER_H