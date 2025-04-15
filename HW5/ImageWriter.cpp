#include "ImageWriter.h"
#include "PPMWriter.h"
#include "PGMWriter.h"
#include "PBMWriter.h"

ImageWriter* ImageWriter::createWriter(const std::string& filename) {
    if(filename.substr(filename.size() - 4) == ".ppm") return new PPMWriter();
    if(filename.substr(filename.size() - 4) == ".pgm") return new PGMWriter();
    if(filename.substr(filename.size() - 4) == ".pbm") return new PBMWriter();
    return nullptr;
}
