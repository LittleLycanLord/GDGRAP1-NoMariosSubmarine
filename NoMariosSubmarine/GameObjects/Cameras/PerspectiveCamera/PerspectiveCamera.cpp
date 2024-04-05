#include "PerspectiveCamera.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
//| TODO: Adjust the constructor based on the changes to the base Camera contructor, with the
//| additional parameters added for perspective projection:
//| - Far-clipping plane (the 1000.f, since we'll have cameras that are short/farsighted)
PerspectiveCamera::PerspectiveCamera(std::string name, float fieldOfView)
    : Camera(name + " Perspective", glm::perspective(1.0f, 1.0f, 1.0f, 1.0f)),
      fieldOfView(fieldOfView) {
    setPosition(glm::vec3(0.0f, 2.0f, 5.0f));
    setProjection(glm::perspective(
        glm::radians(this->fieldOfView), float(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 1000.f));

    if (DEBUG_MODE) std::cout << this->name + " initialized!" << std::endl;
}

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
// namespace models
