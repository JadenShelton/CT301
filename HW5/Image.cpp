#include "Image.h"
using namespace std;

Image::Image(std::string input, std::string checksum) {
    filename = input;
    checksumName = checksum;
}

Image::Image(std::string input) {
    filename = input;
    checksumName = "";
}

int Image::loadImage(ifstream& file) {

    if (!file.is_open()) {
        cerr << "Error: can't open file" << endl;
        return -1;
    }

    file >> magicNumber;

    if (magicNumber == "P3") {
        type = COLOR;
    } else if (magicNumber == "P2") {
        type = GRAYSCALE;
    } else if (magicNumber == "P1") {
        type = BINARY;
    } else {
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
    if(type != BINARY) {
        if (!(file >> maxColorValue) || maxColorValue <= 0 || maxColorValue > 255) {
            cerr << "Error: Improper max color value" << endl;
            return -1;
        }
    } else {
        maxColorValue = 1;
    }

    return 0;
}

int Image::validImage() {
    ifstream file(filename);
    if(loadImage(file) != 0) {
        return -1;
    }
    
    int expectedPixelValues = width * height;
    if (type == COLOR) expectedPixelValues *= 3;

    int pixelValue;
    int totalPixels = 0;

    maxPixelValue = 0;
    minPixelValue = 255;

    while(file >> pixelValue) {
        totalPixels++;
        
        if(type == BINARY) {
            if(pixelValue != 0 && pixelValue != 1) {
                std::cerr << "Error: Invalid binary pixel value" << std::endl;
                return -1;
            }
        } else {
            if(pixelValue < 0 || pixelValue > 255) {
                cerr << "Error: Invalid pixel value" << endl;
                return -1;
            }
        }
        
        if(pixelValue > maxPixelValue) {
            maxPixelValue = pixelValue;
        }

        if(pixelValue < minPixelValue) {
            minPixelValue = pixelValue;
        }
    }

    if(expectedPixelValues !=  totalPixels) {
        cerr << "Error: Incorrect number of pixels" << endl;
        return -1;
    }
    
    cout << "Image format is valid!" << endl;
    return 0;
}



void Image::storePixels() {
    imagePixels = std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width));
    ifstream imageFile(filename);

    loadImage(imageFile);

    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            if(type == BINARY) {
                int bit;
                imageFile >> bit;

                if(bit != 0 && bit != 1) {
                    std::cerr << "Error: Invalid binary pixel value" << std::endl;
                    return;
                }

                int val = 255 * bit;
                imagePixels[row][column] = Pixel(val, val, val);
            } else if (type == GRAYSCALE) {
                int gray;
                imageFile >> gray;
                if(gray < 0 || gray > 255) {
                    std::cerr << "Error: Invalid grascale pixel value" << std::endl;
                    return;
                }
                imagePixels[row][column] = Pixel(gray, gray, gray);
            } else {
                imagePixels[row][column] = Pixel(imageFile);
            }
        }
    }
}

int Image::normalizePixels() {
    if(type == BINARY) return 0;
    
    normImagePixels = std::vector<std::vector<Pixel>>(height, std::vector<Pixel>(width));
    Pixel curr; 

    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            curr = imagePixels[row][col];
            curr.normalize(minPixelValue, maxPixelValue);
            normImagePixels[row][col] = curr;
        }
    }
    return 0;
}

int Image::validComparison() {
    ifstream ppmFile(filename);
    ifstream checksumFile(checksumName);

    loadImage(ppmFile);

    if (!checksumFile.is_open()) {
        cerr << "Error: can't open checksum file" << endl;
        return -1;
    }


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

void Image::convertToGrayscale() {
    if(type == GRAYSCALE) return;

    std::cout << "Converting to grayscale: type=" << type << ", w=" << width << ", h=" << height << std::endl;

    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col) {
            int r = imagePixels[row][col].Red();
            int g = imagePixels[row][col].Green();
            int b = imagePixels[row][col].Blue();
            int intensity = std::round((r + g + b) / 3.0);
            imagePixels[row][col] = Pixel(intensity, intensity, intensity);
        }
    }

    type = GRAYSCALE;

}

void Image::convertToBinary() {
    if(type == BINARY) return;

    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col) {
            int pixelVal;
            if(type == COLOR) {
                int r = imagePixels[row][col].Red();
                int g = imagePixels[row][col].Green();
                int b = imagePixels[row][col].Blue();
                if((r + g + b) > 382.5) {
                    pixelVal = 1;
                } else {
                    pixelVal = 0;
                }
            } else {
                int intensity = imagePixels[row][col].Red();
                if(intensity > 127.5) {
                    pixelVal = 1;
                } else {
                    pixelVal = 0;
                }
            }
            imagePixels[row][col] = Pixel(255 * pixelVal, 255 * pixelVal, 255 * pixelVal);
        }
    }
    type = BINARY;
}

void Image::convertToColor() {
    if(type == COLOR) return;

    for(int row = 0; row < height; ++row){
        for(int col = 0; col < width; ++col) {
            int intensity = std::round((imagePixels[row][col].Red() + imagePixels[row][col].Green() + imagePixels[row][col].Blue())/ 3.0);
            imagePixels[row][col] = Pixel(intensity, intensity, intensity);
        }
    }
    type = COLOR;
}




