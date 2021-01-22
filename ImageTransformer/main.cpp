#include <opencv2/opencv.hpp>
#include <iostream>
#include "Applicator.h"
#include "AdapterFactory.h"
#include "TransformationFactory.h"
#include "Transformation.h"
#include "Data.h"
#include "Loader.h"
#include "Writer.h"



int main(int argc, char* argv[])
{
	//std::string FILENAME = "C:\\Users\\Krempire\\source\\repos\\ImageTransformer\\bear1_32.bmp";
	//std::string FILETYPE = "bmp";

	if (!argv[1] || !argv[2] || !argv[3])
		return 0;

	std::string FILENAME(argv[1]);
	std::string FILETYPE(argv[2]);

	std::string TRANSFORMATIONTYPE = "";
	std::string OUTFILENAME = "";


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