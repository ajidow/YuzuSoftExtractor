#pragma once

#include "JSONProcessor.h"

class evImgCover {
public:
	void imageCover(std::string signalImageLocation);
private:
	JSON_Processor JSON_Reader;
};