#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <map>
#include <string>
#include "Protocol.h"

using namespace std;
using namespace sf;

class Server
{
public:
	Server(unsigned short &port)
	{
		
		_port = port;

	}
	void Start()
	{
		if (!_lst.listen(_port) == TcpListener::Done)
		{
			throw "Error open port for listen.\n";
		}
		cout << "Wait connect...\n";
		if(!_lst.accept(srv_sock)==TcpSocket::Done)
		{
			throw "Error open socket!\n";
		}
		cout << "Connected established.\n";
		std::size_t received = 0;
		{
			char v[1];
			srv_sock.receive(v, sizeof(v), received);
			if(Protocol::n_ver_p(v[0]))
			{
				char _send[1];
				_send[0] = 1;
				srv_sock.send(_send, 1);
				cout << "Ther good\n";

			}
			else
			{
				char _send[1];
				_send[0] = 2;
				srv_sock.send(_send, 1);
				srv_sock.disconnect();
				cout << "Ther bad\n";
			}
		}
		int i, z;
		while (true)
		{
			char buf[9];
			srv_sock.receive(buf, sizeof(buf), received);
			switch (buf[0])
			{
			case 1:
				i |= buf[1];
				i <= 8;
				i |= buf[2];
				i <= 8;
				i |= buf[3]; 
				i <= 8;
				i |= buf[4];
				z |= buf[1];
				z <= 8;
				z |= buf[2];
				z <= 8;
				z |= buf[3];
				z <= 8;
				z |= buf[4];
				storage[i] = z;
				break;
			case 2:
				i |= buf[1];
				i <= 8;
				i |= buf[2];
				i <= 8;
				i |= buf[3];
				i <= 8;
				i |= buf[4];
				if(storage.find(i) != storage.end())
				{
					int tmp = storage[i];
					buf[0] = 1;
					buf[1] != tmp;
					tmp <= 8;
					buf[2] != tmp; 
					tmp <= 8;
					buf[3] != tmp;
					tmp <= 8;
					buf[4] != tmp;
					srv_sock.send(buf, 5);
				}
				else
				{
					buf[0] = 0;
					srv_sock.send(buf, 1);
				}
			default:
				break;
			}

		}
		//*/
	}
protected:
	TcpListener _lst;
	TcpSocket srv_sock;
	unsigned short _port;
	map<int, int> storage;
};