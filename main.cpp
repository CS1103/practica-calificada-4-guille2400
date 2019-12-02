#include <iostream>
#include <vector>
#include <thread>
#include <string_view>
#include "lodepng.h"
#include "filter_Blue.h"
#include "green_Filter.h"
#include "red_Filter.h"
#include "decode_Encode.h"
#include "rotar_Imagen.h"
using namespace std;

void imprimir_Valores(string_view filename, std::vector<unsigned char>& image, unsigned w, unsigned h) {

    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w * 4; j += 4) {
            int r = image[i * w * 4 + j + 0]; // Red component
            int g = image[i * w * 4 + j + 1]; // Green component
            int b = image[i * w * 4 + j + 2]; // Blue component
            int a = image[i * w * 4 + j + 3]; // Alpha component
            std::cout << r << " ";
            std::cout << g << " ";
            std::cout << b << " ";
            std::cout << a << "|";
        }
        std::cout <<endl;
    }


    unsigned error = lodepng::encode(filename.data(), image, w, h);
    if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}

int main()
{
    unsigned int w;
    unsigned int h;
    auto image = decode("../in.png", w, h);
    //Idea de los 4 threads:
    //thread t1[4];
    //for(int i = 1; i<5;++i){
    //    t1[i] = thread([&image,&w,&h]{for(int i = 1; i<5;++i) blue_Filter("../Blue1_Filter.png",image,w*i/4,h*i/4);});}

    thread t1([&image,&w,&h]{blue_Filter("../Blue_Filter.png",image,w,h);});
    thread t2([&image,&w,&h]{red_Filter("../Red_Filter.png",image,w,h);});
    thread t3([&image,&w,&h]{green_Filter("../Green_Filter.png",image,w,h);});

    //Rotar:
    //thread t4([&image, &w, &h]{rotar_Imagen("../rotar_Imagen.png",image,w,h);});

    t1.join();
    t2.join();
    t3.join();
    //t4.join();

    return 0;
}
