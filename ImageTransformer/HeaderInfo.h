#pragma once
#include <stdint.h> //for uint_32, causes an Override error without it

class HeaderInfo
{
public:
	_NODISCARD virtual  const uint32_t GetCompression()=0;
};

