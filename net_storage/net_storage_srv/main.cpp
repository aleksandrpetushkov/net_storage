#include <SFML\Network.hpp>
#include <iostream>
#include <map>


using namespace std;
using namespace sf;

int main()
{
	cout << "Start server.\n";
	TcpListener lst;
	lst.listen(154);
	TcpSocket srv_sock;
	cout << "Wait connect...\n";
	lst.accept(srv_sock);
	size_t received = 0;
	char buf[1024];
	cout << "Connected established.\n";
	srv_sock.disconnect();
	{
		
		srv_sock.receive(buf, sizeof(buf), received);
		//srv_sock.receive()
		cout << "Received: " << buf << endl;
	}
	cout << "End\n";

	
	



	cin.get();
	
}


