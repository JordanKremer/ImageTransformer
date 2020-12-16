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

	//Iterator can be used more generically, that even though
	//it may be less efficient than pass the vector, it means that
	//it doesn't care what the data structure is 
	Pixel(std::vector<int>::iterator, const int numChannels);
	const unsigned char& GetChannel(const int channel) const;
	const std::vector<unsigned char>& GetAllChannelData() const;
	const int GetChannelCount()const;

private:

	std::vector<unsigned char> _channels;
	int _channelCount;

};

