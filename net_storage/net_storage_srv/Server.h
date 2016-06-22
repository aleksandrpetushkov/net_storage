#include <SFML\Network.hpp>
//#include <SFML\System.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <thread>
//#include "TClient.h"
#include <string>
#include "../Protocol.h"


using namespace std;
using namespace sf;


void fr()
{
	cout << "eddd";
}

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
				cout << "Income request.\n";
				Processing(received_pac, answer_pack);
				//cout << (int)answer_pack[0] << "___" << answer_pack[1] << "___" << answer_pack[2] << "___" << endl;

			}
			else
			{
				cout << "Error connection.\n";
				(*_sock).disconnect();
				delete _sock;
				break;

			}
			if ((*_sock).send(answer_pack, 9) == TcpSocket::Done)
			{
				//cout << (int)answer_pack[0] << "___" << answer_pack[1] << "___"<<answer_pack[2] << "___" << endl;
				cout << "Answer transmission.\n";
			}
			else
			{
				cout << "Error connection.\n";
				(*_sock).disconnect();
				delete _sock;
				break;
			}
		}
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
			(*storage)[key] = Protocol::GetVal(received_pac);
			(*_mx).unlock();
			answer_pack[0] = 1;
			cout << "Set: key: " << key << " val: " << Protocol::GetVal(received_pac) << endl;
			break;
		case Protocol::_get_val:
			key = Protocol::GetKey(received_pac);
			cout << "Get: key: " << key << " val: ";
			(*_mx).lock();
			if ((*storage).find(key) != (*storage).end())
			{
				Protocol::S_PackGetVal(answer_pack, (*storage)[key]);
				cout << (*storage)[key] << endl;
				//cout << "1" << endl;
			}
			else
			{
				cout << "not exist.\n";
				Protocol::S_PackError(answer_pack);
				//cout << "2" << endl;
			}
			(*_mx).unlock();
			break;
		case Protocol::_del_elem:
			cout << "Del: key: " << key;
			(*_mx).lock();
			if ((*storage).find(key) != (*storage).end())
			{
				cout << " - deleted\n";
				(*storage).erase(Protocol::GetKey(received_pac));
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
			(*_mx).unlock();
			break;
		}
	}

	
	bool _stop = false;
	map<int, int> *storage;
	Mutex _m_stop;
	Mutex *_mx;
	TcpSocket *_sock;
	map<int, int> *_storage;
	
};



class Server
{
public:
	Server(unsigned short &port)
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
			cout << "Income new connection";
			std::size_t received = 0;
			{
				char v[9];
				(*srv_sock).receive(v, sizeof(v), received);
				if (Protocol::VerOk(v))
				{
					cout << "Protocol - ok.\n";
					if ((*srv_sock).send(v, 9) == TcpSocket::Done)
					{
						cout << "Answer is send.\n"<<"Start connection in new thread.\n";
						//TClient(TcpSocket *sock, Mutex *mx, map<int, int> *mp)
						TCl =  new TClient(srv_sock, &mx, &storage);
						//TCl->
						Thr = new Thread(fun);
						//lstTC.push_back(TCl);
					}
				}
				else
				{
					Protocol::S_ErrorProtocol(v);
					(*srv_sock).send(v, 9);
					(*srv_sock).disconnect();
					cout << "Ther bad\n";
				}
				/*
				for(const auto &elem:lstTC)
				{
					if(elem->Stop())
					{
						delete elem;
					}
				}
				//*/
			}
			
			/*
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
			//*/

		}
	}


	/*
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
			if (storage.find(key) != storage.end())
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
	//*/

protected:

	Mutex mx;
	TClient *TCl;
	Thread *Thr;
	map<Thread*, TClient*> mass_connect;
//	vector<TClient*> lstTC;
	//char received_pac[3], answer_pack[3];
	TcpListener _lst;
	TcpSocket *srv_sock;
	unsigned short _port;
	map<int, int> storage;
};





