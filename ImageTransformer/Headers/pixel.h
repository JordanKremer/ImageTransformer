/*
Author : Jordan Kremer
11/20/20
pixel.h

This class acts as a container for the pixels values. Pixels are variable length vectors
with a defined number of channels, holding unsigned char byte values. This makes for a convenient
way to manage pixel values.

*/


#pragma once
#include <vector>

struct channels {
	static inline const int ONE_BIT_COLOR = 0;
	static inline const int FOUR_BIT_COLORS = 0;
	static inline const int EIGHT_BIT_COLORS = 0;
	static inline const int RED = 0;
	static inline const int GREEN = 1;
	static inline const int BLUE = 2;
	static inline const int ALPHA = 3;
};



class pixel
{
public:
	pixel();
	pixel(std::vector<unsigned char>& channel_data, int channels);
	pixel(std::vector<int>::iterator, const int num_channels);
	pixel& operator+(const pixel& p);
	pixel& operator=(const pixel& p) = default;

	const unsigned char& get_channel(const int channel) const;
	const std::vector<unsigned char>& get_all_channel_data() const;
	const int get_channel_count()const;
	void set_channel(int channel_idx, int channel_value);
	void set_all_channels(std::vector<unsigned char> new_channels);
	void set_all_channels(std::vector<int> new_channels);

private:
	std::vector<unsigned char> channels_;
	int channel_count_;

};

