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

	auto bmpHeader = fac.getBmpHeader(data);	

	return std::make_shared<Data>(_rawData, bmpHeader);
}

