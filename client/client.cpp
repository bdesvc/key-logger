#include "client.h"


void client::initialize(std::string ip, int port) {
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		return;
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	this->csocket = socket(AF_INET, SOCK_STREAM, NULL);

	while (connect(this->csocket, (SOCKADDR*)&addr, sizeofaddr) != 0)
	{

	}
}
