#pragma once
#include <string>
#include "Adapter.h"
class adapter_factory
{
public:
	//Each supported filetype will need a different adapter to convert to generic_image
	std::unique_ptr<Adapter> get_adapter(std::string file_type);
//test
};

