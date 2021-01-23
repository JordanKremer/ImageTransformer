#include "Rotate180.h"



std::vector<Pixel> Rotate180::TransformPixels(std::vector<Pixel> pixels)
{
	//hdr is pull from the abstract base Transformation class
	auto hdr = GetHeader();
	
	if (!hdr) {
		throw std::runtime_error("ERROR | ROTATE180::TRANSFORMPIXELS(): FAILED TO SET HEADER");
	}
		
	uint32_t imageWidth = hdr->GetWidth();
	uint32_t imageHeight = hdr->GetHeight();

	if (imageHeight * imageWidth > pixels.size())
		throw std::runtime_error("ERROR | ROTATE180.TRANSFORMPIXELS(): INVALID IMAGE DIMENSIONS, CANNOT TRANSFORM");
	std::reverse(pixels.begin(), pixels.end());
	return pixels;
}



//Nothing changes dimension or otherwise for the header for this transformation
std::unique_ptr<HeaderInfo> Rotate180::TransformHeader(std::unique_ptr<HeaderInfo> hdr)
{
	//No op function
	return std::move(hdr);
}



