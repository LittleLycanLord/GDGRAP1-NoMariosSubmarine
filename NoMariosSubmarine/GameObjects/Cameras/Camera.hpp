#pragma once
#include "stdafx.h"

namespace models {
class Camera {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
protected:
    std::string name;
    glm::vec3 position;
    glm::mat4 positionMatrix;
    glm::mat4 orientation;
    glm::mat4 view;
    glm::mat4 projection;

    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    Camera(std::string name, glm::mat4 projection);
    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:
private:
    void update();
    void updatePositionMatrix();
    virtual void updateProjection() = 0;
public:
    void initializeOrientation(glm::vec3 RightVector, glm::vec3 UpVector, glm::vec3 ForwardVector);

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

    glm::mat4 getOrientation();

    glm::mat4 getProjection();
    void setProjection(glm::mat4 projection);

    glm::mat4 getView();
    void setView(glm::mat4 view);
};
} 