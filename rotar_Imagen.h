//
// Created by sanch on 12/2/2019.
//

#ifndef PC4_ROTAR_IMAGEN_H
#define PC4_ROTAR_IMAGEN_H
#include <vector>
#include <iostream>
#include <thread>
#include <cmath>
#include "decode_Encode.h"
#include "lodepng.h"
using namespace std;
template <typename T, typename  P>
void rotar_Imagen(string_view filename, vector<T> imagen, P width, P height) {
    vector<unsigned char> temporal;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width * 4; j += 4) {
            temporal.push_back(imagen[(i * width * 4 + j + 0) * cos(45)]); // Red component
            temporal.push_back(imagen[(i * width * 4 + j + 1) * cos(45)]); // Green component
            temporal.push_back(imagen[(i * width * 4 + j + 2) * cos(45)]); // Blue component
            temporal.push_back(imagen[(i * width * 4 + j + 3) * sin(45)]); // Opacidad
        }
    }
    unsigned error = lodepng::encode(filename.data(), imagen, width, height);
    if (error) {
        cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}
#endif //PC4_ROTAR_IMAGEN_H
