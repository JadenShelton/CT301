#include <Pixel.h>
 
Pixel::Pixel(ifstream& file) {
    file >> red;
    file >> green;
    file >> blue;
}

int Pixel::pixelValue() {
    return red + green + blue;
}
