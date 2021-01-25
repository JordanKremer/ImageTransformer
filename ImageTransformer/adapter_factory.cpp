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


#include "adapter_factory.h"
#include "bmp_adapter.h"
#include <stdexcept>

std::unique_ptr<Adapter> adapter_factory::get_adapter(std::string file_type)
{
	//Assumes that file_type accounts for case before function is called
	if (file_type == "bmp")
	{
		std::unique_ptr<bmp_adapter> adapter = std::make_unique<bmp_adapter>();
		return std::move(adapter);
	}
	else {
		throw std::runtime_error("ERROR: INVALID FILETYPE EXTENSION");
	}

	return nullptr;
}

