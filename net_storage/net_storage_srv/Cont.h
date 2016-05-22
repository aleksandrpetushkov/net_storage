#include <map>


class Cont
{
	void Set(char const &key, char const &val)
	{
		cont[key] = val;
	}
	char Get(char const &key)
	{
		if(cont.find(key)==cont.end())
		{
			return '\0';
		}
		return cont[key];
	}

protected:
	std::map<char, char> cont;


};
