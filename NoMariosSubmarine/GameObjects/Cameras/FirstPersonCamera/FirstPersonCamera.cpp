#include "FirstPersonCamera.hpp"

using namespace models;

FirstPersonCamera::FirstPersonCamera(std::string name, float fieldOfView) : 
    Camera(name + " First Person Camera", glm::perspective(1.0f, 1.0f, 1.0f, 1.0f))
    {
        
    setPosition(glm::vec3(0.0f,1.0f,0.5f));
    setProjection(glm::perspective(glm::radians(fieldOfView), float(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 1000.f));
}

