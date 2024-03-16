#include "DirectionalLight.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
DirectionalLight::DirectionalLight(std::string name,
                                   bool enabled,
                                   glm::vec3 direction,
                                   glm::vec3 color,
                                   float ambientStrength,
                                   glm::vec3 ambientColor,
                                   float specularStrength,
                                   float specularPhong,
                                   float brightness)
    : Light(name,
            enabled,
            color,
            ambientStrength,
            ambientColor,
            specularStrength,
            specularPhong,
            brightness),
      direction(direction) {}
//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void DirectionalLight::update(bool enabled,
                              std::vector<glm::vec3> vectorUpdates,
                              std::vector<float> floatUpdates) {
    this->color            = vectorUpdates[0];
    this->ambientStrength  = floatUpdates[0];
    this->ambientColor     = vectorUpdates[1];
    this->specularStrength = floatUpdates[1];
    this->specularPhong    = floatUpdates[2];
    this->brightness       = floatUpdates[3];

    this->direction        = vectorUpdates[2];
}

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
// namespace models
