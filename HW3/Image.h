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

        int getWidth() const {
            return width;
        }

        int getHeight() const {
            return height;
        }

    private:
        std::string filename;
        std::vector<std::vector<Pixel>> imagePixels;

        std::string magicNumber;
        int width;
        int height;
        int maxColorValue;

        std::string checksumName;

        int loadPPM(ifstream& file);

};
