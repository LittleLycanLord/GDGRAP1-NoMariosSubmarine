#include "Camera.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Camera::Camera(std::string name, glm::mat4 projection, glm::vec3 position, glm::vec3 viewCenter)
    : name(name),
      projection(projection),
      position(position),
      positionMatrix(glm::translate(glm::mat4(1.0f), position * -1.0f)),
      view(glm::mat4(1.0f)),
      viewCenter(viewCenter) {}

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
std::string Camera::getName() { return this->name; }
void Camera::setName(std::string name) { this->name = name; }

glm::vec3 Camera::getPosition() { return this->position; }
void Camera::setPosition(glm::vec3 position) { this->position = position; }

glm::mat4 Camera::getPositionMatrix() { return this->positionMatrix; }
void Camera::setPositionMatrix(glm::mat4 positionMatrix) { this->positionMatrix = positionMatrix; }

glm::mat4 Camera::getProjection() { return this->projection; }
void Camera::setProjection(glm::mat4 projection) { this->projection = projection; }

glm::mat4 Camera::getView() { return this->view; }
void Camera::setView(glm::mat4 view) { this->view = view; }

glm::vec3 Camera::getViewCenter() { return this->viewCenter; }
void Camera::setViewCenter(glm::vec3 viewCenter) { this->viewCenter = viewCenter; }

// namespace models