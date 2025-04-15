#include <iostream>
#include <memory>
#include "Image.h"
#include "ImageWriter.h"

int main(int argc, char* argv[])
{
    if(argc != 3) {
        std::cerr << "Error: incorrect number of arguments provided" << std::endl;
        return -1;
    }

    Image img(argv[1]);

    std::cout << "Validating..." << std::endl;
    if (img.validImage() != 0) {
        return -1;
    }

    std::cout << "Storing pixels..." << std::endl;
    img.storePixels();

    std::cout << "Normalizing..." << std::endl;
    img.normalizePixels();

    //conversion logic
    std::cout << "Converting..." << std::endl;
    std::string outFile = argv[2];
    if (outFile.size() >= 4 && outFile.substr(outFile.size() - 4) == ".ppm") {
        img.convertToColor();
    }
    else if (outFile.size() >= 4 && outFile.substr(outFile.size() - 4) == ".pgm") {
        img.convertToGrayscale();
    }
    else if (outFile.size() >= 4 && outFile.substr(outFile.size() - 4) == ".pbm") {
        img.convertToBinary();
    }
    else {
        std::cerr << "Error: unknown output file format" << std::endl;
        return -1;
    }

    std::cout << "Writing..." << std::endl;
    
    std::unique_ptr<ImageWriter> writer(ImageWriter::createWriter(outFile));
    if(!writer) {
        std::cerr << "Error: unknown output file format" << std::endl;
        return -1;
    }  
    
    return writer->write(outFile, img);
}

