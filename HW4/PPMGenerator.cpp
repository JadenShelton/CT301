#include "PPMGenerator.h"

PPMGenerator::PPMGenerator(const std::string& filename, Image& img) : outFilename(filename), image(img) {}

int PPMGenerator::writePPM() {
    std::ofstream outFile(outFilename);

    if(!outFile.is_open()) {
        std::cerr << "Error: can't open file " << outFilename << std::endl;
        return -1;
    }

    outFile << "P3" << " " << image.getWidth() << " " << image.getHeight() << " " << "255" << std::endl;
    imagePixels = image.getNormPixels();

    for(int row = 0; row < image.getHeight(); row++){
        for(int col = 0; col < image.getWidth(); col++){
           outFile << imagePixels[row][col].Red() << std::endl;
           outFile << imagePixels[row][col].Green() << std::endl;
           outFile << imagePixels[row][col].Blue() << std::endl;
        }
    }

    return 0;
}