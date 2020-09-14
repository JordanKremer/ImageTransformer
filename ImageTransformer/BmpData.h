#pragma once
#include "Data.h"
#include "BmpHeaderInfo.h"


class BmpData :
	public Data
{
public:
	BmpData();
	BmpData(std::vector<unsigned char>& data, std::shared_ptr<HeaderInfo> bmpHeader);

private:
	std::shared_ptr<BmpHeaderInfo> _headerInfo;
};

