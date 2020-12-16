#pragma once
#include <string>
#include "Adapter.h"
class AdapterFactory
{
public:
	std::unique_ptr<Adapter> GetAdapter(std::string fileType);

};

