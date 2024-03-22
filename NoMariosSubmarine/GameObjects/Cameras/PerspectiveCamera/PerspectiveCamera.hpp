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
    void updateProjection();

    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
};
}  // namespace models