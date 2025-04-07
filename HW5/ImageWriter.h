#ifndef IMAGE_WRITER_H
#define IMAGE_RITER_H

#include "Image.h"
#include "PPMWriter.h"
#include "PGMWriter.h"
#include "PBMWriter.h"
#include<string>

class ImageWriter {
    public:
    virtual ~ImageWriter() {}
    virtual int write(const std::string& filename, const Image& img) const = 0;

    static ImageWriter* createWriter(const std::string& filename);
};

#endif //IMAGE_WRITER_H