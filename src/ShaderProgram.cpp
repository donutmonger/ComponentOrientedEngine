#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(){
    gl_shader_id = 0;
}

ShaderProgram::ShaderProgram(ShaderFile& vertex_shader, ShaderFile& fragment_shader) {

    create();
    combineShaderPrograms(vertex_shader, fragment_shader);
    bindFragmentDataLocation();
    link();
    printErrors();
}

ShaderProgram ShaderProgram::createFromFiles(string vertex_shader_filename, string fragment_shader_filename) {

    ShaderFile vertex_shader(vertex_shader_filename, GL_VERTEX_SHADER);
    ShaderFile fragment_shader(fragment_shader_filename, GL_FRAGMENT_SHADER);

    return ShaderProgram(vertex_shader, fragment_shader);
}

void ShaderProgram::create() {
    gl_shader_id = glCreateProgram();
}

GLuint ShaderProgram::getGLId() {
    return gl_shader_id;
}

void ShaderProgram::use() {
    glUseProgram(getGLId());
}

GLint ShaderProgram::getUniformLocation(string uniform_name) {
    return glGetUniformLocation(getGLId(), uniform_name.c_str());
}

GLint ShaderProgram::getAttributeLocation(string attribute_name) {
    return glGetAttribLocation(getGLId(), attribute_name.c_str());
}

void ShaderProgram::combineShaderPrograms(ShaderFile& vertex_shader, ShaderFile& fragment_shader) {

    vertex_shader.attachTo(gl_shader_id);
    fragment_shader.attachTo(gl_shader_id);

}

void ShaderProgram::bindFragmentDataLocation() {
    glBindFragDataLocation(gl_shader_id, 0, "outColor");
}

void ShaderProgram::link() {
    glLinkProgram(gl_shader_id);
}

string ShaderProgram::getErrors() {
    char info_log[512] = "";
    if (hasErrors()){
        glGetProgramInfoLog(getGLId(), 512, NULL, info_log);
    }

    return string(info_log);
}

bool ShaderProgram::hasErrors() {
    GLint status;
    glGetProgramiv(getGLId(), GL_LINK_STATUS, &status);
    return status == GL_FALSE;
}

void ShaderProgram::printErrors() {
    if (hasErrors()) {
        cout << "Error linking shader:\n" << getErrors() << "\n";
    }
}
