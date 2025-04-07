#ifndef PGM_WRITER_H
#define PGM_WRITER_H

#include "ImageWriter.h"
#include "Image.h"

#include<fstream>


class PGMWriter : public ImageWriter {
    public:

    int write(const std::string& filename, const Image& img) const override;
};

#endif //PGM_WRiter_H