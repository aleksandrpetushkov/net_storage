#include "Server.h"
#include <iostream>
#include <map>
#include "gtest/gtest.h"
#define t 1

using namespace std;
using namespace sf;

TEST (SErver)
{
	int i = 0;
	char msb[4];
	Protocol::int_to_bytes(msb,0,4);
	ASSERT_TRUE(msb[0] == 0);
	ASSERT_TRUE(msb[1] == 0);
	ASSERT_TRUE(msb[2] == 0);
	ASSERT_TRUE(msb[3] == 4);

	i = Protocol::bytes_to_int(msb, 0);
	ASSERT_TRUE(i == 4);
	
}

int main(int argc, char* argv[])
{
	if(t == 1)
	{
		::testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();
		cin.get();
		cin.get();
	}
	else
	{
		unsigned short port = 154;
		Server srv(port);
		cout << "Start server.\n";
		srv.Start();

	}
	
}


