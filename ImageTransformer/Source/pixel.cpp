/*
MIT License

Copyright(c) 2021 Jordan Kremer

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include "../Headers/pixel.h"
#include <stdexcept>



pixel::pixel()
{
	channel_count_ = 0;
}

pixel::pixel(std::vector<unsigned char>& channel_data, int channelCount)
{
	channels_ = channel_data;
	channel_count_ = channelCount;
}



pixel::pixel(std::vector<int>::iterator, const int num_channels)
{
	channel_count_ = 0;
}



const unsigned char& pixel::get_channel(const int channel) const
{
	if (channel >= channels_.size())
	{
		std::string msg = "ERROR: GETCHANNEL(): CHANNEL SELECTION OUT OF RANGE";
		throw std::out_of_range(msg);
	}
	else {
		return channels_[channel];
	}
}



const std::vector<unsigned char>& pixel::get_all_channel_data()const
{
	return channels_;
}



const int pixel::get_channel_count()const
{
	return channel_count_;
}



void pixel::set_channel(int channel_idx, int channel_value)
{
	if (channel_idx >= channels_.size()) {
		throw std::runtime_error("ERROR | PIXEL::SETCHANNEL():CHANNELIDX OUT OF RANGE");
	}
	else {
		channels_[channel_idx] = channel_value;
	}

}



void pixel::set_all_channels(std::vector<int> new_channels) {

	if (channels_.size() != new_channels.size())
	{
		throw std::out_of_range("ERROR | PIXEL::SETALLCHANNELS() : NEWCHANNEL SIZE INCOMPATIBLE");
	}

	for (int channelIdx = 0; channelIdx < channel_count_; ++channelIdx)
	{
		channels_[channelIdx] = new_channels[channelIdx] % 256;
	}
}



void pixel::set_all_channels(std::vector<unsigned char> new_channels)
{
	if (channels_.size() != new_channels.size())
	{
		throw std::out_of_range("ERROR | PIXEL::SETALLCHANNELS() : NEWCHANNEL SIZE INCOMPATIBLE");
	}

	channels_ = new_channels;
}



pixel& pixel::operator+(const pixel& p2)
{
	if (p2.get_channel_count() != this->get_channel_count())
		throw std::runtime_error("ERROR | pixel::operator+ : MISMATCH CHANNELCOUNT");

	for (int i = 0; i < this->get_channel_count(); ++i)
	{
		this->channels_[i] += + p2.channels_[i];
	}

	return *this;
}


