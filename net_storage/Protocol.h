#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

class Protocol
{
public:

	///*
	static void C_PackSetVal(char * pack, const int &key, const int &val)
	{
		//cout << "Key: " << key << " val: " << val << endl;

		pack[0] = 1; //Код "1" - установить значение
		int_to_bytes(pack, 1, key);
		int_to_bytes(pack, 5, val);
		//std::cout << "pack: " << (int)pack[0] << "___" << (int)pack[1] << "___" << (int)pack[2] << std::endl;
	}




	static void C_PackGetVal(char * pack, const int &key)
	{
		pack[0] = 2; //Код 2 - получить значение по ключу.
		int_to_bytes(pack, 1, key);
	}
	//

	static void C_PackDelVal(char *pack, const int &key)
	{
		pack[0] = 3;
		int_to_bytes(pack, 1, key);
	}
	//

	static int C_GetValFromPack(char *pack)
	{
		return bytes_to_int(pack, 1);
	}
	static void S_PackGetVal(char* answer_pakc, const int& val)
	{
		answer_pakc[0] = 1;
		int_to_bytes(answer_pakc, 1, val);
	}
	//


	
	static void S_PackError(char *pack)
	{
		pack[0] = 0;
	}

	static bool C_AnswerServOk(char *pack)
	{
		if(pack[0]==1)
		{
			return true;
		}
		return false;
	}

	static int  GetKey(char * pack)
	{
		return bytes_to_int(pack, 1);
	}
	static int GetVal(char * pack)
	{
		return bytes_to_int(pack, 5);
	}

	

	static bool VerOk(char *pack)
	{
		if (_ver_protocol == pack[0])
		{
			return true;
		}
		return false;
	}
	//
	
	static void PackProtocol(char* pack)
	{
		pack[0]=_ver_protocol;
	}
	//

	static void S_ErrorProtocol(char * pack)
	{
		pack[0] = _error_protocol;
	}
	//
	
	static const unsigned char _set_val = 1;
	static const unsigned char _get_val = 2;
	static const unsigned char _del_elem = 3;

protected:
	static void int_to_bytes(char* mass_bytes, const short &numb, const int &val)
	{

		int tmp_v;
		tmp_v = val;
		for (short i = 3; i > -1; --i, tmp_v >>= 8)
		{
			mass_bytes[numb + i] = 0;
			mass_bytes[numb + i] |= tmp_v;
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
	static const unsigned char size_pac = 3;

};

