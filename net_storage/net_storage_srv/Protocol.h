#include <SFML\Network.hpp>


class Protocol
{
public:
	Protocol(const sf::TcpSocket &sc,const char ver_protocol)
	{
		if(ver_protocol!=_ver_protocol)
		{
			throw "Bad version protocol";
		}
	}
	static bool n_ver_p(const char ver_protocol) //Провера версиис протокола
	{
		if(_ver_protocol==ver_protocol)
		{
			return true;
		}
		return false;
	}

protected:
	static char _ver_protocol;
	
};
char Protocol::_ver_protocol = 1;
