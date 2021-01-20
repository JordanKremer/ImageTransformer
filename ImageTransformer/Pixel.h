/*
Author : Jordan Kremer
11/20/20
Pixel.h

This class acts as a container for the pixels values. Pixels are variable length vectors
with a defined number of channels, holding unsigned char byte values. This makes for a convenient
way to manage Pixel values.

*/


#pragma once
#include <vector>
#include <stdexcept>

struct Channels {
	static inline const int ONE_BIT_COLOR = 0;
	static inline const int FOUR_BIT_COLORS = 0;
	static inline const int EIGHT_BIT_COLORS = 0;
	static inline const int RED = 0;
	static inline const int GREEN = 1;
	static inline const int BLUE = 2;
	static inline const int ALPHA = 3;
};

class Pixel
{
public:
	Pixel(std::vector<unsigned char>& channelData, int channels);
	Pixel(std::vector<int>::iterator, const int numChannels);
	Pixel operator+(const Pixel& p);

	const unsigned char& GetChannel(const int channel) const;
	const std::vector<unsigned char>& GetAllChannelData() const;
	const int GetChannelCount()const;
	void SetChannel(int channelIdx, int channelValue);
	void SetAllChannels(std::vector<unsigned char> newChannels);

private:

	std::vector<unsigned char> _channels;
	int _channelCount;

};

