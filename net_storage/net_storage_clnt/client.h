#include <SFML/Network.hpp>
#include <iostream>
#include "../Protocol.h"
using namespace sf;

class Client
{
public:
	void start(std::string const &ip, unsigned short const &port)
	{
		if(sock.connect("localhost", port) == Socket::Done)
		{
			char pack[9];
			Protocol::PackProtocol(pack);
			if(sock.send(pack,9)==TcpSocket::Done)
			{
				size_t received = 0;
				if(sock.receive(pack,9,received)==TcpSocket::Done)
				{
					connect = true;
				}
			}
			
		}
	}
	bool Connect()
	{
		return connect;
	}
	//

	bool SetVal(const int &key, const int &val)
	{
		size_t received = 0;
		Protocol::C_PackSetVal(pack, key, val);
		if(sock.send(pack, 9) == TcpSocket::Done)
		{
			if (sock.receive(pack, 9, received) == TcpSocket::Done)
			{
				return Protocol::C_AnswerServOk(pack);
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	//

	int GetVal(const int &key)
	{
		size_t received = 0;
		Protocol::C_PackGetVal(pack, key);
		if (sock.send(pack, sizeof(pack)) == TcpSocket::Done)
		{
			if (sock.receive(pack, sizeof(pack), received) == TcpSocket::Done)
			{
				if(Protocol::C_AnswerServOk(pack))
				{
					return Protocol::C_GetValFromPack(pack);
				}
				throw "Server: values is not exist.\n\0";
			}
		}
	}
	bool DelVal(const int &key)
	{
		size_t received = 0;
		Protocol::C_PackDelVal(pack, key);
		if(sock.send(pack, sizeof(pack))==TcpSocket::Done)
		{
			if(sock.receive(pack,9,received)==TcpSocket::Done)
			{
				if (Protocol::C_AnswerServOk(pack))
				{
					return true;
;				}
				throw "Server: values is not exist.\n\0";
			}
		}
	}
	//


protected:
	char pack[9];
	TcpSocket sock;
	bool connect = false;

};

