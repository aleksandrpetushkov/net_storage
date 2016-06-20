#include <SFML/Network.hpp>

using namespace sf;

class Protocol
{
public:
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
	static void Prarser_rece_pack(char *buf, char *answer)
	{
		switch (buf[0])
		{
		case _setval:
			int key, val;
			key = bytes_to_int(buf, 1);
			val = bytes_to_int(buf, 5);

			break;
		case _getval:
			break;
		}
	}
	//
	static bool n_ver_p(const unsigned char &ver_protocol) 
	{
		if (_ver_protocol == ver_protocol)
		{
			return true;
		}
		return false;
	}
	//
	
	static unsigned char GetProtocol()
	{
		return _ver_protocol;
	}
	//

	static unsigned char ErrorProtocol()
	{
		return _error_protocol;
	}
	//

	static unsigned char GetSizPack()
	{
		return _size_pack;
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
			result <<= 8;
			result |= (unsigned char)mass_bytes[numb + i];
		}
		return result;
	}
	static const unsigned char _ver_protocol=1;
	static const unsigned char _error_protocol=0;


	static const unsigned char _size_pack = 3;
	static const unsigned char _setval = 1;
	static const unsigned char _getval = 2;
	static const unsigned char size_pac = 3;

};

