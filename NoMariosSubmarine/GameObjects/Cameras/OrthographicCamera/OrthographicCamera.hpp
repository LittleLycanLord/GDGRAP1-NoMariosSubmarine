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
    OrthographicCamera(std::string name);
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