#pragma once

#include "JSONProcessor.h"
#include <iostream>
#include <io.h>

class evImgCover {
public:
	void imageCover(std::string signalImageLocation);
	std::string getFileLocation();
	void SetFileAfterFix(const char *FAF);
	void fun();
	void Begin(const char* jsonstr);
private:
	JSONProcessor JSON_Reader;
	std::string fileAfterFix;
	int fileNumber;
	std::string fileLocation;
	std::string jsonFileLocation;
	std::string originalImageLocation;
	char originalImageCode;
	struct coordinate {
		int x;
		int y;
		int from;
		int to;
	}Position;
};