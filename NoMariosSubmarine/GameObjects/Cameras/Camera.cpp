#include "Camera.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Camera::Camera(std::string name, glm::mat4 projection) : name(name + " Camera"), projection(projection) {
    if (DEBUG_MODE) std::cout << this->name + " initialized!" << std::endl;
}   

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void Camera::update() {
    this->updatePositionMatrix();
    this->updateProjection();
}
void Camera::updatePositionMatrix() {}

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
std::string Camera::getName() { return this->name; }
void Camera::setName(std::string name) { this->name = name; }
glm::vec3 Camera::getPosition() { return this->position; }
void Camera::setPosition(glm::vec3 position) { this->position = position; }
glm::mat4 Camera::getPositionMatrix() { return this->positionMatrix; }
void Camera::setPositionMatrix(glm::mat4 positionMatrix) { this->positionMatrix = positionMatrix; }
glm::vec3 Camera::getOrientation() { return this->orientation; }
void Camera::setOrientation(glm::vec3 Orientation) { this->orientation = Orientation; }
glm::mat4 Camera::getProjection() { return this->projection; }
void Camera::setProjection(glm::mat4 Projection) { this->projection = Projection; }
// namespace models
