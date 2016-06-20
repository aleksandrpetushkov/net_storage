#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <map>
#include <string>
#include "../Protocol.h"

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
			//char _send[1];
			char v[1], _send[1];
			srv_sock.receive(v, sizeof(v), received);
			if(Protocol::n_ver_p(v[0]))
			{
				_send[0] = Protocol::GetProtocol();
				srv_sock.send(_send, 1);
				cout << "Ther good\n";

			}
			else
			{
				_send[0] = Protocol::ErrorProtocol();
				srv_sock.send(_send, 1);
				srv_sock.disconnect();
				cout << "Ther bad\n";
			}
		}
		int i, z;
		received_pac = new char[3];
		answer_pack = new char[Protocol::GetSizPack()];
		while (true)
		{
			srv_sock.receive(received_pac, sizeof(rsi), received);
			Protocol::Prarser_rec_pack_answer(buf, answer);
		}
		//*/
	}
protected:
	char *received_pac, *answer_pack;
	TcpListener _lst;
	TcpSocket srv_sock;
	unsigned short _port;
	map<int, int> storage;
};