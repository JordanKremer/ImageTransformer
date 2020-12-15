#include <opencv2/opencv.hpp>
#include <iostream>
#include "AdapterFactory.h"
#include "TransformationFactory.h"
#include "Transformation.h"
#include "BmpLoader.h"
#include "Data.h"


using namespace std;
using namespace cv;


int main(int argc, char* argv[])
{
	std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\bear1_32.bmp";
	std::string FILETYPE = "bmp";

	std::unique_ptr<Loader> _loader;
	auto rawData = _loader->Load(FILENAME);
	std::shared_ptr<Adapter> adapter;
	std::unique_ptr<AdapterFactory> adapterFac;


//https://stackoverflow.com/questions/27502968/how-do-i-implement-polymorphism-with-stdshared-ptr
//https://en.cppreference.com/w/cpp/memory/unique_ptr polymorphism with unique_ptr
	try {
		/*adapter = adapterFac->GetAdapter(FILETYPE);
		auto adaptedData = adapter->AdaptFromRaw(rawData);
		
		std::unique_ptr<TransformationFactory> transformFac;
		auto transformer = transformFac->GetTransformation(TRANSFORMATIONTYPE);
		
		auto transformedAdaptedData = transformer->Transform(adaptedData);
		auto transformedRawData = adapter->AdaptToRaw(transformedRawData);

		std::unique_ptr<FileWriter> writer;
		writer->WriteToFile(transformedRawData);
		*/
	}
	catch (const runtime_error& error) {
		return 0;
	}
}