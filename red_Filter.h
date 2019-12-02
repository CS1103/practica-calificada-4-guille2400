//
// Created by sanch on 12/2/2019.
//

#ifndef PC4_RED_FILTER_H
#define PC4_RED_FILTER_H
#include <vector>
#include <iostream>
#include <thread>
#include "decode_Encode.h"
#include "lodepng.h"
using namespace std;
template <typename T, typename P>
void red_Filter(string_view filename, T image, P width, P height)
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width * 4; j += 4)
        {
            image[(i * width * 4 + j + 1)]=0; // Green component
            image[(i * width * 4 + j + 2)]=0; // BLue component

        }
    }
    unsigned error = lodepng::encode(filename.data(), image, width, height);
    if (error) {
        cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}
#endif //PC4_RED_FILTER_H
