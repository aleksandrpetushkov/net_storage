#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <map>
#include <vector>
//#include <thread>
//#include "TClient.h"
#include <string>
#include "../Protocol.h"


using namespace std;
using namespace sf;


class TClient
{
public:
	TClient(TcpSocket *sock, Mutex *mx, map<int, int> *storage)
	{
		_storage = storage;
		_sock = sock;
		_mx = mx;
	}
	void Run()
	{
		char received_pac[9], answer_pack[9];
		size_t received = 0;
		while (true)
		{
			if ((*_sock).receive(received_pac, 9, received) == TcpSocket::Done)
			{
				cout << "Income request from client: " << (*_sock).getRemoteAddress() << ":" << (*_sock).getRemotePort() << ".\n";
				Processing(received_pac, answer_pack);
				//cout << (int)answer_pack[0] << "___" << answer_pack[1] << "___" << answer_pack[2] << "___" << endl;

			}
			else
			{
				break;
			}
			if ((*_sock).send(answer_pack, 9) == TcpSocket::Done)
			{
				//cout << (int)answer_pack[0] << "___" << answer_pack[1] << "___"<<answer_pack[2] << "___" << endl;
				cout << "Answer transmission.\n";
			}
			else
			{
				break;
			}
		}
		cout << "Client: " << (*_sock).getRemoteAddress() << ":" << (*_sock).getRemotePort() << " is lost.\n";
		//По какой-то причине связь разорвалась, выставляется _stop в тру, что бы основной поток мог удалить данный объект.
		_m_stop.lock();
		_stop = true;
		_m_stop.unlock();
	}
	//

	bool Stop() //Проверка на прекращение работы сетевой сессии для удленя объекта
	{
		bool result;
		_m_stop.lock();
		result = _stop;
		_m_stop.unlock();
		return result;
	}
	~TClient()
	{
		//cout << "Destructor start...\n";
		(*_sock).disconnect();
		delete _sock;

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
			(*_mx).lock();
			(*_storage)[key] = Protocol::GetVal(received_pac);
			(*_mx).unlock();
			answer_pack[0] = 1;
			cout << "Set: key: " << key << " val: " << Protocol::GetVal(received_pac) << endl;
			break;
		case Protocol::_get_val:
			key = Protocol::GetKey(received_pac);
			cout << "Get: key: " << key << " val: ";
			(*_mx).lock();
			if ((*_storage).find(key) != (*_storage).end())
			{
				Protocol::S_PackGetVal(answer_pack, (*_storage)[key]);
				cout << (*_storage)[key] << endl;
			}
			else
			{
				cout << "not exist.\n";
				Protocol::S_PackError(answer_pack);
			}
			(*_mx).unlock();
			break;
		case Protocol::_del_elem:
			cout << "Del: key: " << key;
			(*_mx).lock();
			if ((*_storage).find(key) != (*_storage).end())
			{
				cout << " - deleted\n";
				(*_storage).erase(key);
				answer_pack[0] = 1;
			}
			else
			{
				cout << " not exit.\n";
				Protocol::S_PackError(answer_pack);
				answer_pack[0] = 0;
			}
			(*_mx).unlock();
			break;
		}
	}

	
	bool _stop = false;
	Mutex _m_stop;
	Mutex *_mx;
	TcpSocket *_sock;
	map<int, int> *_storage;
	
};



class Server
{
public:
	Server(unsigned short const &port)
	{
		
		_port = port;

	}
	//

	void Start()
	{
		if (!_lst.listen(_port) == TcpListener::Done)
		{
			throw "Error open port for listen.\n";
		}
		while (true)
		{
			srv_sock = new TcpSocket;
			cout << "Wait new client...\n";
			if (!_lst.accept(*srv_sock) == TcpSocket::Done)
			{
				throw "Error open socket!\n";
			}
			cout << "Income new client: "<<(*srv_sock).getRemoteAddress()<<":"<<(*srv_sock).getRemotePort()<<".\n";
			std::size_t received = 0;
			{
				char v[9];
				(*srv_sock).receive(v, sizeof(v), received);
				if (Protocol::VerOk(v))
				{
					cout << "Protocol - ok.\n";
					if ((*srv_sock).send(v, 9) == TcpSocket::Done)
					{
						//cout << "Answer is send.\n"<<"Start connection in new thread.\n";
						TCL =  new TClient(srv_sock, &mx, &storage);
						TRC = new Thread(&TClient::Run, TCL);
						TRC->launch();
						mass_connect[TRC] = TCL;
						cout << "Clients before clean:" << mass_connect.size() << endl;
						for(auto& elem:mass_connect)
						{
							//cout << "!!!\n";
							if(elem.second->Stop())
							{
								delete elem.second;
								delete elem.first;
								mass_connect.erase(elem.first);
							}
						}
						cout << "Clients after clean:" << mass_connect.size() << endl;
					}
					else
					{
						cout << "Error connection.\n";
						(*srv_sock).disconnect();
						delete srv_sock;
					}
				}
				else
				{
					Protocol::S_ErrorProtocol(v);
					(*srv_sock).send(v, 9);
					(*srv_sock).disconnect();
					delete srv_sock;
					cout << "Protocol - bad";
				}
			}
		}
	}


	
protected:

	Mutex mx;
	TClient *TCL;
	Thread *TRC;
	map<Thread*, TClient*> mass_connect;
	TcpListener _lst;
	TcpSocket *srv_sock;
	unsigned short _port;
	map<int, int> storage;
};





