#include "PGMWriter.h"


int PGMWriter::write(const std::string& filename, const Image& image) const {
    std::ofstream outFile(filename);

    if(!outFile.is_open()) {
        std::cerr << "Error: can't open file " << filename << std::endl;
        return -1;
    }

    outFile << "P2\n" << image.getWidth() << " " << image.getHeight() << " " << "\n255" << std::endl;
    const auto& pixels = image.getPixels();
    
    for(int row = 0; row < image.getHeight(); row++){
        for(int col = 0; col < image.getWidth(); col++){
            Pixel pixel = pixels[row][col];
            int intensity = std::round((pixel.Red() + pixel.Green() + pixel.Blue()) /3.0);
            outFile << intensity << "\n";
        }
    }

    return 0;
}
