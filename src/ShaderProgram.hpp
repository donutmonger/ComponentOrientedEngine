#ifndef Shader_h
#define Shader_h

#include <string>
#include <fstream>
#include <iostream>

#include "includes/gl.hpp"

#include "ShaderFile.hpp"

using namespace std;

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(ShaderFile& vertex_shader, ShaderFile& fragment_shader);

    static ShaderProgram createFromFiles(string vertex_shader_filename, string fragment_shader_filename);

    void use();
    GLint getUniformLocation(string uniform_name);
    GLint getAttributeLocation(string attribute_name);

    string getErrors();
    bool hasErrors();

    GLuint getGLId();

private:
    void create();
    void combineShaderPrograms(ShaderFile& vertex_shader, ShaderFile& fragment_shader);
    void bindFragmentDataLocation();
    void link();

    void printErrors();

    GLuint gl_shader_id;

};

#endif
