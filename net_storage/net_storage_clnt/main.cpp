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
		cout << "Connection is not established. Pres any key.\n";
		cin.get();
		return 1;
	}
	cout << "Connection is established.\n";
	char mas[2];
	while(true)
	{
		cout << "Enter key: ";
		cin >> mas[0];
		cout << "Enter value: ";
		cin >> mas[1];
		cln.send(mas);
		cin.get();
	}


	cin.get();
	return 0;
}