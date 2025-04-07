#include "PPMWriter.h"


int PPMWriter::write(const std::string& filename, const Image& image) const {
    std::ofstream outFile(filename);

    if(!outFile.is_open()) {
        std::cerr << "Error: can't open file " << filename << std::endl;
        return -1;
    }

    outFile << "P3\n" << image.getWidth() << " " << image.getHeight() << " " << "\n255" << std::endl;
    const auto& pixels = image.getPixels();

    for(int row = 0; row < image.getHeight(); row++){
        for(int col = 0; col < image.getWidth(); col++){
           outFile << pixels[row][col].Red() << std::endl;
           outFile << pixels[row][col].Green() << std::endl;
           outFile << pixels[row][col].Blue() << std::endl;
        }
    }

    return 0;
}
