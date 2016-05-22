#include <sfml\Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	cout << "Start client.";
	TcpSocket clnt_sock;
	cout << "Connecting....\n";
	//;
	if(clnt_sock.connect("localhost", 154)!=Socket::Done)
	{
		cout << "Connection is not established. Pres any key.\n";
		cin.get();
		return 1;
	}
	cout << "Connection is established.\n";
	
	clnt_sock.send("HW", 3);


	cin.get();
	return 0;
}