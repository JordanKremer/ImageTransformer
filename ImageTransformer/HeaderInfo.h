#pragma once
#include <stdint.h> //for uint_32, causes an Override error without it

class HeaderInfo
{
public:
	 virtual const uint32_t GetCompression()=0;
};

