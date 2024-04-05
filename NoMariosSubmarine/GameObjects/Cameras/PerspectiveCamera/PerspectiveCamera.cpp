#include "PerspectiveCamera.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
PerspectiveCamera::PerspectiveCamera(std::string name,
                                     glm::vec3 position,
                                     glm::vec3 viewCenter,
                                     float fieldOfView,
                                     float farClippingPlane)
    : Camera(name,
             glm::perspective(glm::radians(fieldOfView),
                              float(WINDOW_WIDTH / WINDOW_HEIGHT),
                              0.1f,
                              farClippingPlane),
             position,
             viewCenter) {
    if (DEBUG_MODE) std::cout << this->name + " initialized!" << std::endl;
}

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
// namespace models
