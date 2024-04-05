#pragma once
#include "../Camera.hpp"
#include "stdafx.h"

namespace models {
class OrthographicCamera : public Camera {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
private:
    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    OrthographicCamera(std::string name,
                       glm::vec3 position,
                       glm::vec3 viewCenter,
                       float left,
                       float right,
                       float bottom,
                       float top,
                       float near,
                       float far);
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:

    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
};
}  // namespace models