#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include "Image.h"
#include<string>

class ImageWriter {
    public:
    virtual ~ImageWriter() {}
    virtual int write(const std::string& filename, const Image& img) const = 0;

    static ImageWriter* createWriter(const std::string& filename);
};

#endif //IMAGE_WRITER_H