#include "Light.hpp"

using namespace models;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Light::Light(std::string name,
             glm::vec3 color,
             float ambientStrength,
             glm::vec3 ambientColor,
             float specularStrength,
             float specularPhong, float brightness)
    : name(name),
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
// namespace models
