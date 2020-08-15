#pragma once
#include "Data.h"
#include "BmpHeaderInfo.h"
class BmpData :
	public Data
{
public:
	BmpData();

private:
	std::shared_ptr<BmpHeaderInfo> _headerInfo;
};

