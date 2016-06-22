#include <sfml\Network.hpp>
#include <iostream>
#include "client.h"
#include <SFML/System.hpp>
#include "gtest/gtest.h"

TEST(Client)
{
	Client clnt("localhost", 1010);
	clnt.start();
	ASSERT_FALSE(clnt.Connect());
	ASSERT_FALSE(clnt.SetVal(4, 4));
	ASSERT_FALSE(clnt.GetVal(5));
	char tst[9];
	tst[0] = 1;
	ASSERT_TRUE(Protocol::C_AnswerServOk(tst));
	tst[0] = 2;
	ASSERT_FALSE(Protocol::C_AnswerServOk(tst));
	
}

using namespace std;
using namespace sf;

int main(int argc, char* argv[])
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
	}
	else
	{
		cout << "Connection is established.\n";

		unsigned short menu;
		int key, val;
		bool work = true;
		while (work)
		{
			try
			{
				cout << "1. Set value.\n2. Get value.\n3. Delete value.\n4. Exit.\nEnter number menu:";
				cin >> menu;
				switch (menu)
				{
				case 1:
					cout << "Enter key: ";
					cin >> key;
					cout << "Enter value: ";
					cin >> val;
					if (cln.SetVal(key, val))
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
					if (cln.GetVal(key))
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
				case 4:
					work = false;
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
	}
	
	//*/
	//*
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	//*/
	cin.get();
	cin.get();
	return 0;
}