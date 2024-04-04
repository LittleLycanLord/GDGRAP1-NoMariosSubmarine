#pragma once

#include "../../tiny_obj_loader.h"
#include "../MyNormal/MyNormal.hpp"
#include "../MyTexture/MyTexture.hpp"
#include "stdafx.h"

namespace models {
class Model3D {
    //* ╔════════════╗
    //* ║ Attributes ║
    //* ╚════════════╝
protected:
    std::string name;
    bool enabled;
    MyTexture texture;
    MyNormal normalMap;
    std::string texturePath;
    std::string normalPath;
    std::string modelPath;
    glm::vec3 position;
    glm::mat4 positionMatrix;
    glm::vec3 scale;
    glm::vec3 orientation;
    std::vector<GLfloat> fullVertexData;
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;
    GLuint VAO;
    GLuint VBO;

    //* ╔═══════════════════════════════╗
    //* ║ Constructors & Deconstructors ║
    //* ╚═══════════════════════════════╝
public:
    Model3D(std::string name,
            std::string modelPath,
            std::string texturePath,
            std::string normalPath,
            glm::vec3 position,
            glm::mat4 positionMatrix,
            glm::vec3 scale,
            glm::vec3 orientation);

    //* ╔═════════╗
    //* ║ Methods ║
    //* ╚═════════╝
public:
    void loadModel();
    void update();
    void updatePositionMatrix();

    //* ╔═══════════════════╗
    //* ║ Getters & Setters ║
    //* ╚═══════════════════╝
public:
    std::string getName();
    void setName(std::string name);
    bool getEnabled();
    void setEnabled(bool enabled);
    MyTexture getTexture();
    MyNormal getNormalMap();
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    glm::mat4 getPositionMatrix();
    void setPositionMatrix(glm::mat4 positionMatrix);
    glm::vec3 getScale();
    void setScale(glm::vec3 scale);
    glm::vec3 getOrientation();
    void setOrientation(glm::vec3 orientation);
    glm::mat4 getProjection();
    void setProjection(glm::mat4 projection);
    std::vector<GLfloat> getFullVertexData();
    GLuint* getVAO();
    GLuint* getVBO();
};
}  // namespace models