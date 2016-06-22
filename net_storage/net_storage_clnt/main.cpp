#include <sfml\Network.hpp>
#include <iostream>
#include "client.h"
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

int main()
{
	cout << "Start client.\n";
	//TcpSocket clnt_sock; // Создание сокета для соединения с сервером
	IpAddress ip("localhost");
	unsigned short port(154);
	Client cln(ip,port);
	cout << "Connecting....\n";
	cln.start();
	if (!cln.Connect())
	{
		cout << "Connection is not established. Pres any key for exit.\n";
		cin.get();
		return 1;
	}
	cout << "Connection is established.\n";
	
	unsigned short menu;
	int key, val;
	while(true)
	{
		try
		{
			cout << "1. Set value.\n2. Get value.\n3. Delete value.\nEnter number menu:";
			cin >> menu;
			switch (menu)
			{
			case 1:
				cout << "Enter key: ";
				cin >> key;
				cout << "Enter value: ";
				cin >> val;
				if(cln.SetVal(key, val))
				{
					cout << "Success.\n";
				}
				{
					cout << "Error. Connection is lost. press any key.";
					cin.get();
					return 1;
				}
				break;
			case 2:
				cout << "Enter key: ";
				cin >> key;
				if(cln.GetVal(key))
				{
					cout << "Val from server: " << key << endl;
				}
				else
				{
					cout << "Error. Connection is lost. press any key.";
					cin.get();
					return 1;
				}
				break;
			case 3:
				cout << "Enter key: ";
				cin >> key;
				if (cln.DelVal(key))
				{
					cout << "Success.\n";
				}
				else
				{
				cout << "Error. Connection is lost. press any key.";
				cin.get();
				return 1;
				}
				break;

			default:
				break;
			}
		}
		catch (char *mess)
		{
			cout << mess;
		}
	}
	//*/


	cin.get();
	return 0;
}