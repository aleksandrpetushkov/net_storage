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
	Client cln;
	cout << "Connecting....\n";
	cln.start("localhost", 154);
	if (!cln.Connect())
	{
		cout << "Connection is not established. Pres e(xit) || r(esume).\n";
		cin.get();
		return 1;
	}
	cout << "Connection is established.\n";
	/*
	char mas[1];
	mas[0] = 1;
	cln.Send(mas);
	cln.Received(mas);
	if(mas[0]==1)
	{
		cout << "Ther good\n";
	}
	else
	{
		cout << "Ther bad\n";
	}
	//*/
	//*
	unsigned short menu;
	int key, val;
	while(true)
	{
		try
		{
			cout << "\n1. Set value.\n2. Get value.\n3. Delete value.\nEnter number menu:";
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
				else
				{
					cout << "Error.\n";
				}
				break;
			case 2:
				cout << "Enter key: ";
				cin >> key;
				cout << "Val from server: " << cln.GetVal(key) << endl;
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
					cout << "Error.\n";
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