#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;

class Client
{
public:
	void start(std::string const &ip, short const &port)
	{
		if(sock.connect("localhost", 154) == Socket::Done)
		{
			connect = true;
		}
	}
	bool Connect()
	{
		return connect;
	}
	void send(const char mas[])
	{
		sock.send(mas, sizeof(mas));
	}

protected:
	TcpSocket sock;
	bool connect = false;

};

