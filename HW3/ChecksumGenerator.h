#include"Image.h"
#include <string>
#include <fstream>

class ChecksumGenerator {
    public:
        ChecksumGenerator(Image& img, const std::string& rowOutputFile, const std::string& colOutputFile);

        int generateRowChecksums();

        int generateColumnChecksums();

    private:
        Image& image;
        std::string rowOutputFilename;
        std::string colOutputFilename;


};