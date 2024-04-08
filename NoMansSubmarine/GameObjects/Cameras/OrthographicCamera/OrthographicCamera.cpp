#include "OrthographicCamera.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
//| TODO: Adjust the constructor based on the changes to the base Camera contructor, with the
//| additional parameters added for orthographic projection:
//| - Left-clipping plane
//| - Right-clipping plane
//| - Bottom-clipping plane
//| - Top-clipping plane
//| - Near-clipping plane
//| - Far-clipping plane
OrthographicCamera::OrthographicCamera(std::string name)
    : Camera(name, this->getProjection(), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f)) {
    setPosition(glm::vec3(0.0f, 10.0f, 5.0f));
    setProjection(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.f, 1000.0f));

    if (DEBUG_MODE) std::cout << this->name + " initialized!" << std::endl;
}

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
// namespace models
