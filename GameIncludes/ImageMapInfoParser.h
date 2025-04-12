#pragma once
#include "imageMapColour.h"
#include "iostream"
#include "string" 
#include "sstream"
#include "fstream"
#include "map"
class ImageMapInfoParser {

public:

	ImageMapInfoParser(){};
	~ImageMapInfoParser(){}
	std::map<imageMapColour, std::string> parseImageMapInfoFile(std::string& imageMapInfoPath);

	



private:




};