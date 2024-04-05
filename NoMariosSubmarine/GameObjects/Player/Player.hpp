#pragma once
#include "../Cameras/OrthographicCamera/OrthographicCamera.hpp"
#include "../Cameras/PerspectiveCamera/PerspectiveCamera.hpp"
#include "../Cameras/FirstPersonCamera/FirstPersonCamera.hpp"
#include "../Lights/DirectionalLight/DirectionalLight.hpp"
#include "../Lights/PointLight/PointLight.hpp"
#include "../Lights/SpotLight/SpotLight.hpp"
#include "../Model3D/Model3D.hpp"
#include "../MyNormal/MyNormal.hpp"
#include "iomanip"
#include "cstdlib"
#include "../MyTexture/MyTexture.hpp"
// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on
#include "stdafx.h"

namespace models {
class Player {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
protected:
    Model3D* model;
    SpotLight* spotLight;
    FirstPersonCamera* firstPersonView;
    PerspectiveCamera* thirdPersonView;
    float turnInput;
    float yInput;
    float zInput;
    int lightIntensity;
    //? [0]: LOW
    //? [1]: MID
    //? [2]: HIGH

    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    Player();

    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:
    void playerKeyboardInput(int key, int action);
    void playerMouseInput();
    void movePlayer();
    void turnPlayer();
    void cycleLightIntensity();
    void resetInputs();
    void displayDepth();
    void haveSpotlightFollowModel();

    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
    Model3D* getModel();
    SpotLight* getSpotLight();
    FirstPersonCamera* getFirstPersonView();
    PerspectiveCamera* getThirdPersonView();
};
}  // namespace models