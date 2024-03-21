#include "MyTexture.hpp"

using namespace models;
using namespace std;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
MyTexture::MyTexture(std::string texturePath, int textureCount)
    : texturePath(texturePath),
      textureCount(textureCount) {
    if (DEBUG_MODE) std::cout << this->texturePath + " initialized!" << std::endl;
}

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void MyTexture::loadTexture() {
    stbi_set_flip_vertically_on_load(true);
    unsigned char* texBytes =
        stbi_load(this->texturePath.c_str(), &this->width, &this->height, &this->colorChannels, 0);

    glGenTextures(1, &this->texture);
    glActiveTexture(GL_TEXTURE0);
    switch (this->textureCount) {
        case 0:
            glActiveTexture(GL_TEXTURE0);
            break;
        case 1:
            glActiveTexture(GL_TEXTURE1);
            break;
        case 2:
            glActiveTexture(GL_TEXTURE2);
            break;
        case 3:
            glActiveTexture(GL_TEXTURE3);
            break;
        case 4:
            glActiveTexture(GL_TEXTURE4);
            break;
        case 5:
            glActiveTexture(GL_TEXTURE5);
            break;
        case 6:
            glActiveTexture(GL_TEXTURE6);
            break;
        case 7:
            glActiveTexture(GL_TEXTURE7);
            break;
        case 8:
            glActiveTexture(GL_TEXTURE8);
            break;
        case 9:
            glActiveTexture(GL_TEXTURE9);
            break;
    }
    glBindTexture(GL_TEXTURE_2D, this->texture);

    if (!texBytes) {
        cout << "ERROR: Model texture failed to load" << endl;
        return;
    } else {
        switch (this->colorChannels) {
            case 3:
                glTexImage2D(GL_TEXTURE_2D,
                             this->textureCount,  //? <- Texture Index
                             GL_RGB,
                             this->width,
                             this->height,
                             0,
                             GL_RGB,
                             GL_UNSIGNED_BYTE,
                             texBytes);
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_2D,
                             this->textureCount,  //? <- Texture Index
                             GL_RGBA,
                             this->width,
                             this->height,
                             0,
                             GL_RGBA,
                             GL_UNSIGNED_BYTE,
                             texBytes);
                break;
        }
        //? Mipmap: Low resolution versions of our texture for if we view the model from far away,
        // we won't need to load as much detail
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(texBytes);
    }
}

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
GLuint MyTexture::getTexture() { return this->texture; }
void MyTexture::setTexture(GLuint texture) { this->texture = texture; }
std::string MyTexture::getTexturePath() { return this->texturePath; }
void MyTexture::setTexturePath(std::string texturePath) { this->texturePath = texturePath; }
int MyTexture::getWidth() { return this->width; }
void MyTexture::setWidth(int width) { this->width = width; }
int MyTexture::getHeight() { return this->height; }
void MyTexture::setHeight(int height) { this->height = height; }
int MyTexture::getColorChannels() { return this->colorChannels; }
void MyTexture::setColorChannels(int colorChannels) { this->colorChannels = colorChannels; }
int MyTexture::getTextureCount() { return this->textureCount; }
