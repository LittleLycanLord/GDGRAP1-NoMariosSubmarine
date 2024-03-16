#pragma once
#include "stdafx.h"

namespace models {
class Light {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
public:
    std::string name;
    glm::vec3 color;
    float ambientStrength;
    glm::vec3 ambientColor;
    float specularStrength;
    float specularPhong;
    float brightness;
    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    Light(std::string name,
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
private:
    virtual void update(std::vector<glm::vec3> vectorUpdates, std::vector<float> floatUpdates) = 0;

    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
};
}  // namespace models