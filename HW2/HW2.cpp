#include <iostream>
#include "Image.h"

int main(int argc, char* argv[])
{
    if(argc != 3) {
        std::cerr << "Error: incorrect number of arguments provided" << std::endl;
        return -1;
    }

    Image img(argv[1], argv[2]);
    img.validPPM();
    return img.validComparison();
}