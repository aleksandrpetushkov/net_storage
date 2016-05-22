#include <sfml\Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	cout << "Start client.\n";
	TcpSocket clnt_sock; // Создание сокета для соединения с сервером
	cout << "Connecting....\n";
	if(clnt_sock.connect("localhost", 154)!=Socket::Done)// если не удается подключиться выход из программы
	{
		cout << "Connection is not established. Pres any key.\n";
		cin.get();
		return 1;
	}
	cout << "Connection is established.\n";
	while(true)
	{
		cout<<Ent
	}


	cin.get();
	return 0;
}