//
// Created by sanch on 12/2/2019.
//

#ifndef PC4_DECODE_ENCODE_H
#define PC4_DECODE_ENCODE_H
#include <iostream>
using namespace std;

void encode(string_view filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
    unsigned error = lodepng::encode(filename.data(), image, width, height);
    if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }

}


vector<unsigned char> decode (string_view filename, unsigned int& width, unsigned int& height) {

    std::vector<unsigned char> result;
    unsigned error = lodepng::decode(result, width, height, filename.data());
    if (error) {
        cerr << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
    return result;
}

#endif //PC4_DECODE_ENCODE_H
