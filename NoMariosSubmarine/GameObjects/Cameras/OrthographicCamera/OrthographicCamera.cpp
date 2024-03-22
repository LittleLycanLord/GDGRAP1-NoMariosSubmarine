#include "OrthographicCamera.hpp"

using namespace models;

// TODO 3: Make us an orthographic camera with an orthographic projection, which accepts the 6 different paramater of glm::ortho() function, stores
// td   them as its own attributes.
OrthographicCamera::OrthographicCamera(std::string name) 
	: Camera(name + " Orthographic Camera", glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.f, 1000.0f)) {

	setPosition(glm::vec3(glm::vec3(0.0f, 0.0f, 5.0f)));
	setProjection(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.f, 1000.0f));

	if (DEBUG_MODE) std::cout << this->name + " initialized!" << std::endl;
}
//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void OrthographicCamera::updateProjection() {}

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
// namespace models
