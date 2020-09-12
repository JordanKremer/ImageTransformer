#pragma once
#include "Pixel.h"
class PixelAlpha :
	public Pixel
{
public:
	//get from base class
	PixelAlpha(int red, int green, int blue, int alpha);  //load the base class with those values

	int getAlpha();
private:

	int _alpha;
};

