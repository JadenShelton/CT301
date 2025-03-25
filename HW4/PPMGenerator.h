#ifndef PPMGenerator_H
#define PPMGenerator_H

#include "Image.h"
#include "Pixel.h"

#include<string>
#include<iostream>
#include<fstream>
#include<vector>

class PPMGenerator {
    public:
    PPMGenerator(const std::string& filename, Image& img);

    int writePPM();

    private:
    std::string outFilename;
    std::vector<std::vector<Pixel>> imagePixels;
    Image image;
};

#endif //PPMGenerator_H