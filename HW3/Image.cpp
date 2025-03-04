#include "Image.h"
using namespace std;

Image::Image(std::string input, std::string checksum) {
    filename = input;
    checksumName = checksum;
}

Image::Image(std::string input) {
    filename = input;
    checksumName = nullptr;
}

int Image::loadPPM(ifstream& file) {

    if (!file.is_open()) {
        cerr << "Error: can't open file" << endl;
        return -1;
    }

    file >> magicNumber;

    if (magicNumber != "P3") {
        cerr << "Error: Improper file header" << endl;
        return -1;
    }

    if (!(file >> width) || width <= 0) {
        cerr << "Error: Improper file width" << endl;
        return -1;
    }
    
    if (!(file >> height) || height <= 0) {
        cerr << "Error: Improper file height" << endl;
        return -1;
    }

    if (!(file >> maxColorValue) || maxColorValue <= 0 || maxColorValue > 255) {
        cerr << "Error: Improper max color value" << endl;
        return -1;
    }

    return 0;
}

int Image::validPPM() {
    ifstream file(filename);

    loadPPM(file);

    int expectedPixelValues = width * height * 3;
    int pixelValue;
    int totalPixels = 0;

    while(file >> pixelValue) {
        if(pixelValue < 0 || pixelValue > 255) {
            cerr << "Error: Invalid pixel value" << endl;
            return -1;
        }
        totalPixels++;
    }

    if(expectedPixelValues !=  totalPixels) {
        cerr << "Error: Incorrect number of pixels" << endl;
        return -1;
    }
    
    cout << "PPM format is valid!" << endl;
    return 0;
}



void Image::storePixels() {
    imagePixels = std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width));
    
}

int Image::validComparison() {
    ifstream ppmFile(filename);
    ifstream checksumFile(checksumName);

    if (!ppmFile.is_open()) {
        cerr << "Error: can't open ppm file" << endl;
        return -1;
    }

    if (!checksumFile.is_open()) {
        cerr << "Error: can't open checksum file" << endl;
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
            cerr << "Error: not enough checksums provided" << endl;
            return -1;
        }

        if(rowSum != checksumValue) {
            cerr << "Error: row sum does not equal checksum on row: " << row + 2 << endl;
            return -(row + 2);
        }

    }

    int extraChecksum;
    if(checksumFile >> extraChecksum) {
        cerr << "Error: extra entries in checksum" << endl;
        return -1;
    }

    cout << "Checksum complete and correct!" << endl;
    return 0;
}



