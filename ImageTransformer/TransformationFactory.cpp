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
#include "TransformationFactory.h"
#include "Gaussian.h"
#include "Pixelate.h"
#include "Rotate180.h"



std::unique_ptr<Transformation> TransformationFactory::GetTransformation(std::string transformationType) {
	if (transformationType == "")
		throw std::runtime_error("ERROR | TRANSFORMATIONFACTORY::GETTRANSFORMATION() : EMPTY STRING TRANSFORMATIONTYPE");

	if (transformationType == "rotate180")
	{
		return std::move(std::make_unique<Rotate180>());
	}
	else if (transformationType == "pixelate")
	{
		return std::move(std::make_unique<Pixelate>());
	}
	else {
		return nullptr;
	}

}


