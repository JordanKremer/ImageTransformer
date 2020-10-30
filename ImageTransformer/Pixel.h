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

	Pixel(std::vector<unsigned char>& channelData);
	Pixel(std::vector<int>::iterator, const int pixelLength);
	const unsigned char& GetChannel(const int channel);

private:

	std::vector<unsigned char> _channels;

};

