#include "Model3D.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Model3D::Model3D(std::string name, glm::mat4 projection) : name(name + " Model3D"), projection(projection) {
    if (DEBUG_MODE) std::cout << this->name + " initialized!" << std::endl;
}   

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void Model3D::update() {
    this->updatePositionMatrix();
    this->updateProjection();
}
void Model3D::updatePositionMatrix() {}

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
std::string Model3D::getName() { return this->name; }
void Model3D::setName(std::string name) { this->name = name; }
glm::vec3 Model3D::getPosition() { return this->position; }
void Model3D::setPosition(glm::vec3 position) { this->position = position; }
glm::mat4 Model3D::getPositionMatrix() { return this->positionMatrix; }
void Model3D::setPositionMatrix(glm::mat4 positionMatrix) { this->positionMatrix = positionMatrix; }
glm::vec3 Model3D::getOrientation() { return this->orientation; }
void Model3D::setOrientation(glm::vec3 Orientation) { this->orientation = Orientation; }
glm::mat4 Model3D::getProjection() { return this->projection; }
void Model3D::setProjection(glm::mat4 Projection) { this->projection = Projection; }
// namespace models
