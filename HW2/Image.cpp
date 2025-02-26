#include "Image.h"
#include<string>
#include<iostream>
#include<fstream>

using namespace std;

std::string filename;
std::string checksumName;

Image::Image(std::string input, std::string checksum) {
    filename = input;
    checksumName = checksum;
}

int Image::validPPM() {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: can't open file" << std::endl;
        return -1;
    }

    string magicNumber;
    file >> magicNumber;

    if (magicNumber != "P3") {
        cerr << "Error: Improper file header" << std::endl;
        return -1;
    }

    int width, height, maxColorValue;

    if (!(file >> width) || width <= 0) {
        cerr << "Error: Improper file width" << std::endl;
        return -1;
    }
    
    if (!(file >> height) || height <= 0) {
        cerr << "Error: Improper file height" << std::endl;
        return -1;
    }

    if (!(file >> maxColorValue) || maxColorValue <= 0 || maxColorValue > 255) {
        cerr << "Error: Improper max color value" << std::endl;
        return -1;
    }

    int expectedPixelValues = width * height * 3;
    int pixelValue;
    int totalPixels = 0;

    while(file >> pixelValue) {
        if(pixelValue < 0 || pixelValue > 255) {
            cerr << "Error: Invalid pixel value" << std::endl;
            return -1;
        }
        totalPixels++;
    }

    if(expectedPixelValues !=  totalPixels) {
        cerr << "Error: Incorrect number of pixels" << std::endl;
        return -1;
    }
    
    cout << "PPM format is valid!" << endl;
    return 0;
}

int Image::validComparison() {
    ifstream ppmFile(filename);
    ifstream checksumFile(checksumName);

    if (!ppmFile.is_open()) {
        cerr << "Error: can't open ppm file" << std::endl;
        return -1;
    }

    if (!checksumFile.is_open()) {
        cerr << "Error: can't open checksum file" << std::endl;
        return -1;
    }
    
    string magicNumber;
    int width, height, maxColorValue;
    ppmFile >> magicNumber;
    ppmFile >> width;
    ppmFile >> height;
    ppmFile >> maxColorValue;

    for(int row = 0; row < height; row++) {
        int rowSum = 0;
        int pixelValue;

        for(int i = 0; i < width * 3; i++) {
            ppmFile >> pixelValue;
            rowSum += pixelValue;
        }

        int checksumValue;
        if (!(checksumFile >> checksumValue)) {
            cerr << "Error: not enough checksums provided" << std::endl;
            return -1;
        }

        if(rowSum != checksumValue) {
            cerr << "Error: row sum does not equal checksum on row: " << row + 2 << std::endl;
            return -(row + 2);
        }

    }

    int extraChecksum;
    if(checksumFile >> extraChecksum) {
        cerr << "Error: extra entries in checksum" << std::endl;
        return -1;
    }

    cout << "Checksum complete and correct!" << endl;
    return 0;
}



