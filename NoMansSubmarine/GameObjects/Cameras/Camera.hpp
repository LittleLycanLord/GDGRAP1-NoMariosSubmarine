#pragma once
#include "stdafx.h"
// #include "PerspectiveCamera/PerspectiveCamera.hpp"
// #include "../Player/Player.hpp"

namespace models {
class Camera {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
protected:
    std::string name;
    glm::vec3 position;
    glm::mat4 positionMatrix;
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 viewCenter;
    float prevX,prevY;

    
    // Player* player;
    // PerspectiveCamera* perspectiveCamera;
    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    Camera(std::string name, glm::mat4 projection, glm::vec3 position, glm::vec3 viewCenter);
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:
    //void turnCamera(Camera* camera);
    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
    std::string getName();
    void setName(std::string name);

    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);

    glm::mat4 getPositionMatrix();
    void setPositionMatrix(glm::mat4 positionMatrix);

    glm::mat4 getProjection();
    void setProjection(glm::mat4 projection);

    glm::mat4 getView();
    void setView(glm::mat4 view);

    glm::vec3 getViewCenter();
    void setViewCenter(glm::vec3 viewCenter);

    float getPrevX();
    void setPrevX(float prevX);

    float getPrevY();
    void setPrevY(float prevY);
};
}  // namespace models