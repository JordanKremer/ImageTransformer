#include "AdapterFactory.h"
#include "BmpAdapter.h"

Adapter* AdapterFactory::GetAdapter(std::string fileType)
{
	if (fileType == ".bmp" || fileType == ".BMP")
	{
		return new BmpAdapter();
	}
}
