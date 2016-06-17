#include <map>

class Storage
{
	void Set(char const &key, char const &val)
	{
		cont[key] = val;
	}
	int Get(int const &key)
	{
		if (cont.find(key) == cont.end())
		{
			return '\0';
		}
		return cont[key];
	}
protected:
	std::map<int, int> cont;
};
