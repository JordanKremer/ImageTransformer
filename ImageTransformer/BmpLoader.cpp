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

	ifstream in;

	in.open(_FILENAME, ios::binary);

	if (!in.is_open())
		throw std::invalid_argument("Failure to open file / File doesn't exist");
	
	
	char ID[2];
	in >> ID[0] >> ID[1];

	//simple header check, not great validation
	if (ID[0] != 'B' && ID[1] != 'M')
		throw std::invalid_argument("INVALID BMP: BITMAP ID INCORRECT"); //include ID in error?

	//Check for all parts of the bitmap to be sure?

	

	

	return make_shared<Data>();
}