#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>

class BmpHeaderInfo
{
public:

	virtual const int getCompression() = 0;
	virtual std::shared_ptr<const char> getByte(int headerIndex);
	//= operator = 0
	//>> operator (ifstream& in) = 0
	//const int getWidth() = 0;

};

