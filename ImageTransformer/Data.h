#pragma once
#include <vector>
#include <memory>
#include "HeaderInfo.h"
#include "BmpHeaderInfo.h"
class Data
{
public:
	Data();
	Data(std::vector<unsigned char> &data, std::unique_ptr<HeaderInfo> header);


private:
	std::unique_ptr<HeaderInfo> _header;
	std::vector<unsigned char> _rawData;

};

