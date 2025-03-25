#include "ChecksumGenerator.h"

ChecksumGenerator::ChecksumGenerator(Image& img, const std::string& rowOutputFile, const std::string& colOutputFile) : image(img), rowOutputFilename(rowOutputFile), colOutputFilename(colOutputFile){}

int ChecksumGenerator::generateRowChecksums() {
    std::vector<std::vector<Pixel>> imagePixels = image.getPixels();
    std::ofstream outFile(rowOutputFilename);

    if(!outFile.is_open()) {
        std::cerr << "Error: can't open file " << rowOutputFilename << std::endl;
        return -1;
    }

    for(int row = 0; row < image.getHeight(); row++) {
        int rowSum = 0;
        for(int col = 0; col < image.getWidth(); col++) {
            rowSum += imagePixels[row][col].getPixelValue();
        }
        outFile << rowSum << std::endl;
    }

    outFile.close();
    return 0;
}

int ChecksumGenerator::generateColumnChecksums() {
    std::vector<std::vector<Pixel>> imagePixels = image.getPixels();
    std::ofstream outFile(colOutputFilename);

    if(!outFile.is_open()) {
        std::cerr << "Error: can't open file " << colOutputFilename << std::endl;
        return -1;
    }

    for(int col = 0; col < image.getWidth(); col++) {
        int colSum = 0;
        for(int row = 0; row < image.getHeight(); row++) {
            colSum += imagePixels[row][col].getPixelValue();
        }
        outFile << colSum << std::endl;
    }

    outFile.close();
    return 0;
}