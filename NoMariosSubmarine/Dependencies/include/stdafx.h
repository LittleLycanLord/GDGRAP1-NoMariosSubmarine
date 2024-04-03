#pragma once
#include "Settings.hpp"
#include "fstream"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "iostream"
#include "sstream"
#include "string"
#include "vector"

//* - - - - - ROTATION AXES - - - - -
const glm::vec3 rotateAroundTheXAxis = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 rotateAroundTheYAxis = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 rotateAroundTheZAxis = glm::vec3(0.0f, 0.0f, 1.0f);
//* - - - - - END OF ROTATION AXES - - - - -

//* - - - - - DATA FORMATTING - - - - -
const int STRIDE_LENGTH              = 14;
const int POSITION_INDEX             = 0;
const int NORMAL_INDEX               = 1;
const int UV_INDEX                   = 2;
const int TANGENT_INDEX              = 3;
const int BITANGENT_INDEX            = 4;
//* - - - - - END OF DATA FORMATTING - - - - -