#pragma once
class Pixel
{

	Pixel(int red, int green, int blue);

	//add const correctness
	int getRed();
	int getGreen();
	int getBlue();
private:
	int _red;
	int _green;
	int _blue;
};

