#pragma once
#include <vector>

struct Channels {
	static inline const int BLACK = 0;
	static inline const int RED = 0;
	static inline const int GREEN = 1;
	static inline const int BLUE = 2;
	static inline const int ALPHA = 3;
};

class Pixel
{
public:

	Pixel(std::vector<int>& channelData);
	const int GetChannel(int channel);

private:

	std::vector<int> _channels;

};

