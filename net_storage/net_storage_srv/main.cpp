#include "Server.h"
#include <iostream>
#include <map>


using namespace std;
using namespace sf;


int main()
{
	cout << "Start server.\n";
	unsigned short port=154;
	Server srv(port);
	srv.Start();
	
	
	
	
	cout << "End\n";
	cin.get();
	
}


