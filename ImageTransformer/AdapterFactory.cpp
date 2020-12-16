#include "AdapterFactory.h"
#include "BmpAdapter.h"
#include <exception>

std::unique_ptr<Adapter> AdapterFactory::GetAdapter(std::string fileType)
{
	//Assumes that fileType accounts for case before function is called
	if (fileType == "bmp")
	{
		std::unique_ptr<BmpAdapter> adapter = std::make_unique<BmpAdapter>();
		return std::move(adapter);
	}
	else {
		std::runtime_error("ERROR: INVALID FILETYPE EXTENSION");
	}

	return nullptr;
}

