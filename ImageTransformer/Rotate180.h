#pragma once
#include "Transformation.h"

class Rotate180 :
	public Transformation
{
public:
	Rotate180();
	std::vector<Pixel> TransformPixels(std::vector<Pixel> pixels, const HeaderInfo* hdr);
	std::unique_ptr<HeaderInfo> TransformHeader(std::unique_ptr<HeaderInfo> header);
private:
	void Swap(std::vector<Pixel>& pixels, int curUpperBoundIdx, int curLowerBoundIdx);

};

