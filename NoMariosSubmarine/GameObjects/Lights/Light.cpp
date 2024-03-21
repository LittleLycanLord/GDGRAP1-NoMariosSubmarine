#include "Light.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Light::Light(std::string name,
             bool enabled,
             glm::vec3 color,
             float ambientStrength,
             glm::vec3 ambientColor,
             float specularStrength,
             float specularPhong,
             float brightness)
    : name(name),
      enabled(enabled),
      color(color),
      ambientStrength(ambientStrength),
      ambientColor(ambientColor),
      specularStrength(specularStrength),
      specularPhong(specularPhong),
      brightness(brightness) {}
//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝

//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
bool Light::getEnabled() { return this->enabled; }
// namespace models
