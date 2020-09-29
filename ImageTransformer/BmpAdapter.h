#pragma once
#include "Adapter.h"
#include "Pixel.h"
#include <memory>


class BmpAdapter :
	public Adapter
{
public:
	std::shared_ptr<Data> Adapt(std::vector<unsigned char>& data);

private:
	std::vector<Pixel>& LoadPixels(std::vector<unsigned char>& data, std::unique_ptr<BmpHeaderInfo> header);
};

