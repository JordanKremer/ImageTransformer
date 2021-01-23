//#include <opencv2/opencv.hpp>
#include <iostream>
//#include <boost/filesystem.hpp >
#include "Applicator.h"
#include "AdapterFactory.h"
#include "TransformationFactory.h"
#include "Transformation.h"
#include "Data.h"
#include "Loader.h"
#include "Writer.h"


//#include <boost/filesystem.hpp>

int main(int argc, char* argv[])
{

	std::string FILENAME("C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\bear1_32.bmp");
	std::string FILETYPE("bmp");
	std::string TRANSFORMATIONTYPE("rotate180");
	std::string OUTFILENAME("C:\\Users\\SkullHead\\source\\repos\\ImageTransformer\\Images\\test_new.bmp");

/*
* 	auto workingDirctory = boost::filesystem::current_path();
	if (!argv[1] || !argv[2] || !argv[3])
		return 0;

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


	try {
		auto rawImageByteValues = _loader->Load(FILENAME);
		auto adapter = adapterFac->GetAdapter(FILETYPE);
		auto genericAdaptedImage = adapter->AdaptFromRaw(rawImageByteValues);
		auto transformer = transformFac->GetTransformation(TRANSFORMATIONTYPE);
		auto transformedAdaptedImage = applicator->ApplyTransformation(std::move(genericAdaptedImage), std::move(transformer));
		auto transformedRawData = adapter->AdaptToRaw(std::move(transformedAdaptedImage));

		writer->WriteToFile(transformedRawData, OUTFILENAME);
	}
	catch (const std::runtime_error& error) {
		return 0;
	}

	return 0;
}