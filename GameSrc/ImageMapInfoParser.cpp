#include "ImageMapInfoParser.h"
#pragma once


// parsing tile image map info files as each image map for tiles will have colours that relate to a specifc tile object 
// each tile that needs an string id object has a string id mapped to it and this function will read files that associate a specfic colour
//within the tile image map to a tile id making it easier to quickly create an image map and write a simple text file that maps string id's to colours 
std::map<imageMapColour, std::string> ImageMapInfoParser::parseImageMapInfoFile(std::string& imageMapInfoPath)
{
    std::map<imageMapColour, std::string> parsedData; 
    std::ifstream file;
    std::istringstream inputData;
    std::string line; 

    file.open(imageMapInfoPath); 

    if (!file.is_open()) {
        std::cout << "could not find  path to tile map info " << imageMapInfoPath << std::endl;
    }
    std::cout << "PARSING TILE IMAGE MAP  path: " << imageMapInfoPath << std::endl;
    while (std::getline(file, line)) {

        if (line.find(":") != std::string::npos) {

            std::string tileNameId = line.substr(0, line.find(":") ); // get the tile id associated with the colour 
            line.erase(0, line.find(":") + 1); 

            float r, g, b, a; // parse the colour data
            inputData >> r;
            inputData >> g;
            inputData >> b;
            inputData >> a;
            // construct the imagMapColour struct and insert it as a key to the parsed id value
            imageMapColour temp = imageMapColour(r, g, b, a);
       

            parsedData.insert(std::pair<imageMapColour, std::string>(temp, tileNameId));

            continue; // move to next file

        }

        // log any errors 
        std::cout << "line did not have id marker ':'" << std::endl;
       
    }

    return parsedData;
}
