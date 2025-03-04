#include "Pixel.h"

#include<string>
#include<iostream>
#include<fstream>
#include<vector>

class Image {
    public:
        Image(std::string input, std::string checksum);

        Image(std::string input);

        int loadPPM(ifstream& file);

        int validPPM();

        void storePixels();

        int validComparison();

    private:
        std::string filename;
        std::vector<std::vector<Pixel>> imagePixels;

        std::string magicNumber;
        int width;
        int height;
        int maxColorValue;

        std::string checksumName;

};
