#pragma once
#include "../Light.hpp"
#include "stdafx.h"

namespace models {
class PointLight : public Light {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
public:
    glm::vec3 position;

    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    PointLight(std::string name,
               bool enabled,
               glm::vec3 position,
               glm::vec3 color,
               float ambientStrength,
               glm::vec3 ambientColor,
               float specularStrength,
               float specularPhong,
               float brightness);

    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:
    void update(bool enabled,
                std::vector<glm::vec3> vectorUpdates,
                std::vector<float> floatUpdates);

    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
    glm::vec3 getPosition();
};
}  // namespace models