#include "Pixel.h"

Pixel::Pixel(std::vector<unsigned char>& channelData)
{
	_channels = channelData;
}

const unsigned char& Pixel::GetChannel(const int channel)
{
	if (channel >= _channels.size())
	{
		std::string msg = "ERROR: GETCHANNEL(): CHANNEL SELECTION OUT OF RANGE";
		throw std::out_of_range(msg);
	}
	else {
		return _channels[channel];
	}
}

const std::vector<unsigned char>& Pixel::GetAllChannelData()
{
	return _channels;
}

const int Pixel::GetChannelCount()
{
	return channelCount;
}
