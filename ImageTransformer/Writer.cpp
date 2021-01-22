#include "Writer.h"

void Writer::WriteToFile(std::vector<unsigned char> rawImageData, const std::string FILENAME)
{
	std::ofstream out;
	out.open(FILENAME, std::ios::binary | std::ios::out);
	assert(out.is_open());
	
	for (auto& byte : rawImageData)
	{
		out.write((char*)& byte, sizeof(byte));
	}

	out.close();
}
