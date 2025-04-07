#ifndef PBM_WRITER_H
#define PBM_WRITER_H

#include "ImageWriter.h"
#include "Image.h"

#include<fstream>


class PBMWriter : public ImageWriter {
    public:

    int write(const std::string& filename, const Image& img) const override;
};

#endif //PBM_WRiter_H