#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
#include <fstream>
#include <cmath>
using std::ifstream;

class Pixel {
    public:
        Pixel() : red(0), green(0), blue(0) {} //default
        Pixel(ifstream& file);

        int normalize(int min, int max);

        int getPixelValue();

        inline int Red() const {return red;}
        inline int Green() const {return green;}
        inline int Blue() const {return blue;}

    protected:
        int red;
        int green;
        int blue;
};

#endif // PIXEL_H
