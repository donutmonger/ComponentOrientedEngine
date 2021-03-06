#ifndef Mesh_h
#define Mesh_h

#include <iostream>

#include "includes/gl.hpp"
#include "includes/glm.hpp"

#include "ShaderProgram.hpp"
#include "VertexSpecification.hpp"

using namespace std;

struct MeshData {
public:
    MeshData(vector<GLfloat>& vertices, vector<GLuint>& elements) : vertices(vertices), elements(elements) {};

    vector<GLfloat>& vertices;
    vector<GLuint>& elements;

};

class Mesh {
public:
    Mesh(MeshData& mesh_data, VertexSpecification vertex_specification);

    void draw();
    void prepareToBeDrawn();
    void linkToShader(ShaderProgram& shader_program);

    int getNumberOfTriangles();

private:
    void bindVAO();
    void bindVBO();
    void createVAO();
    void createVBO(vector<GLfloat>& vertices);
    void createEBO(vector<GLuint>& elements);

    void sendMeshDataToOpenGL(MeshData& mesh_data);
    void setMeshStatsFromMeshData(MeshData& mesh_data);

    void setNumberOfElements(int number_of_elements);
    int getNumberOfElements();

    void drawAllElementsWireframe();
    void drawAllElementsSolid();
    void drawAllElements(GLint draw_mode);

    VertexSpecification& getVertexSpecification();

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    int number_of_elements;
    VertexSpecification vertex_specification;
};

#endif
