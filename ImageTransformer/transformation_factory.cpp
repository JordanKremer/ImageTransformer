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
#include "transformation_factory.h"
#include "pixelate.h"
#include "rotate180.h"



std::unique_ptr<transformation> transformation_factory::get_transformation(std::string transformation_type) {
	if (transformation_type == "")
		throw std::runtime_error("ERROR | TRANSFORMATIONFACTORY::GETTRANSFORMATION() : EMPTY STRING TRANSFORMATIONTYPE");

	if (transformation_type == "rotate180")
	{
		return std::move(std::make_unique<rotate180>());
	}
	else if (transformation_type == "pixelate")
	{
		return std::move(std::make_unique<pixelate>());
	}
	else {
		return nullptr;
	}

}


