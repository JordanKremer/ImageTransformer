#include "Pixel.h"

Pixel::Pixel(int red, int green, int blue) {
	_red = red;
	_green = green;
	_blue = blue;

}

int Pixel::getRed()
{
	return _red;
}

int Pixel::getGreen()
{
	return _green;
}

int Pixel::getBlue()
{
	return _blue;
}
