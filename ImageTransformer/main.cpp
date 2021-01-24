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


#include <iostream>
#include "Applicator.h"
#include "AdapterFactory.h"
#include "TransformationFactory.h"
#include "Transformation.h"
#include "Data.h"
#include "Loader.h"
#include "Writer.h"
//#include <windows.h>


int main(int argc, char* argv[])
{

	std::string FILENAME("C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp");
	std::string FILETYPE("bmp");
	std::string TRANSFORMATIONTYPE("rotate180");
	std::string OUTFILENAME("C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_new.bmp");


	//Not necessesary as the user and/or UI can point to the file location 
	/*
	char pBuf[256];
	size_t len = sizeof(pBuf);
	int bytes = GetModuleFileName(NULL, pBuf, len);
	*/
/*

	std::string FILENAME(argv[1]);
	std::string FILETYPE(argv[2]);
	std::string TRANSFORMATIONTYPE(argv[3]);
	std::string OUTFILENAME(argv[4]);
*/

	std::unique_ptr<Loader> _loader = std::make_unique<Loader>();
	std::unique_ptr<Writer> writer = std::make_unique<Writer>();
	std::unique_ptr<AdapterFactory> adapterFac = std::make_unique<AdapterFactory>();
	std::unique_ptr<TransformationFactory> transformFac = std::make_unique<TransformationFactory>();
	std::unique_ptr<Applicator> applicator = std::make_unique<Applicator>();;

	//Load -> Adapt to generic -> Transform image -> Adapt back to byte vector -> Write to disk
	try {
		auto rawImageByteValues = _loader->Load(FILENAME);
		auto adapter = adapterFac->GetAdapter(FILETYPE);
		auto genericAdaptedImage = adapter->AdaptFromRaw(rawImageByteValues);
		auto transformer = transformFac->GetTransformation(TRANSFORMATIONTYPE);
		auto transformedAdaptedImage = applicator->ApplyTransformation(std::move(genericAdaptedImage), std::move(transformer));
		auto transformedRawData = adapter->AdaptToRaw(std::move(transformedAdaptedImage));

		writer->WriteToFile(transformedRawData, OUTFILENAME);
	}
	catch (const std::out_of_range& oor)
	{
		std::cout << oor.what();
	}
	catch (const std::runtime_error& error) {
		std::cout << error.what();
	}


	return 0;
}