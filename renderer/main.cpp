#include "drawer.h"
#include "objmodel.h"

#include <iostream>

int main(int argc, char **argv) {
    TGAImage image(800, 800, TGAImage::RGB);
    TGAColor color(255, 100, 100, 255);
    // line(0, 0, 20, 40, image, color);
    // triangle(40, 50, 10, 10, 70, 20, image, color);

    if (argc > 1) {
        OBJModel *model = load_obj(argv[1]);
        if (model != NULL) {

            for (int i = 0; i < model->get_num_faces(); i++) {
                Face face = model->get_face(i);
                Vertex v1 = model->get_vertex(face.raw[0]);
                Vertex v2 = model->get_vertex(face.raw[1]);
                Vertex v3 = model->get_vertex(face.raw[2]);

                // std::cout << v1.raw[0] << " " << v1.raw[1] << " " << v1.raw[2] << std::endl;
                // std::cout << v2.raw[0] << " " << v2.raw[1] << " " << v2.raw[2] << std::endl;
                // std::cout << v3.raw[0] << " " << v3.raw[1] << " " << v3.raw[2] << std::endl;
                // std::cout << "-----" << std::endl;
            }
        }
        else {
            std::cout << "HELP" << std::endl;
        }
    }
    // triangle(10, 70, 50, 10, 80, 80, image, color);
    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}