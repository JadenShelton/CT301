#ifndef PPM_WRITER_H
#define PPM_WRITER_H

#include "ImageWriter.h"
#include "Image.h"

#include<fstream>


class PPMWriter : public ImageWriter {
    public:

    int write(const std::string& filename, const Image& img) const override;
};

#endif //PPM_WRiter_H