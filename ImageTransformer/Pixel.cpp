/*
Author : Jordan Kremer
11/20/20
Pixel.cpp

This class acts as a container for the pixels values. Pixels are variable length vectors
with a defined number of channels, holding unsigned char byte values. This makes for a convenient 
way to manage Pixel values.

*/

#include "Pixel.h"



Pixel::Pixel(std::vector<unsigned char>& channelData, int channelCount)
{
	_channels = channelData;
	_channelCount = channelCount;
}


//TODO 
//Try to find a way to use a generic iterator so it doesn't
//have to care about a predefined one

Pixel::Pixel(std::vector<int>::iterator, const int numChannels)
{

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
	return _channelCount;
}

void Pixel::SetChannel(int channelIdx, int channelValue)
{
	if (channelIdx >= _channels.size()) {
		throw std::runtime_error("ERROR | PIXEL::SETCHANNEL():CHANNELIDX OUT OF RANGE");
	}
	else {
		_channels[channelIdx] = channelValue;
	}

}


void Pixel::SetAllChannels(std::vector<unsigned char> newChannels)
{
	if (_channels.size() != newChannels.size())
	{
		throw std::out_of_range("ERROR | PIXEL::SETALLCHANNELS() : NEWCHANNEL SIZE INCOMPATIBLE");
	}

	_channels = newChannels;
}

Pixel Pixel::operator+(const Pixel& p)
{
	if (p.GetChannelCount() != this->GetChannelCount())
		throw std::runtime_error("ERROR | Pixel::operator+ : MISMATCH CHANNELCOUNT");
	
	std::vector<unsigned char> channelData;
	channelData = this->GetAllChannelData();

	

	for (int i = 0; i < this->GetChannelCount(); ++i)
	{
		channelData[i] += + p._channels[i];
	}

	Pixel pixel(channelData, this->GetChannelCount());
	return pixel;
}
