#ifndef IMAGE_H
#define IMAGE_H


#include "Pixel.h"

#include<string>
#include<iostream>
#include<fstream>
#include<vector>

enum ImageType { COLOR, GRAYSCALE, BINARY };

class Image {
    public:
        Image(std::string input, std::string checksum);

        Image(std::string input);

        int validImage();

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

        ImageType getType() const { 
            return type; 
        }
        
        int normalizePixels();

        void convertToGrayscale();

        void convertToBinary();

        void convertToColor();

    private:
        std::string filename;
        std::vector<std::vector<Pixel>> imagePixels;
        int maxPixelValue;
        int minPixelValue;


        std::string magicNumber;
        ImageType type;
        int width;
        int height;
        int maxColorValue;

        std::string checksumName;

        int loadImage(ifstream& file);

        std::vector<std::vector<Pixel>> normImagePixels;

};

#endif //IMAGE_H