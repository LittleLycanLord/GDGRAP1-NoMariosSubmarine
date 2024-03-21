#include "Model3D.hpp"

using namespace models;
using namespace std;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Model3D::Model3D(std::string name,
                 std::string modelPath,
                 int textureCount,
                 std::string texturePath,
                 glm::vec3 position,
                 glm::mat4 positionMatrix,
                 glm::vec3 scale,
                 glm::vec3 orientation)
    : name(name),
      texture(texturePath, textureCount),
      texturePath(texturePath),
      modelPath(modelPath),
      position(position),
      positionMatrix(positionMatrix),
      scale(scale),
      orientation(orientation),
      VAO(0),
      VBO(0) {
    if (DEBUG_MODE) std::cout << this->name + " initialized!" << std::endl;
}

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void Model3D::loadModel() {
    if (this->texturePath != "") this->texture.loadTexture();
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;
    tinyobj::attrib_t attributes;

    if (!tinyobj::LoadObj(
            &attributes, &shapes, &material, &warning, &error, this->modelPath.c_str())) {
        cout << "ERROR: Model failed to load" << endl;
        return;
    } else {
        for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
            tinyobj::index_t vData = shapes[0].mesh.indices[i];
            //* Positions
            this->fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3)]);
            this->fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 1]);
            this->fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 2]);
            //* Normals
            this->fullVertexData.push_back(attributes.normals[(vData.normal_index * 3)]);
            this->fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 1]);
            this->fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 2]);
            //* UVs
            this->fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2)]);
            this->fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2) + 1]);
        }
    }

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * this->fullVertexData.size(),
                 this->fullVertexData.data(),
                 GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    GLintptr normalPtr = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtr);
    glEnableVertexAttribArray(1);
    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtr);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Model3D::update() { this->updatePositionMatrix(); }
void Model3D::updatePositionMatrix() {
    this->positionMatrix = glm::translate(glm::mat4(1.0f), this->position);
    this->positionMatrix = glm::scale(this->positionMatrix, this->scale);
    this->positionMatrix =
        glm::rotate(this->positionMatrix, glm::radians(this->orientation.x), rotateAroundTheXAxis);
    this->positionMatrix =
        glm::rotate(this->positionMatrix, glm::radians(this->orientation.y), rotateAroundTheYAxis);
    this->positionMatrix =
        glm::rotate(this->positionMatrix, glm::radians(this->orientation.z), rotateAroundTheZAxis);
}

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
std::string Model3D::getName() { return this->name; }
void Model3D::setName(std::string name) { this->name = name; }
MyTexture Model3D::getTexture() { return this->texture; }
glm::vec3 Model3D::getPosition() { return this->position; }
void Model3D::setPosition(glm::vec3 position) { this->position = position; }
glm::mat4 Model3D::getPositionMatrix() { return this->positionMatrix; }
void Model3D::setPositionMatrix(glm::mat4 positionMatrix) { this->positionMatrix = positionMatrix; }
glm::vec3 Model3D::getScale() { return this->scale; }
void Model3D::setScale(glm::vec3 scale) { this->scale = scale; }
glm::vec3 Model3D::getOrientation() { return this->orientation; }
void Model3D::setOrientation(glm::vec3 orientation) { this->orientation = orientation; }
std::vector<GLfloat> Model3D::getFullVertexData() { return this->fullVertexData; }
GLuint* Model3D::getVAO() { return &this->VAO; }
GLuint* Model3D::getVBO() { return &this->VBO; }  // namespace models
