#include <iostream>
#include <fstream>
using std::ifstream;

class Pixel {
    public:
        Pixel(ifstream& file);

        int pixelValue();

        inline int Red() const {return red;}
        inline int Green() const {return green;}
        inline int Blue() const {return blue;}

    protected:
        int red;
        int green;
        int blue;
};