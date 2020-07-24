#pragma once
#include "BmpLoader.h"
BmpLoader::BmpLoader(std::string FILENAME) {
	_FILENAME = FILENAME;
}

std::string BmpLoader::getFileName() const {
	return _FILENAME;
}
