#include <iostream>
#include "Image.h"

int main(int argc, char* argv[])
{
    if(argc != 4) {
        std::cerr << "Error: incorrect number of arguments provided" << std::endl;
        return -1;
    }

    Image img(argv[1]);
    img.validPPM();
    img.storePixels();
    
}