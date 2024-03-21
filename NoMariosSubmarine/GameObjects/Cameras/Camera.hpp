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
    glm::vec3 orientation;
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
    // TODO 1: Given that we keep track of the position using a glm::vec3, updatePositionMatrix should update PositionMatrix based on the
    // td    values in Position. [HINT: it's one line]
    void updatePositionMatrix();
    virtual void updateProjection() = 0;

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
    glm::vec3 getOrientation();
    void setOrientation(glm::vec3 orientation);
    glm::mat4 getProjection();
    void setProjection(glm::mat4 projection);
};
}  // namespace models