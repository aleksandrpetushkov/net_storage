#include <SFML/Network.hpp>

using namespace sf;

class Protocol
{
public:
	/*
	Protocol(const TcpSocket &sock)
	{
		tcp
	}
	//*/
	static bool SetVal(const int & key, const int &val, TcpSocket &soc)
	{
		char pack[9];
		pack[0] = 1; //Код "1" - установить значение
		int_to_bytes(pack, 1, key);
		int_to_bytes(pack, 5, val);
		if(soc.send(pack, 9)==TcpSocket::Done)
		{
			return true;
		}
		return false;
	}
	static int GetVal(const int &key, TcpSocket &soc)
	{
		int result;
		char pack[5];
		pack[0] = 2; //Код 2 - получить значение по ключу.
		int_to_bytes(pack, 1, key);
		if (soc.send(pack, 5) == TcpSocket::Done)
		{
			std::size_t receive = 0;
			if(soc.receive(pack, 5, receive)==TcpSocket::Done)
			{
				result = bytes_to_int(pack, 0);
				return result;
			}
			else
			{
				throw "Error received data.\n";
			}
		}
		else
		{
			throw "Error transmission request.\n";
		}
	}


protected:
	static void int_to_bytes(char* mass_bytes, const short &numb, const int &val)
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

	static int bytes_to_int(char *mass_bytes, const short &numb)
	{
		int result(0);
		for (short i = 0; i < 4; ++i)
		{
			//result=0;
			result <<= 8;
			result |= (unsigned char)mass_bytes[numb + i];
			//cout << bitset<32>(result) << "___" << bitset<8>(mass_bytes[numb + i]) << "___" << (int)mass_bytes[numb+i] << endl;

		}
		return result;
	}

};
