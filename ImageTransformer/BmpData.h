#pragma once
#include "Data.h"
#include "BmpHeaderInfo.h"
class BmpData :
	public Data
{
public:
	BmpData();

private:
	BmpHeaderInfo _headerInfo;
};

