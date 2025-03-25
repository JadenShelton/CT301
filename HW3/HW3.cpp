#include <iostream>
#include "Image.h"
#include "ChecksumGenerator.h"

int main(int argc, char* argv[])
{
    if(argc != 4) {
        std::cerr << "Error: incorrect number of arguments provided" << std::endl;
        return -1;
    }

    Image img(argv[1]);

    img.validPPM();
    img.storePixels();

    ChecksumGenerator generator(img, argv[2], argv[3]);
    
    return generator.generateRowChecksums() || generator.generateColumnChecksums();
}
