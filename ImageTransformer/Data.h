#pragma once
#include <vector>
#include <memory>
#include "HeaderInfo.h"
class Data
{
public:
	Data();
	Data(std::vector<unsigned char> &data, std::shared_ptr<HeaderInfo> header);


private:
	std::shared_ptr<HeaderInfo> _header;
	std::vector<unsigned char> _rawData;

};

