#include "OrthographicCamera.hpp"

using namespace models;

OrthographicCamera::OrthographicCamera(std::string name) 
	: Camera(name + " Orthographic Camera", this->getProjection()) {

	setPosition(glm::vec3(0.0f, 10.0f, 5.0f));
	setProjection(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.f, 1000.0f));

	if (DEBUG_MODE) std::cout << this->name + " initialized!" << std::endl;
}
//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
// namespace models
