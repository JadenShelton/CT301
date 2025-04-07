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

    img.validImage();
    img.storePixels();
    img.normalizePixels();

    //conversion logic

    std::unique_ptr<ImageWriter> writer(ImageWriter::createWriter(argv[2]));
    if(!writer) {
        std::cerr << "Error: unknown output file format" << std::endl;
        return -1;
    }  
    
    return writer->write(argv[2], img);
}

