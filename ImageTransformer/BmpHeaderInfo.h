#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>

class BmpHeaderInfo
{
public:
	BmpHeaderInfo();
	BmpHeaderInfo(std::vector<char>);

	//= operator
	//>> operator (ifstream& in)


private:
	int _translateDecimaltoRGBA(uint32_t mask);

	std::vector<const char> _headerData;
	std::map<std::string, int> _indexMap;
};

