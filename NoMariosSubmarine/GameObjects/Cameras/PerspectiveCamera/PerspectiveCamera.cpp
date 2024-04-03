#include "PerspectiveCamera.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝

// TODO 2: Fix the parameters for perspective, knowing we have:
// td          - a fieldOfView Parameter
// td          - Window Height and Window Width Constants in Settings.hpp [already included in
// stdafx.h] td          - Our Near and Far clipping planes are 0.01f and 1000.0f respectively

PerspectiveCamera::PerspectiveCamera(std::string name, float fieldOfView)
    : Camera(name + " Perspective Camera", glm::perspective(1.0f, 1.0f, 1.0f, 1.0f)),
      fieldOfView(fieldOfView) {
    setPosition(glm::vec3(0.0f, 0.0f, 1.8f));
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
