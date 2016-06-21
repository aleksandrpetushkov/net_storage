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
		while (true)
		{			
			cout << "Wait new client...\n";
			if (!_lst.accept(srv_sock) == TcpSocket::Done)
			{
				throw "Error open socket!\n";
			}
			cout << "Connected established.\n";
			std::size_t received = 0;
			{
				char v[9];
				srv_sock.receive(v, sizeof(v), received);
				if (Protocol::VerOk(v))
				{
					if (srv_sock.send(v, 9) == TcpSocket::Done)
					{
						cout << "Ther good\n";
					}
				}
				else
				{
					Protocol::S_ErrorProtocol(v);
					srv_sock.send(v, 9);
					srv_sock.disconnect();
					cout << "Ther bad\n";
				}
			}
			while (true)
			{
				if (srv_sock.receive(received_pac, 9, received) == TcpSocket::Done)
				{
					cout << "Income request.\n";
					Processing(received_pac, answer_pack);
					//cout << (int)answer_pack[0] << "___" << answer_pack[1] << "___" << answer_pack[2] << "___" << endl;

				}
				else
				{
					cout << "Error connection.\n";
					srv_sock.disconnect();
					break;

				}
				if (srv_sock.send(answer_pack, 9) == TcpSocket::Done)
				{
					//cout << (int)answer_pack[0] << "___" << answer_pack[1] << "___"<<answer_pack[2] << "___" << endl;
					cout << "Answer transmission.\n";
				}
				else
				{
					cout << "Error connection.\n";
					srv_sock.disconnect();
					break;
				}
			}
		}
		
		//*/
	}
protected:
	void Processing(char * received_pac, char * answer_pack)
	{
		int key = Protocol::GetKey(received_pac);
		switch (received_pac[0])
		{
		case  Protocol::_set_val:
			
			//cout << "inpack: " << received_pac[0] << "___" << received_pac[1] << "___" << received_pac[2] << "___" << endl;
			//cout << "\n1. key: " << key << endl;
			storage[key] = Protocol::GetVal(received_pac);
			answer_pack[0] = 1;
			cout << "Set: key: " << key << " val: " << Protocol::GetVal(received_pac) << endl;
			break;
		case Protocol::_get_val:
			key = Protocol::GetKey(received_pac);
			cout << "Get: key: " << key << " val: ";
			if(storage.find(key)!=storage.end())
			{
				Protocol::S_PackGetVal(answer_pack, storage[key]);
				cout << storage[key] << endl;
				//cout << "1" << endl;
			}
			else
			{
				cout << "not exist.\n";
				Protocol::S_PackError(answer_pack);
				//cout << "2" << endl;
			}
			break;
		case Protocol::_del_elem:
			cout << "Del: key: " << key;
			if (storage.find(key) != storage.end())
			{
				cout << " - deleted\n";
				storage.erase(Protocol::GetKey(received_pac));
				answer_pack[0] = 1;
				//cout << "1" << endl;
			}
			else
			{
				cout << " not exit.\n";
				Protocol::S_PackError(answer_pack);
				answer_pack[0] = 0;

				//cout << "2" << endl;
			}
			break;
		}

	}
	char received_pac[3], answer_pack[3];
	TcpListener _lst;
	TcpSocket srv_sock;
	unsigned short _port;
	map<int, int> storage;
};