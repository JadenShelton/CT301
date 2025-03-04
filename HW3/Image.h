#include <string>

class Image {
    public:
        Image(std::string input, std::string checksum);

        Image(std::string input);

        int validPPM();

        int validComparison();

    private:
        std::string filename;
        std::string checksumName;

};
