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


#include "loader.h"
#include <fstream>



//C++ doesn't create a second copy for vector when returning it
//it just moves the data
std::vector<unsigned char> loader::load(std::string filename)
{

	std::ifstream in;

	in.open(filename, std::ios::binary);

	//exception is throw when using a loop with while(!in.eof), so using a range based for loop instead
	in.exceptions(in.failbit);

	//Go to end of file, get byte number, go back to beginning of file
	in.seekg(0, in.end);
	int fileLength = in.tellg();
	in.seekg(0, in.beg);

	unsigned char dataByte;
	std::vector<unsigned char> loadData;

	int reserveAmount = 2 * fileLength;
	loadData.reserve(reserveAmount);
	
	for (int i = 0; i < fileLength; ++i)
	{
		in.read((char*)& dataByte, 1);
		loadData.push_back(dataByte);
	}
	in.close();

	return loadData;
}


