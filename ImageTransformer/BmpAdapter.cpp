#include "BmpAdapter.h"
#include "BmpHeaderFactory.h"
#include "BmpHeaderInfo_24Bit.h"
#include "BmpHeaderInfo_32Bit.h"
#include <memory>
#include <stdexcept>

std::shared_ptr<Data> BmpAdapter::Adapt(std::vector<unsigned char>& data)
{
	//Build new data object with a header and the raw data

	//first send a cut of the vector to the bmpheader contructor
	//but find out which bmpheader we need first, somehow 

	if (!(data[0] == 'B' && data[1] == 'M'))
	{
		throw std::runtime_error("ERROR: NOT A BMP");
	}

	std::vector<unsigned char> _rawData;

	BmpHeaderFactory fac;

	//cannot do this as it is trying to assign a unique ptr to something else
	//auto bmpHeader = fac.getBmpHeader(data);	

	auto bmpHeader = std::move(fac.getBmpHeader(data));
	uint32_t compression = bmpHeader->GetCompression();
	uint32_t bitsPerPixel = bmpHeader->GetBitsPerPixel();


	return std::make_shared<Data>(_rawData, bmpHeader);
}

std::vector<Pixel>& BmpAdapter::LoadPixels(std::vector<unsigned char>& rawdata, std::unique_ptr<BmpHeaderInfo> header)
{
	std::vector<Pixel> pixelData;

	int padding = ((header->GetWidth() * header->GetBitsPerPixel()) % 32) / 8;
	int startOfImage = header->GetImageStartOffset();

	uint32_t widthIndexCount = 0;

	int byteCount = header->GetBitsPerPixel() % 8;
	int leftOverBits = byteCount % 8;


	/*
		*In a while loop:
			create pixels from the data
			load a vector with the pixels
			SKIP PADDING, SO DO THE CALCULATION FOR PADDING FIRST
				the padding is saved in the data vector, so skip over
				those vector indices

				When writing the vector back to file, add the padding per line.
			
	
		return the vector
	
	
	*/




	if (leftOverBits == 4) {
		//4 bit image

	}
	else if (leftOverBits == 1)
	{
		//1 bit image
	}

	for (int idx = startOfImage; idx < rawdata.size(); ++idx)
	{

		//pixelData.push_back();
	}

	
}

