#ifndef IMAGE_H
#define IMAGE_H


#include "Pixel.h"

#include<string>
#include<iostream>
#include<fstream>
#include<vector>

class Image {
    public:
        Image(std::string input, std::string checksum);

        Image(std::string input);

        int validPPM();

        void storePixels();

        int validComparison();

        const std::vector<std::vector<Pixel>>& getPixels() const {
            return imagePixels;
        }

        const std::vector<std::vector<Pixel>>& getNormPixels() const {
            return normImagePixels;
        }

        int getWidth() const {
            return width;
        }

        int getHeight() const {
            return height;
        }

        int getMaxPixelValue() const {
            return maxPixelValue;
        }

        int getMinPixelValue() const {
            return minPixelValue;
        }
        
        int normalizePixels();

    private:
        std::string filename;
        std::vector<std::vector<Pixel>> imagePixels;
        int maxPixelValue;
        int minPixelValue;

        std::string magicNumber;
        int width;
        int height;
        int maxColorValue;

        std::string checksumName;

        int loadPPM(ifstream& file);

        std::vector<std::vector<Pixel>> normImagePixels;

};

#endif //IMAGE_H