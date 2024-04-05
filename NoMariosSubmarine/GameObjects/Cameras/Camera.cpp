#include "Camera.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
//| TODO: Add the following parameters in the contructor so we can simply edit it from main.cpp:
//| - position
//| - viewCenter

Camera::Camera(std::string name, glm::mat4 projection)
    : name(name + " Camera"),
      position(glm::vec3(0.0f)),
      positionMatrix(glm::translate(glm::mat4(1.0f), this->position * -1.0f)),
      view(glm::mat4(1.0f)),
      viewCenter(glm::vec3(0.f, 0.f, -1.f)),
      //| TODO: I suggest setting the projection to a glm::mat4(1.0f) so we can't have just Camera
      //| classes spawned (Abstract class)
      projection(
          glm::perspective(glm::radians(60.f), float(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 1000.f)) {
}

Camera::Camera(std::string name, glm::mat4 projection, glm::vec3 position, glm::vec3 viewCenter)
    : name(name + " Camera"),
      position(glm::vec3(0.0f)),
      positionMatrix(glm::translate(glm::mat4(1.0f), this->position * -1.0f)),
      view(glm::mat4(1.0f)),
      viewCenter(glm::vec3(0.f, 0.f, -1.f)),
      //| TODO: I suggest setting the projection to a glm::mat4(1.0f) so we can't have just Camera
      //| classes spawned (Abstract class)
      projection(
          glm::perspective(glm::radians(60.f), float(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 1000.f)) {
}

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