#include "Pixel.h"
 
Pixel::Pixel(ifstream& file) {
    file >> red;
    file >> green;
    file >> blue;
}

int Pixel::getPixelValue() {
    return red + green + blue;
}

int Pixel::normalize(int min, int max) {
    red = std::round((red - min) * (255.0 / (max - min)));
    green = std::round((green - min) * (255.0 / (max - min)));
    blue = std::round((blue - min) * (255.0 / (max - min)));
    
    return 0;
}
