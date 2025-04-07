#include "PBMWriter.h"


int PBMWriter::write(const std::string& filename, const Image& image) const {
    std::ofstream outFile(filename);

    if(!outFile.is_open()) {
        std::cerr << "Error: can't open file " << filename << std::endl;
        return -1;
    }

    outFile << "P1\n" << image.getWidth() << " " << image.getHeight() << "\n" << std::endl;
    const auto& pixels = image.getPixels();
    
    for(int row = 0; row < image.getHeight(); row++){
        for(int col = 0; col < image.getWidth(); col++){
            Pixel pixel = pixels[row][col];
            int value = (pixel.Red() + pixel.Green() + pixel.Blue()) > 382.5 ? 1 : 0;
            outFile << value << "\n";
        }
    }
    
    return 0;
}
