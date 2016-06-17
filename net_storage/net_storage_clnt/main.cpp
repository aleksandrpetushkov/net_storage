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
	//*
	unsigned short menu;
	while(true)
	{
		cout << "Enter number menu:\n1. Set value.\n2. Get value.n";
		cin >> menu;
		switch(menu)
		{
		case 1:
			int key, val;
			cout << "Enter key: ";
			cin >> key;
			cout << "Enter value: ";
			cin >> val;
			cln.SetVal(key, val);
			break;
		}

		cout << "Enter key: ";
		cin >> mas[0];
		cout << "Enter value: ";
		cin >> mas[1];
		cln.Send(mas);
		cin.get();
	}
	//*/


	cin.get();
	return 0;
}