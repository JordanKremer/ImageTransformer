#pragma once
#include "BmpLoader.h"
#include <fstream>
using namespace std;

BmpLoader::BmpLoader(std::string FILENAME) {
	_FILENAME = FILENAME;
}

std::string BmpLoader::getFileName() const {
	return _FILENAME;
}


std::shared_ptr<Data> BmpLoader::Load() {

	fstream in;

	in.open(_FILENAME, ios::binary);

	if (!in.is_open())
		throw "Failure to open file / File doesn't exist";
	

	return make_shared<Data>();
}