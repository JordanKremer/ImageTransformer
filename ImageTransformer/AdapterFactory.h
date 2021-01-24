#pragma once
#include <string>
#include "Adapter.h"
class AdapterFactory
{
public:
	//Each supported filetype will need a different adapter to convert to GenericImage
	std::unique_ptr<Adapter> GetAdapter(std::string fileType);
};

