#include "MyNormal.hpp"

using namespace models;
using namespace std;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
MyNormal::MyNormal(std::string normalPath, int normalCount)
    : normalPath(normalPath),
      normalCount(normalCount) {}
//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void MyNormal::loadNormal() {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* normBytes =
        stbi_load(this->normalPath.c_str(), &this->width, &this->height, &this->colorChannels, 0);

    glGenTextures(1, &this->normal);
    glActiveTexture(GL_TEXTURE0);
    switch (this->normalCount) {
        case 1:
            glActiveTexture(GL_TEXTURE1);
            break;
        case 3:
            glActiveTexture(GL_TEXTURE3);
            break;
        case 5:
            glActiveTexture(GL_TEXTURE5);
            break;
        case 7:
            glActiveTexture(GL_TEXTURE7);
            break;
        case 9:
            glActiveTexture(GL_TEXTURE9);
            break;
        case 11:
            glActiveTexture(GL_TEXTURE11);
            break;
        case 13:
            glActiveTexture(GL_TEXTURE13);
            break;
        case 15:
            glActiveTexture(GL_TEXTURE15);
            break;
        case 17:
            glActiveTexture(GL_TEXTURE17);
            break;
        case 19:
            glActiveTexture(GL_TEXTURE19);
            break;
    }
    glBindTexture(GL_TEXTURE_2D, this->normal);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    if (!normBytes) {
        cout << "ERROR: Model normal failed to load" << endl;
        return;
    } else {
        switch (this->colorChannels) {
            case 3:
                glTexImage2D(GL_TEXTURE_2D,
                             this->normalCount,  //? <- Texture Index
                             GL_RGB,
                             this->width,
                             this->height,
                             0,
                             GL_RGB,
                             GL_UNSIGNED_BYTE,
                             normBytes);
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_2D,
                             this->normalCount,  //? <- Texture Index
                             GL_RGBA,
                             this->width,
                             this->height,
                             0,
                             GL_RGBA,
                             GL_UNSIGNED_BYTE,
                             normBytes);
                break;
        }
        //? Mipmap: Low resolution versions of our texture for if we view the model from far
        // away,
        // we won't need to load as much detail
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(normBytes);
    }
    if (DEBUG_MODE) std::cout << this->normalPath + " loaded!" << std::endl;
}

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
GLuint MyNormal::getNormal() { return this->normal; }
void MyNormal::setNormal(GLuint normal) { this->normal = normal; }
std::string MyNormal::getNormalPath() { return this->normalPath; }
void MyNormal::setNormalPath(std::string normalPath) { this->normalPath = normalPath; }
int MyNormal::getWidth() { return this->width; }
void MyNormal::setWidth(int width) { this->width = width; }
int MyNormal::getHeight() { return this->height; }
void MyNormal::setHeight(int height) { this->height = height; }
int MyNormal::getColorChannels() { return this->colorChannels; }
void MyNormal::setColorChannels(int colorChannels) { this->colorChannels = colorChannels; }
int MyNormal::getNormalCount() { return this->normalCount; }
