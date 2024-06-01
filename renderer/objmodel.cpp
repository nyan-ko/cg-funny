#include "sys/stat.h"
#include <fstream>

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
        if (line[0] == 'v') {
            sscanf(line.c_str(), "v %lf %lf %lf", &vertices[vertex_idx].x, &vertices[vertex_idx].y, &vertices[vertex_idx].z);
            vertex_idx++;
        }
        else if (line[0] == 'f') {
            sscanf(line.c_str(), "f %d %d %d", &faces[face_idx].vertex_idx1, &faces[face_idx].vertex_idx2, &faces[face_idx].vertex_idx3);
            face_idx++;
        }
    }
    model->set_vertices(vertices);
    model->set_faces(faces);

    return model;
}