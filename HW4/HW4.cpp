#include <iostream>
#include "Image.h"
#include "PPMGenerator.h"

int main(int argc, char* argv[])
{
    if(argc != 3) {
        std::cerr << "Error: incorrect number of arguments provided" << std::endl;
        return -1;
    }

    Image img(argv[1]);

    img.validPPM();
    img.storePixels();
    img.normalizePixels();
    img.getNormPixels();

    PPMGenerator fileGen(argv[2], img);
    return fileGen.writePPM();

    //std::cout << "Max = " << img.getMaxPixelValue() << std::endl;
    //std::cout << "Min = " << img.getMinPixelValue() << std::endl;
}
