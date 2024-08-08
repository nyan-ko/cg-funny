#include "sys/stat.h"
#include <fstream>
#include <sstream>

#include "objmodel.h"

// OBJModel::OBJModel() : vertex_count(0), face_count(0) {}

OBJModel::~OBJModel() throw() {
    if (vertices) {
        free(vertices);
    }
    if (faces) {
        free(faces);
    }
}

int OBJModel::get_num_vertices() {
    return vertex_count;
}

void OBJModel::set_num_vertices(int num) {
    vertex_count = num;
}

Vertex OBJModel::get_vertex(int index) {
    return vertices[index];
}

void OBJModel::set_vertices(Vertex *vertices) {
    this->vertices = vertices;
}

int OBJModel::get_num_faces() {
    return face_count;
}

void OBJModel::set_num_faces(int num) {
    face_count = num;
}

Face OBJModel::get_face(int index) {
    return faces[index];
}

void OBJModel::set_faces(Face *faces) {
    this->faces = faces;
}



bool file_exists(char *path) {
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

OBJModel *load_obj(char *path) {
    if (!file_exists(path)) {
        return NULL;
    }

    int vertex_count = 0;
    int face_count = 0;

    std::ifstream obj(path);
    std::string line;
    while (std::getline(obj, line)) {
        if (line[0] == 'v') {
            vertex_count++;
        }
        else if (line[0] == 'f') {
            face_count++;
        }
    }

    OBJModel *model = (OBJModel *) malloc(sizeof(OBJModel));
    model->set_num_vertices(vertex_count);
    model->set_num_faces(face_count);
    Vertex *vertices = (Vertex *) malloc(sizeof(Vertex) * vertex_count);
    Face *faces = (Face *) malloc(sizeof(Face) * face_count);

    obj.clear();
    obj.seekg(0, std::ios::beg);

    int vertex_idx = 0;
    int face_idx = 0;
    while (std::getline(obj, line)) {
        std::istringstream iss(line.c_str());
        char trash;
        if (line[0] == 'v') {
            iss >> trash;
            
            for (int i = 0; i < 3; i++) {
                iss >> vertices[vertex_idx].raw[i];
            }
            vertex_idx++;
        }
        else if (line[0] == 'f') {
            int int_trash;
            iss >> trash;

            
            int vertex_id;
            int i = 0;
            // Only need the first value in each chunk, account for possible additional texture detail in this chunk
            // (see obj file format documentation)
            // Adapted from Dmitry V. Sokolov's tinyrenderer repository:
            // https://github.com/ssloy/tinyrenderer/blob/f6fecb7ad493264ecd15e230411bfb1cca539a12/model.cpp
            while (iss >> vertex_id >> trash >> int_trash >> trash >> int_trash) {
                // Obj vertex id starts from 1
                vertex_id--;
                faces[face_idx].raw[i] = vertex_id;
                i++;
            }
            face_idx++;
        }
    }
    model->set_vertices(vertices);
    model->set_faces(faces);

    return model;
}