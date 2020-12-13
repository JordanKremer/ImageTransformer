#pragma once
#include <string>
#include "Adapter.h"
class AdapterFactory
{
public:
	Adapter* GetAdapter(std::string fileType);
	
};

