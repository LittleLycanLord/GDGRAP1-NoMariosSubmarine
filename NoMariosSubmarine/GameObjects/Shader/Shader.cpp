#include "Shader.hpp"

using namespace models;
using namespace std;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Shader::Shader(std::string path, ShaderType type) : path(path), type(type) {}

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void Shader::loadShader() {
    this->file = fstream(this->path);
    this->buffer << this->file.rdbuf();
    this->shaderString = this->buffer.str();
    this->charArray    = this->shaderString.c_str();

    switch (this->type) {
        case ShaderType::FRAGMENT:
            this->shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        case ShaderType::VERTEX:
            this->shader = glCreateShader(GL_VERTEX_SHADER);
            break;
    }
    glShaderSource(this->shader, 1, &this->charArray, NULL);
    glCompileShader(this->shader);

    if (DEBUG_MODE) std::cout << this->path + " loaded!" << std::endl;
}

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
GLuint Shader::getShader() { return this->shader; }
