#include "PixelAlpha.h"

PixelAlpha::PixelAlpha(int red, int green, int blue, int alpha):Pixel(red, green, blue)
{
	_alpha = alpha;
}

int PixelAlpha::getAlpha()
{
	return _alpha;
}
