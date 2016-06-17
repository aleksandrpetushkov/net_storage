#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;

class Client
{
public:
	void start(std::string const &ip, short const &port)
	{
		if(sock.connect("localhost", 154) == Socket::Done)
		{
			connect = true;
		}
	}
	bool Connect()
	{
		return connect;
	}
	void Send(const char mas[])
	{
		sock.send(mas, sizeof(mas));
	}
	bool Received(void *data)
	{
		size_t received = 0;
		if(sock.receive(data, 1, received)==TcpSocket::Disconnected)
		{
			return true;
		}
		return false;
	}
	void SetVal(const int &key, const int &val)
	{

		
		/*
		int tmp_k, tmp_v;
		tmp_k = key;
		tmp_v = val;
		char pack[9];
		pack[0] = 1;
		pack[1] |= tmp_k;
		tmp_k <= 8;
		pack[2] |= tmp_k;
		tmp_k <= 8;
		pack[3] |= tmp_k;
		tmp_k <= 8;
		pack[4] |= tmp_k;
		pack[5] |= tmp_v;
		tmp_k <= 8;
		pack[2] |= tmp_v;
		tmp_v <= 8;
		pack[3] |= tmp_v;
		tmp_v <= 8;
		pack[4] |= tmp_v;
		//*/

		if(sock.receive(data, 1, received) == TcpSocket::Disconnected)
		{
			
		}
	}
	void int_to_bytes(char* mass_bytes, const short &numb, const int &val)
	{

		int tmp_v;
		tmp_v = val;
		//cout << bitset<32>(tmp_v) << "___"  << endl;
		for (short i = 3; i > -1; --i, tmp_v >>= 8)
		{
			mass_bytes[numb + i] = 0;
			mass_bytes[numb + i] |= tmp_v;
			//cout << bitset<32>(tmp_v) << "___" << bitset<8>(mass_bytes[numb + i]) << endl;
			//cout << (int)mass_bytes[numb + i] << "___";
			//cout << tmp_v << endl;
		}
	}

	int bytes_to_int(char *mass_bytes, const short &numb)
	{
		int result(0);
		for (short i = 0; i < 4; ++i)
		{
			//result=0;
			result <<= 8;
			result |= (unsigned char)mass_bytes[numb + i];
			//cout << bitset<32>(result) << "___" << bitset<8>(mass_bytes[numb + i]) << endl;
		}
		return result;
	}


protected:
	TcpSocket sock;
	bool connect = false;

};

