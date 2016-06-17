#include <SFML/Network.hpp>
#include <iostream>
#include "Protocol.h"
using namespace sf;

class Client
{
public:
	void start(std::string const &ip, unsigned short const &port)
	{
		if(sock.connect("localhost", port) == Socket::Done)
		{
			connect = true;
		}
	}
	bool Connect()
	{
		return connect;
	}
	void Send(const char mas[])
	{
		sock.send(mas, sizeof(mas));
	}
	bool Received(void *data)
	{
		size_t received = 0;
		if(sock.receive(data, 1, received)==TcpSocket::Disconnected)
		{
			return true;
		}
		return false;
	}
	bool SetVal(const int &key, const int &val)
	{

		if (Protocol::SetVal(key, val, sock))
		{
			return true;
		}
		return false;
	}
	int GetVal(const int &key)
	{
		Protocol::GetVal(key, sock);
	}

protected:
	TcpSocket sock;
	bool connect = false;

};

