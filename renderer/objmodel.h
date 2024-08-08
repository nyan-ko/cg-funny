

struct Vertex {
    double raw[3];
};

struct Face {
    int raw[3];

    // Face(int vertex_idx1, int vertex_idx2, int vertex_idx3) : vertex_idx1(vertex_idx1), vertex_idx2(vertex_idx2), vertex_idx3(vertex_idx3) {}
};

class OBJModel {
private:
    int vertex_count;
    Vertex *vertices;
    int face_count;
    Face *faces;

public:
    OBJModel() : vertex_count(0), face_count(0) {};
    ~OBJModel() throw();

    int get_num_vertices();
    void set_num_vertices(int num);
    Vertex get_vertex(int index);
    void set_vertices(Vertex *vertices);
    int get_num_faces();
    void set_num_faces(int num);
    Face get_face(int index);
    void set_faces(Face *faces);
};

OBJModel *load_obj(char *path);

bool file_exists(char *path);