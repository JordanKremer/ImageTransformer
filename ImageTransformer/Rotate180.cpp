#include "Rotate180.h"

std::unique_ptr<Data> Rotate180::Transform(std::unique_ptr<Data> adaptedData)
{
	/*
	vector<unsigned char>tmpVec;
	bool hasCountedWidth = false;
	for (int y = (Height - 1); y > -1; y--)
	{
		for (int x = (Width - 1); x > -1; x--)
		{
			pushPixelOntoVector(tmpVec, x, y);
			if (!hasCountedWidth)
				++scaledWidth;
		}
		hasCountedWidth = true;
		++scaledHeight;
	}
	pixelByte = tmpVec;
	*/

	adaptedData->_header;


	//data needs args for constructor
	//return std::move(std::make_unique<Data>());
	return nullptr;
}
