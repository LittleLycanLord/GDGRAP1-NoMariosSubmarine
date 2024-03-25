#pragma once
#include "../Camera.hpp"
#include "stdafx.h"

namespace models {
class PerspectiveCamera : public Camera {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
private:
    float fieldOfView;
    
    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    PerspectiveCamera(std::string name, float fieldOfView);

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