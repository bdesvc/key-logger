
#pragma once
#include <string>
#include <winsock.h>
#include <iostream>

class client
{
public:
	SOCKET csocket;
	void initialize(std::string ip, int port);
};

