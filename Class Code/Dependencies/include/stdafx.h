#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "iostream"
#include "string"
#include "vector"
#include "Settings.hpp"

//* - - - - - ROTATION AXES - - - - -
const glm::vec3 rotateAroundTheXAxis = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 rotateAroundTheYAxis = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 rotateAroundTheZAxis = glm::vec3(0.0f, 0.0f, 1.0f);
//* - - - - - END OF ROTATION AXES - - - - -