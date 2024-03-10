// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"
// clang-format on
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "iostream"
#include "string"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

//* - - - - - SYSTEM SETTINGS - - - - -
const float WINDOW_WIDTH             = 600.f;
const float WINDOW_HEIGHT            = 600.f;
const bool DRAW_SKYBOX               = false;
//* - - - - - END OF SYSTEM SETTINGS - - - - -

//* - - - - - SPEEDS - - - - -
const float ROTATE_SPEED             = 0.05f;
const float MOVE_SPEED               = 1.0f;
//* - - - - - END OF SPEEDS - - - - -

//* - - - - - ROTATION AXES - - - - -
const glm::vec3 rotateAroundTheXAxis = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 rotateAroundTheYAxis = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 rotateAroundTheZAxis = glm::vec3(0.0f, 0.0f, 1.0f);
//* - - - - - END OF ROTATION AXES - - - - -

//* - - - - - MODEL TRANSFORM - - - - -
glm::vec3 modelPosition              = glm::vec3(0.0f);
glm::vec3 modelScale                 = glm::vec3(0.05f);
glm::vec3 modelOrientation           = glm::vec3(0.0f);
glm::mat4 modelTransform             = glm::mat4(1.0f);
//* - - - - - END OF MODEL TRANSFORM - - - - -

//? Reserved GLFW Function for Keyboard Inputs
void Key_Callback(GLFWwindow* window,  //? Which window did we get the event?
                  int key,             //? What key was pressed?
                  int scancode,        //? What exact physical key was pressed?
                  int action,          //? What is being done to the key? [GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE]
                  int mods) {          //? Which modifer keys are held? [alt, control, shift, Super, num lock, and caps lock]

    switch (key) {
        //* Translation
        case GLFW_KEY_W:
            // if (GLFW_REPEAT)
            //* Move Forward
            modelPosition.z += MOVE_SPEED;
            break;
        case GLFW_KEY_A:
            // if (GLFW_REPEAT)
            //* Move Left
            modelPosition.x -= MOVE_SPEED;
            break;
        case GLFW_KEY_S:
            // if (GLFW_REPEAT)
            //* Move Backward
            modelPosition.z -= MOVE_SPEED;
            break;
        case GLFW_KEY_D:
            // if (GLFW_REPEAT)
            //* Move Right
            modelPosition.x += MOVE_SPEED;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            // if (GLFW_REPEAT)
            //* Move Up
            modelPosition.y += MOVE_SPEED;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            // if (GLFW_REPEAT)
            //* Move Down
            modelPosition.y -= MOVE_SPEED;
            break;

        //* Rotation
        case GLFW_KEY_UP:
            // if (GLFW_REPEAT)
            //* Look Up
            modelOrientation.x += ROTATE_SPEED;
            break;
        case GLFW_KEY_DOWN:
            // if (GLFW_REPEAT)
            //* Look Down
            modelOrientation.x += ROTATE_SPEED;
            break;
        case GLFW_KEY_LEFT:
            // if (GLFW_REPEAT)
            //* Look Left
            modelOrientation.y += ROTATE_SPEED;
            break;
        case GLFW_KEY_RIGHT:
            // if (GLFW_REPEAT)
            //* Look Right
            modelOrientation.y += ROTATE_SPEED;
            break;
        case GLFW_KEY_RIGHT_SHIFT:
            // if (GLFW_REPEAT)
            //* Roll Clockwise
            modelOrientation.z += ROTATE_SPEED;
            break;
        case GLFW_KEY_RIGHT_CONTROL:
            // if (GLFW_REPEAT)
            //* Roll Counter Clockwise
            modelOrientation.z += ROTATE_SPEED;
            break;
    }
}

int main(void) {
    //* - - - - - WINDOW CREATION - - - - -
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Quiz 2 - Conrad Ubay", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glEnable(GL_DEPTH_TEST);
    glfwSetKeyCallback(window, Key_Callback);
    //* - - - - - END OF WINDOW CREATION - - - - -

    //* - - - - - MODEL TEXTURE LOADING - - - - -
    int textureWidth, textureHeight, textureColorChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* texBytes = stbi_load("Assets/partenza.jpg", &textureWidth, &textureHeight, &textureColorChannels, 0.f);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (!texBytes) {
        cout << "ERROR: Model texture failed to load" << endl;
        return -1;
    } else {
        switch (textureColorChannels) {
            case 3:
                glTexImage2D(GL_TEXTURE_2D,
                             0,  //? <- Texture Index
                             GL_RGB,
                             textureWidth,
                             textureHeight,
                             0,
                             GL_RGB,
                             GL_UNSIGNED_BYTE,
                             texBytes);
                break;
            case 4:
                glTexImage2D(GL_TEXTURE_2D,
                             0,  //? <- Texture Index
                             GL_RGBA,
                             textureWidth,
                             textureHeight,
                             0,
                             GL_RGBA,
                             GL_UNSIGNED_BYTE,
                             texBytes);
                break;
        }
        //? Mipmap: Low resolution versions of our texture for if we view the model from far away, we won't need to load as much detail
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(texBytes);
    }
    //* - - - - - END OF MODEL TEXTURE LOADING - - - - -

    //* - - - - - SHADER CREATION - - - - -
    std::fstream lightingVertexFile("Shaders/directional.vert");
    std::stringstream lightingVertexBuffer;
    lightingVertexBuffer << lightingVertexFile.rdbuf();
    std::string lightingVertexString    = lightingVertexBuffer.str();
    const char* lightingVertexCharArray = lightingVertexString.c_str();

    std::fstream lightingFragmentFile("Shaders/directional.frag");
    std::stringstream lightingFragmentBuffer;
    lightingFragmentBuffer << lightingFragmentFile.rdbuf();
    std::string lightingFragmentString    = lightingFragmentBuffer.str();
    const char* lightingFragmentCharArray = lightingFragmentString.c_str();

    std::fstream skyboxVertexFile("Shaders/skybox.vert");
    std::stringstream skyboxVertexBuffer;
    skyboxVertexBuffer << skyboxVertexFile.rdbuf();
    std::string skyboxVertexString    = skyboxVertexBuffer.str();
    const char* skyboxVertexCharArray = skyboxVertexString.c_str();

    std::fstream skyboxFragmentFile("Shaders/skybox.frag");
    std::stringstream skyboxFragmentBuffer;
    skyboxFragmentBuffer << skyboxFragmentFile.rdbuf();
    std::string skyboxFragmentString    = skyboxFragmentBuffer.str();
    const char* skyboxFragmentCharArray = skyboxFragmentString.c_str();

    GLuint lightingVertexShader         = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(lightingVertexShader, 1, &lightingVertexCharArray, NULL);
    glCompileShader(lightingVertexShader);

    GLuint lightingFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(lightingFragmentShader, 1, &lightingFragmentCharArray, NULL);
    glCompileShader(lightingFragmentShader);

    GLuint skyboxVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(skyboxVertexShader, 1, &skyboxVertexCharArray, NULL);
    glCompileShader(skyboxVertexShader);

    GLuint skyboxFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(skyboxFragmentShader, 1, &skyboxFragmentCharArray, NULL);
    glCompileShader(skyboxFragmentShader);

    GLuint lightingProgram = glCreateProgram();
    glAttachShader(lightingProgram, lightingVertexShader);
    glAttachShader(lightingProgram, lightingFragmentShader);

    glLinkProgram(lightingProgram);

    GLuint skyboxProgram = glCreateProgram();
    glAttachShader(skyboxProgram, skyboxVertexShader);
    glAttachShader(skyboxProgram, skyboxFragmentShader);

    glLinkProgram(skyboxProgram);
    //* - - - - - END OF SHADER CREATION - - - - -

    //* - - - - - MODEL LOADING - - - - -
    std::string path = "Assets/djSword.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;
    tinyobj::attrib_t attributes;
    std::vector<GLfloat> fullVertexData;

    if (!tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, path.c_str())) {
        cout << "ERROR: Model failed to load" << endl;
        return -1;
    } else {
        for (int i = 0.f; i < shapes[0].mesh.indices.size(); i++) {
            tinyobj::index_t vData = shapes[0].mesh.indices[i];
            //* Positions
            fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3)]);
            fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 1]);
            fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 2]);
            //* Normals
            fullVertexData.push_back(attributes.normals[(vData.normal_index * 3)]);
            fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 1]);
            fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 2]);
            //* UVs
            fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2)]);
            fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2) + 1]);
        }
    }

    GLuint modelVAO, modelVBO;
    glGenVertexArrays(1, &modelVAO);
    glGenBuffers(1, &modelVBO);
    glBindVertexArray(modelVAO);
    glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * fullVertexData.size(), fullVertexData.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    GLintptr normalPtr = 3 * sizeof(float);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtr);
    glEnableVertexAttribArray(1);
    GLintptr uvPtr = 6 * sizeof(float);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtr);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //* - - - - - END OF MODEL LOADING - - - - -

    //* - - - - - SKYBOX CREATION - - - - -
    //?   7--------6
    //?  /|       /|
    //? 4--------5 |
    //? | |      | |
    //? | 3------|-2
    //? |/       |/
    //? 0--------1

    //* Define our skybox's vertices
    float skyboxVertices[]{
       // clang-format off
       -1.f, -1.f,  1.f, //? 0 - Near Bottom Left Corner
        1.f, -1.f,  1.f, //? 1 - Near Bottom Right Corner
        1.f, -1.f, -1.f, //? 2 - Far Bottom Right Corner
       -1.f, -1.f, -1.f, //? 3 - Far Bottom Left Corner
       -1.f,  1.f,  1.f, //? 4 - Near Top Left Corner
        1.f,  1.f,  1.f, //? 5 - Near Top Right Corner
        1.f,  1.f, -1.f, //? 6 - Far Top Right Corner
       -1.f,  1.f, -1.f  //? 7 - Far Top Left Corner
       // clang-format on
    };

    //* Define our skybox's fragments
    //* Note: Each face consist of two triangles, thus each face is made up of a pair of vertex triplets (cuz triangles have three corners, duh)
    unsigned int skyboxFragments[]{
       // clang-format off
        1, 2, 6, 6, 5, 1, //? Right Face
        0, 4, 7, 7, 3, 0, //? Left Face
        4, 5, 6, 6, 7, 4, //? Top Face
        0, 3, 2, 2, 1, 0, //? Bottom Face
        0, 1, 5, 5, 4, 0, //? Near Face
        3, 7, 6, 6, 2, 3  //? Far Face
       // clang-format on
    };

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxFragments, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    //* - - - - - END OF SKYBOX CREATION - - - - -

    //* - - - - - SKYBOX TEXTURING - - - - -
    std::string skyboxTexturePaths[]{"Assets/Skybox/rainbow_rt.png",
                                     "Assets/Skybox/rainbow_lf.png",
                                     "Assets/Skybox/rainbow_up.png",
                                     "Assets/Skybox/rainbow_dn.png",
                                     "Assets/Skybox/rainbow_ft.png",
                                     "Assets/Skybox/rainbow_bk.png"};

    unsigned int skyboxTexture;
    glGenTextures(1, &skyboxTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0.f; i < 6; i++) {
        int w, h, skyCChannel;
        stbi_set_flip_vertically_on_load(false);
        unsigned char* data = stbi_load(skyboxTexturePaths[i].c_str(), &w, &h, &skyCChannel, 0.f);

        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0.f, GL_RGB, w, h, 0.f, GL_RGB, GL_UNSIGNED_BYTE, data);

            stbi_image_free(data);
        }

        stbi_set_flip_vertically_on_load(true);
    }
    //* - - - - - END OF SKYBOX TEXTURING - - - - -

    //* - - - - - CAMERA PART 1 - - - - -
    glm::vec3 cameraPosition       = glm::vec3(0.f, 0.f, 5.f);
    glm::mat4 cameraPositionMatrix = glm::translate(glm::mat4(1.0f), cameraPosition * -1.0f);
    glm::mat4 cameraProjection     = glm::perspective(glm::radians(90.f), WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.f);
    //* - - - - - END OF CAMERA PART 1 - - - - -

    //* - - - - - WORLD FACTS - - - - -
    glm::vec3 WorldUp              = glm::vec3(0.f, 1.0f, 0.f);
    glm::vec3 Center               = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 ForwardVector        = glm::vec3(Center - cameraPosition);
    ForwardVector                  = glm::normalize(ForwardVector);
    glm::vec3 RightVector          = glm::normalize(glm::cross(ForwardVector, WorldUp));
    glm::vec3 UpVector             = glm::normalize(glm::cross(RightVector, ForwardVector));
    //* - - - - - END OF WORLD FACTS - - - - -

    //* - - - - - CAMERA PART 2 - - - - -
    glm::mat4 cameraOrientation    = glm::mat4(1.f);

    cameraOrientation[0][0]        = RightVector.x;
    cameraOrientation[1][0]        = RightVector.y;
    cameraOrientation[2][0]        = RightVector.z;

    cameraOrientation[0][1]        = UpVector.x;
    cameraOrientation[1][1]        = UpVector.y;
    cameraOrientation[2][1]        = UpVector.z;

    cameraOrientation[0][2]        = -ForwardVector.x;
    cameraOrientation[1][2]        = -ForwardVector.y;
    cameraOrientation[2][2]        = -ForwardVector.z;

    glm::mat4 cameraView           = cameraOrientation * cameraPositionMatrix;
    //* - - - - - END OF CAMERA PART 2 - - - - -

    //* - - - - - LIGHTS - - - - -
    glm::vec3 lightPosition        = glm::vec3(-1.f, -1.f, 0.f);
    glm::vec3 lightColor           = glm::vec3(0.f, 1.f, 0.f);
    float ambientStrength          = 0.1f;
    glm::vec3 ambientColor         = lightColor;
    float specularStrength         = 0.5f;
    float specularPhong            = 16;
    //* - - - - - END OF LIGHTS - - - - -

    //* - - - - - RUNTIME - - - - -
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        modelOrientation.y += ROTATE_SPEED;

        //* - - - - - SKYBOX RENDERING - - - - -
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxProgram);

        glm::mat4 skyboxView           = glm::mat4(1.f);
        skyboxView                     = glm::mat4(glm::mat3(cameraView));

        unsigned int skyboxViewAddress = glGetUniformLocation(skyboxProgram, "view");
        glUniformMatrix4fv(skyboxViewAddress, 1, GL_FALSE, glm::value_ptr(skyboxView));

        unsigned skyboxProjectionAddress = glGetUniformLocation(skyboxProgram, "projection");
        glUniformMatrix4fv(skyboxProjectionAddress, 1, GL_FALSE, glm::value_ptr(cameraProjection));

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        if (DRAW_SKYBOX) glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //* - - - - - END OF SKYBOX RENDERING - - - - -

        //* - - - - - MODEL UPDATE - - - - -
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
        glUseProgram(lightingProgram);

        //* - - - - - MODEL TRANSFORM - - - - -
        modelTransform             = glm::translate(glm::mat4(1.0f), modelPosition);
        modelTransform             = glm::scale(modelTransform, modelScale);
        modelTransform             = glm::rotate(modelTransform, glm::radians(modelOrientation.x), rotateAroundTheXAxis);
        modelTransform             = glm::rotate(modelTransform, glm::radians(modelOrientation.y), rotateAroundTheYAxis);
        modelTransform             = glm::rotate(modelTransform, glm::radians(modelOrientation.z), rotateAroundTheZAxis);

        unsigned int cameraProjectionAddress = glGetUniformLocation(lightingProgram, "projection");
        glUniformMatrix4fv(cameraProjectionAddress, 1, GL_FALSE, glm::value_ptr(cameraProjection));

        unsigned int modelTransformAddress = glGetUniformLocation(lightingProgram, "transform");
        glUniformMatrix4fv(modelTransformAddress, 1, GL_FALSE, glm::value_ptr(modelTransform));

        unsigned int cameraViewAddress = glGetUniformLocation(lightingProgram, "view");
        glUniformMatrix4fv(cameraViewAddress, 1, GL_FALSE, glm::value_ptr(cameraView));
        //* - - - - - END OF MODEL TRANSFORM - - - - -

        //* - - - - - MODEL LIGHTING - - - - -
        glBindVertexArray(modelVAO);

        GLuint modelTextureAddress = glGetUniformLocation(lightingProgram, "tex0");
        glBindTexture(GL_TEXTURE_2D, texture);

        GLuint lightPositionAddress = glGetUniformLocation(lightingProgram, "lightPos");
        glUniform3fv(lightPositionAddress, 1, glm::value_ptr(lightPosition));

        GLuint lightColorAddress = glGetUniformLocation(lightingProgram, "lightColor");
        glUniform3fv(lightColorAddress, 1, glm::value_ptr(lightColor));

        GLuint ambientStrengthAddress = glGetUniformLocation(lightingProgram, "ambientStr");
        glUniform1f(ambientStrengthAddress, ambientStrength);

        GLuint ambientColorAddress = glGetUniformLocation(lightingProgram, "ambientColor");
        glUniform3fv(ambientColorAddress, 1, glm::value_ptr(ambientColor));

        GLuint cameraPositionAddress = glGetUniformLocation(lightingProgram, "cameraPos");
        glUniform3fv(cameraPositionAddress, 1, glm::value_ptr(cameraPosition));

        GLuint specularStrengthAddress = glGetUniformLocation(lightingProgram, "specStr");
        glUniform1f(specularStrengthAddress, specularStrength);

        GLuint specularPhongAddress = glGetUniformLocation(lightingProgram, "specPhong");
        glUniform1f(specularPhongAddress, specularPhong);
        //* - - - - - END OF MODEL LIGHTING - - - - -

        //* - - - - - MODEL RENDERING - - - - -
        glUniform1i(modelTextureAddress, 0);
        glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);
        //* - - - - - END OF MODEL RENDERING - - - - -
        //* - - - - - END OF MODEL UPDATE - - - - -
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    //* - - - - - END OF RUNTIME - - - - -

    //* - - - - - CLEAN UP - - - - -
    glDeleteVertexArrays(1, &modelVAO);
    glDeleteBuffers(1, &modelVBO);
    glDeleteShader(lightingVertexShader);
    glDeleteShader(lightingFragmentShader);
    glDeleteShader(skyboxVertexShader);
    glDeleteShader(skyboxFragmentShader);
    //* - - - - - END OF CLEAN UP - - - - -
    glfwTerminate();
    return 0.f;
}