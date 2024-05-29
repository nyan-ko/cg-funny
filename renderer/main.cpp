#include "drawer.h"


int main(int argc, char **argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    TGAColor color(255, 100, 100, 255);
    // line(0, 0, 20, 40, image, color);
    triangle(40, 50, 10, 10, 70, 20, image, color);


    
    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}