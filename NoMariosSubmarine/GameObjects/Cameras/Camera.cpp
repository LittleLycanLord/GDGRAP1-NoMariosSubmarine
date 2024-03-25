#include "Camera.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Camera::Camera(std::string name, glm::mat4 projection) : name(name + " Camera"),
                orientation(glm::mat4(1.f)), position(glm::vec3(0.0f, 0.0f, 5.0f)), 
                positionMatrix(glm::translate(glm::mat4(1.0f), position * -1.0f)), viewCenter(glm::vec3(0.f, 0.f, -1.f)), 
                projection(glm::perspective(glm::radians(60.f), float(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 1000.f)){

    if (DEBUG_MODE) std::cout << "Parent Camera " + this->name + " initialized!" << std::endl;
}   

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void Camera::initializeOrientation(glm::vec3 RightVector, glm::vec3 UpVector, glm::vec3 ForwardVector){

    
    orientation[0][0] = RightVector.x;
    orientation[1][0] = RightVector.y;
    orientation[2][0] = RightVector.z;

    orientation[0][1] = UpVector.x;
    orientation[1][1] = UpVector.y;
    orientation[2][1] = UpVector.z;

    orientation[0][2] = -ForwardVector.x;
    orientation[1][2] = -ForwardVector.y;
    orientation[2][2] = -ForwardVector.z;

    this->view = orientation * this->getPositionMatrix();
    

}
//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
std::string Camera::getName() { return this->name; }
void Camera::setName(std::string name) { this->name = name; }

glm::vec3 Camera::getPosition() { return this->position;}
void Camera::setPosition(glm::vec3 position) { this->position = position;}

glm::mat4 Camera::getPositionMatrix() { return this->positionMatrix; }
void Camera::setPositionMatrix(glm::mat4 positionMatrix) { this->positionMatrix = positionMatrix; }

glm::mat4 Camera::getOrientation() { return this->orientation; }

glm::mat4 Camera::getProjection() { return this->projection; }
void Camera::setProjection(glm::mat4 projection) { this->projection = projection; }

glm::mat4 Camera::getView() { return this->view; }
void Camera::setView(glm::mat4 view) { this->view = view; }

glm::vec3 Camera::getViewCenter() { return this->viewCenter; }
void Camera::setViewCenter(glm::vec3 viewCenter) { this->viewCenter = viewCenter; }

// namespace models