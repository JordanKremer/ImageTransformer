#include "Pixel.h"

Pixel::Pixel(std::vector<unsigned char>& channelData)
{
	_channels = channelData;
}

const unsigned char& Pixel::GetChannel(const int channel) const
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

const std::vector<unsigned char>& Pixel::GetAllChannelData()const
{
	return _channels;
}

const int Pixel::GetChannelCount()const
{
	return channelCount;
}
