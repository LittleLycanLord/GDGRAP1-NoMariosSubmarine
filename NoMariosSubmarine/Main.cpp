// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "GameObjects/Cameras/Camera.hpp"
#include "GameObjects/Cameras/OrthographicCamera/OrthographicCamera.hpp"
#include "GameObjects/Cameras/PerspectiveCamera/PerspectiveCamera.hpp"

#include "GameObjects/Lights/Light.hpp"
#include "GameObjects/Lights/DirectionalLight/DirectionalLight.hpp"
#include "GameObjects/Lights/SpotLight/SpotLight.hpp"
#include "GameObjects/Lights/PointLight/PointLight.hpp"
#include "GameObjects/MyTexture/MyTexture.hpp"
#include "GameObjects/Model3D/Model3D.hpp"
#include "stdafx.h"
// clang-format on

using namespace std;
using namespace models;

//* - - - - - SPEEDS - - - - -
const float ROTATE_SPEED   = 0.05f;
const float MOVE_SPEED     = 0.1f;
//* - - - - - END OF SPEEDS - - - - -

//* - - - - - MODEL TRANSFORM - - - - -
glm::vec3 modelPosition    = glm::vec3(0.f, -1.f, 0.f);
glm::vec3 modelScale       = glm::vec3(1.0f);
glm::vec3 modelOrientation = glm::vec3(0.0f);
glm::mat4 modelTransform   = glm::mat4(1.0f);
//* - - - - - END OF MODEL TRANSFORM - - - - -

//* - - - - - PROGRAMMING CHALLENGE 2 VARIABLES - - - - -
bool controllingModel      = false;
Light* activeLight         = NULL;
//* - - - - - END OF PROGRAMMING CHALLENGE 2 VARIABLES - - - - -

//? Reserved GLFW Function for Keyboard Inputs
void Key_Callback(
    GLFWwindow* window,  //? Which window did we get the event?
    int key,             //? What key was pressed?
    int scancode,        //? What exact physical key was pressed?
    int action,  //? What is being done to the key? [GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE]
    int mods) {  //? Which modifer keys are held? [alt, control, shift, Super, num lock, and caps
                 // lock]

    switch (key) {
        //* Switch between Light and Model
        case GLFW_KEY_SPACE:
            controllingModel = !controllingModel;
            break;

        //* Translation
        case GLFW_KEY_W:
            //* Move Forward
            if (controllingModel) {
                modelPosition.z -= MOVE_SPEED;
            } else {
                activeLight->update(true,
                                    {glm::vec3(0.0f),
                                     glm::vec3(0.0f),
                                     glm::vec3(0.0f, 0.0f, MOVE_SPEED),
                                     glm::vec3(0.0f)},
                                    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            }
            break;
        case GLFW_KEY_A:
            //* Move Left
            if (controllingModel) {
                modelPosition.x -= MOVE_SPEED;
            } else {
                activeLight->update(true,
                                    {glm::vec3(0.0f),
                                     glm::vec3(0.0f),
                                     glm::vec3(-MOVE_SPEED, 0.0f, 0.0f),
                                     glm::vec3(0.0f)},
                                    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            }
            break;
        case GLFW_KEY_S:
            //* Move Backward
            if (controllingModel) {
                modelPosition.z += MOVE_SPEED;
            } else {
                activeLight->update(true,
                                    {glm::vec3(0.0f),
                                     glm::vec3(0.0f),
                                     glm::vec3(0.0f, 0.0f, -MOVE_SPEED),
                                     glm::vec3(0.0f)},
                                    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            }
            break;
        case GLFW_KEY_D:
            //* Move Right
            if (controllingModel) {
                modelPosition.x += MOVE_SPEED;
            } else {
                activeLight->update(true,
                                    {glm::vec3(0.0f),
                                     glm::vec3(0.0f),
                                     glm::vec3(MOVE_SPEED, 0.0f, 0.0f),
                                     glm::vec3(0.0f)},
                                    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            }
            break;
        case GLFW_KEY_LEFT_SHIFT:
            //* Move Up
            if (controllingModel) {
                modelPosition.y += MOVE_SPEED;
            } else {
                activeLight->update(true,
                                    {glm::vec3(0.0f),
                                     glm::vec3(0.0f),
                                     glm::vec3(0.0f, MOVE_SPEED, 0.0f),
                                     glm::vec3(0.0f)},
                                    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            }
            break;
        case GLFW_KEY_LEFT_CONTROL:
            //* Move Down
            if (controllingModel) {
                modelPosition.y -= MOVE_SPEED;
            } else {
                activeLight->update(true,
                                    {glm::vec3(0.0f),
                                     glm::vec3(0.0f),
                                     glm::vec3(0.0f, -MOVE_SPEED, 0.0f),
                                     glm::vec3(0.0f)},
                                    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            }
            break;

        //* Rotation
        case GLFW_KEY_Q:
            //* Spin CW
            if (controllingModel) {
                modelOrientation.y -= ROTATE_SPEED;
            } else {
                activeLight->update(
                    true,
                    {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)},
                    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            }
            break;

        case GLFW_KEY_E:

            //* Spin CCW
            if (controllingModel) {
                modelOrientation.y += ROTATE_SPEED;
            } else {
                activeLight->update(
                    true,
                    {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)},
                    {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            }
            break;

            // case GLFW_KEY_UP:
            //
            //     //* Look Up
            //     if (controllingModel) {
            //         modelOrientation.x += ROTATE_SPEED;
            //     } else {
            //         activeLight->update(
            //             true,
            //             {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)},
            //             {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            //     }
            //     break;
            // case GLFW_KEY_DOWN:
            //
            //     //* Look Down
            //     if (controllingModel) {
            //         modelOrientation.x += ROTATE_SPEED;
            //     } else {
            //         activeLight->update(
            //             true,
            //             {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)},
            //             {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            //     }
            //     break;
            // case GLFW_KEY_LEFT:
            //
            //     //* Look Left
            //     if (controllingModel) {
            //         modelOrientation.y += ROTATE_SPEED;
            //     } else {
            //         activeLight->update(
            //             true,
            //             {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)},
            //             {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            //     }
            //     break;
            // case GLFW_KEY_RIGHT:
            //
            //     //* Look Right
            //     if (controllingModel) {
            //         modelOrientation.y += ROTATE_SPEED;
            //     } else {
            //         activeLight->update(
            //             true,
            //             {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)},
            //             {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            //     }
            //     break;
            // case GLFW_KEY_RIGHT_SHIFT:
            //
            //     //* Roll Clockwise
            //     if (controllingModel) {
            //         modelOrientation.z += ROTATE_SPEED;
            //     } else {
            //         activeLight->update(
            //             true,
            //             {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)},
            //             {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            //     }
            //     break;
            // case GLFW_KEY_RIGHT_CONTROL:
            //
            //     //* Roll Counter Clockwise
            //     if (controllingModel) {
            //         modelOrientation.z += ROTATE_SPEED;
            //     } else {
            //         activeLight->update(
            //             true,
            //             {glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f)},
            //             {0.0f, 0.0f, 0.0f, 0.0f, 0.0f});
            //     }
            //     break;
    }
}

int main(void) {
    //* - - - - - WINDOW CREATION - - - - -
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "PCO2 - Ubay & Vingno", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetKeyCallback(window, Key_Callback);
    //* - - - - - END OF WINDOW CREATION - - - - -

    //* - - - - - MODEL TEXTURE LOADING - - - - -
    // int textureWidth, textureHeight, textureColorChannels;
    // stbi_set_flip_vertically_on_load(true);
    // unsigned char* texBytes =
    //     stbi_load("Assets/Submarine.png", &textureWidth, &textureHeight, &textureColorChannels,
    //     0);

    // GLuint texture;
    // glGenTextures(1, &texture);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, texture);

    // if (!texBytes) {
    //     cout << "ERROR: Model texture failed to load" << endl;
    //     return -1;
    // } else {
    //     switch (textureColorChannels) {
    //         case 3:
    //             glTexImage2D(GL_TEXTURE_2D,
    //                          0,  //? <- Texture Index
    //                          GL_RGB,
    //                          textureWidth,
    //                          textureHeight,
    //                          0,
    //                          GL_RGB,
    //                          GL_UNSIGNED_BYTE,
    //                          texBytes);
    //             break;
    //         case 4:
    //             glTexImage2D(GL_TEXTURE_2D,
    //                          0,  //? <- Texture Index
    //                          GL_RGBA,
    //                          textureWidth,
    //                          textureHeight,
    //                          0,
    //                          GL_RGBA,
    //                          GL_UNSIGNED_BYTE,
    //                          texBytes);
    //             break;
    //     }
    //     //? Mipmap: Low resolution versions of our texture for if we view the model from far
    //     away,
    //     // we won't need to load as much detail
    //     glGenerateMipmap(GL_TEXTURE_2D);
    //     stbi_image_free(texBytes);
    // }
    //* - - - - - END OF MODEL TEXTURE LOADING - - - - -

    //* - - - - - SHADER CREATION - - - - -
    fstream lightingVertexFile("Shaders/main.vert");
    stringstream lightingVertexBuffer;
    lightingVertexBuffer << lightingVertexFile.rdbuf();
    string lightingVertexString         = lightingVertexBuffer.str();
    const char* lightingVertexCharArray = lightingVertexString.c_str();

    fstream lightingFragmentFile("Shaders/main.frag");
    stringstream lightingFragmentBuffer;
    lightingFragmentBuffer << lightingFragmentFile.rdbuf();
    string lightingFragmentString         = lightingFragmentBuffer.str();
    const char* lightingFragmentCharArray = lightingFragmentString.c_str();

    fstream skyboxVertexFile("Shaders/skybox.vert");
    stringstream skyboxVertexBuffer;
    skyboxVertexBuffer << skyboxVertexFile.rdbuf();
    string skyboxVertexString         = skyboxVertexBuffer.str();
    const char* skyboxVertexCharArray = skyboxVertexString.c_str();

    fstream skyboxFragmentFile("Shaders/skybox.frag");
    stringstream skyboxFragmentBuffer;
    skyboxFragmentBuffer << skyboxFragmentFile.rdbuf();
    string skyboxFragmentString         = skyboxFragmentBuffer.str();
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
    // string path = "Assets/MeepballSub.obj";
    // vector<tinyobj::shape_t> shapes;
    // vector<tinyobj::material_t> material;
    // string warning, error;
    // tinyobj::attrib_t attributes;
    // vector<GLfloat> fullVertexData;

    // if (!tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, path.c_str())) {
    //     cout << "ERROR: Model failed to load" << endl;
    //     return -1;
    // } else {
    //     for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
    //         tinyobj::index_t vData = shapes[0].mesh.indices[i];
    //         //* Positions
    //         fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3)]);
    //         fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 1]);
    //         fullVertexData.push_back(attributes.vertices[(vData.vertex_index * 3) + 2]);
    //         //* Normals
    //         fullVertexData.push_back(attributes.normals[(vData.normal_index * 3)]);
    //         fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 1]);
    //         fullVertexData.push_back(attributes.normals[(vData.normal_index * 3) + 2]);
    //         //* UVs
    //         fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2)]);
    //         fullVertexData.push_back(attributes.texcoords[(vData.texcoord_index * 2) + 1]);
    //     }
    // }

    // GLuint modelVAO, modelVBO;
    // glGenVertexArrays(1, &modelVAO);
    // glGenBuffers(1, &modelVBO);
    // glBindVertexArray(modelVAO);
    // glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
    // glBufferData(GL_ARRAY_BUFFER,
    //              sizeof(GLfloat) * fullVertexData.size(),
    //              fullVertexData.data(),
    //              GL_DYNAMIC_DRAW);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // GLintptr normalPtr = 3 * sizeof(float);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)normalPtr);
    // glEnableVertexAttribArray(1);
    // GLintptr uvPtr = 6 * sizeof(float);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)uvPtr);
    // glEnableVertexAttribArray(2);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    vector<Model3D*> models = {new Model3D("Submarine",
                                           "Assets/MeepballSub.obj",
                                           0,
                                           "Assets/Submarine.png",
                                           glm::vec3(0.5f, -1.f, 0.f),
                                           glm::mat4(1.0f),
                                           glm::vec3(1.0f),
                                           glm::vec3(0.0f)),
                               new Model3D("Submarine",
                                           "Assets/MeepballSub.obj",
                                           0,
                                           "Assets/Submarine.png",
                                           glm::vec3(-0.5f, -1.f, 0.f),
                                           glm::mat4(1.0f),
                                           glm::vec3(1.0f),
                                           glm::vec3(0.0f))};

    for (Model3D* model : models) model->loadModel();
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
    //* Note: Each face consist of two triangles, thus each face is made up of a pair of vertex
    // triplets (cuz triangles have three corners, duh)
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
    string skyboxTexturePaths[]{"Assets/Skybox/rainbow_rt.png",
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

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, skyCChannel;
        stbi_set_flip_vertically_on_load(false);
        unsigned char* data = stbi_load(skyboxTexturePaths[i].c_str(), &w, &h, &skyCChannel, 0);

        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0,
                         GL_RGB,
                         w,
                         h,
                         0,
                         GL_RGB,
                         GL_UNSIGNED_BYTE,
                         data);

            stbi_image_free(data);
        }

        stbi_set_flip_vertically_on_load(true);
    }
    //* - - - - - END OF SKYBOX TEXTURING - - - - -

    //* - - - - - CAMERA PART 1 - - - - -
    // PerspectiveCamera* perspectiveCamera = new PerspectiveCamera("Main", 90.0f);
    // OrthographicCamera
    // Camera* mainCamera                   = perspectiveCamera;
    glm::vec3 cameraPosition       = glm::vec3(0.f, 0.f, 3.f);
    glm::vec3 cameraViewCenter     = glm::vec3(0.f, 0.f, -1.f);
    glm::mat4 cameraPositionMatrix = glm::translate(glm::mat4(1.0f), cameraPosition * -1.0f);
    glm::mat4 cameraProjection =
        glm::perspective(glm::radians(90.f), float(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.f);
    //* - - - - - END OF CAMERA PART 1 - - - - -

    //* - - - - - WORLD FACTS - - - - -
    glm::vec3 WorldUp           = glm::vec3(0.f, 1.0f, 0.f);
    glm::vec3 Center            = glm::vec3(0.f);
    glm::vec3 ForwardVector     = glm::vec3(cameraViewCenter - cameraPosition);
    ForwardVector               = glm::normalize(ForwardVector);
    glm::vec3 RightVector       = glm::normalize(glm::cross(ForwardVector, WorldUp));
    glm::vec3 UpVector          = glm::normalize(glm::cross(RightVector, ForwardVector));
    //* - - - - - END OF WORLD FACTS - - - - -

    //* - - - - - CAMERA PART 2 - - - - -
    glm::mat4 cameraOrientation = glm::mat4(1.f);

    cameraOrientation[0][0]     = RightVector.x;
    cameraOrientation[1][0]     = RightVector.y;
    cameraOrientation[2][0]     = RightVector.z;

    cameraOrientation[0][1]     = UpVector.x;
    cameraOrientation[1][1]     = UpVector.y;
    cameraOrientation[2][1]     = UpVector.z;

    cameraOrientation[0][2]     = -ForwardVector.x;
    cameraOrientation[1][2]     = -ForwardVector.y;
    cameraOrientation[2][2]     = -ForwardVector.z;

    // glm::mat4 cameraView        = cameraOrientation * cameraPositionMatrix;
    glm::mat4 cameraView        = glm::lookAt(cameraPosition, cameraViewCenter, WorldUp);
    //* - - - - - END OF CAMERA PART 2 - - - - -

    //* - - - - - LIGHTS - - - - -
    glm::vec3 lightPosition     = glm::vec3(-1.f, -1.f, 0.f);
    glm::vec3 lightColor        = glm::vec3(1.f, 1.f, 1.f);
    float ambientStrength       = 0.1f;
    glm::vec3 ambientColor      = lightColor;
    float specularStrength      = 0.5f;
    float specularPhong         = 16;

    vector<Light*> lights       = {};
    vector<DirectionalLight*> directionalLights = {
       new DirectionalLight("Red Directional Light",
                            false,
                            glm::vec3(0.f, -1.f, 0.f),  //? Direction
                            glm::vec3(1.f, 0.f, 0.f),   //? Color
                            0.1f,                       //? Ambient Strength
                            glm::vec3(1.f, 0.f, 0.f),   //? Ambient Color
                            0.5f,                       //?Specular Strength
                            16,                         //?Specular Phong
                            2.0f),                      //? Brightness
       new DirectionalLight("Blue Directional Light",
                            false,
                            glm::vec3(0.f, 1.f, 0.f),  //? Direction
                            glm::vec3(0.f, 0.f, 1.f),  //? Color
                            0.1f,                      //? Ambient Strength
                            glm::vec3(0.f, 0.f, 1.f),  //? Ambient Color
                            0.5f,                      //?Specular Strength
                            16,                        //?Specular Phong
                            2.0f)                      //? Brightness
    };
    for (DirectionalLight* directionalLight : directionalLights) lights.push_back(directionalLight);

    vector<PointLight*> pointLights = {
       new PointLight("Green Point Light",
                      false,
                      glm::vec3(0.f, -1.f, 0.f),  //? Position
                      glm::vec3(0.f, 1.f, 0.f),   //? Color
                      0.1f,                       //? Ambient Strength
                      glm::vec3(0.f, 1.f, 0.f),   //? Ambient Color
                      0.5f,                       //?Specular Strength
                      16,                         //?Specular Phong
                      2.0f),                      //? Brightness
    };
    for (PointLight* pointLight : pointLights) lights.push_back(pointLight);

    vector<SpotLight*> spotLights = {
       new SpotLight("White Spotlight",
                     true,
                     glm::vec3(0.f, 5.f, 0.f),   //? Position
                     glm::vec3(0.f, -1.f, 0.f),  //? Direction
                     12.5f,                      //? Cone Size
                     glm::vec3(1.f, 1.f, 1.f),   //? Color
                     0.1f,                       //? Ambient Strength
                     glm::vec3(1.f, 1.f, 1.f),   //? Ambient Color
                     0.5f,                       //?Specular Strength
                     16,                         //?Specular Phong
                     10.0f),                     //? Brightness
    };
    for (SpotLight* spotLight : spotLights) lights.push_back(spotLight);
    for (Light* light : lights) {
        if (light->getEnabled()) activeLight = light;
    }

    //* - - - - - END OF LIGHTS - - - - -

    //* - - - - - RUNTIME - - - - -
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // modelOrientation.y += ROTATE_SPEED;

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

        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
        glUseProgram(lightingProgram);

        //* - - - - - CAMERA UPDATE - - - - -
        unsigned int cameraProjectionAddress = glGetUniformLocation(lightingProgram, "projection");
        glUniformMatrix4fv(cameraProjectionAddress, 1, GL_FALSE, glm::value_ptr(cameraProjection));

        unsigned int cameraViewAddress = glGetUniformLocation(lightingProgram, "view");
        glUniformMatrix4fv(cameraViewAddress, 1, GL_FALSE, glm::value_ptr(cameraView));

        GLuint cameraPositionAddress = glGetUniformLocation(lightingProgram, "cameraPosition");
        glUniform3fv(cameraPositionAddress, 1, glm::value_ptr(cameraPosition));
        //* - - - - - END OF CAMERA UPDATE - - - - -

        //* - - - - - MODEL UPDATE - - - - -

        //* - - - - - MODEL LIGHTING - - - - -
        for (Model3D* model : models) {
            glBindVertexArray(model->getVAO());

            GLuint modelTextureAddress = glGetUniformLocation(lightingProgram, "modelTexture");
            glBindTexture(GL_TEXTURE_2D, model->getTexture().getTexture());

            GLuint directionalLightCountAddress =
                glGetUniformLocation(lightingProgram, "directionalLightCount");
            glUniform1i(directionalLightCountAddress, GLint(directionalLights.size()));

            for (int i = 0; i < directionalLights.size(); i++) {
                if (directionalLights[i]->enabled) {
                    string address = "directionalLights[" + to_string(i) + "].direction";

                    GLuint lightDirectionAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(
                        lightDirectionAddress, 1, glm::value_ptr(directionalLights[i]->direction));

                    address = "directionalLights[" + to_string(i) + "].color";
                    GLuint lightColorAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(lightColorAddress, 1, glm::value_ptr(directionalLights[i]->color));

                    address = "directionalLights[" + to_string(i) + "].ambientStrength";
                    GLuint ambientStrengthAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(ambientStrengthAddress, directionalLights[i]->ambientStrength);

                    address = "directionalLights[" + to_string(i) + "].ambientColor";
                    GLuint ambientColorAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(
                        ambientColorAddress, 1, glm::value_ptr(directionalLights[i]->ambientColor));

                    address = "directionalLights[" + to_string(i) + "].specularStrength";
                    GLuint specularStrengthAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(specularStrengthAddress, directionalLights[i]->specularStrength);

                    address = "directionalLights[" + to_string(i) + "].specularPhong";
                    GLuint specularPhongAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(specularPhongAddress, directionalLights[i]->specularPhong);

                    address = "directionalLights[" + to_string(i) + "].brightness";
                    GLuint brightnessAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(brightnessAddress, directionalLights[i]->brightness);
                }
            }

            GLuint pointLightCountAddress =
                glGetUniformLocation(lightingProgram, "pointLightCount");
            glUniform1i(pointLightCountAddress, GLint(pointLights.size()));

            for (int i = 0; i < pointLights.size(); i++) {
                if (pointLights[i]->enabled) {
                    string address = "pointLights[" + to_string(i) + "].position";

                    GLuint lightPositionAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(lightPositionAddress, 1, glm::value_ptr(pointLights[i]->position));

                    address = "pointLights[" + to_string(i) + "].color";
                    GLuint lightColorAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(lightColorAddress, 1, glm::value_ptr(pointLights[i]->color));

                    address = "pointLights[" + to_string(i) + "].ambientStrength";
                    GLuint ambientStrengthAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(ambientStrengthAddress, pointLights[i]->ambientStrength);

                    address = "pointLights[" + to_string(i) + "].ambientColor";
                    GLuint ambientColorAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(
                        ambientColorAddress, 1, glm::value_ptr(pointLights[i]->ambientColor));

                    address = "pointLights[" + to_string(i) + "].specularStrength";
                    GLuint specularStrengthAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(specularStrengthAddress, pointLights[i]->specularStrength);

                    address = "pointLights[" + to_string(i) + "].specularPhong";
                    GLuint specularPhongAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(specularPhongAddress, pointLights[i]->specularPhong);

                    address = "pointLights[" + to_string(i) + "].brightness";
                    GLuint brightnessAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(brightnessAddress, pointLights[i]->brightness);
                }
            }

            GLuint spotLightCountAddress = glGetUniformLocation(lightingProgram, "spotLightCount");
            glUniform1i(spotLightCountAddress, GLint(spotLights.size()));

            for (int i = 0; i < spotLights.size(); i++) {
                if (spotLights[i]->enabled) {
                    string address = "spotLights[" + to_string(i) + "].position";

                    GLuint lightPositionAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(lightPositionAddress, 1, glm::value_ptr(spotLights[i]->position));

                    address = "spotLights[" + to_string(i) + "].direction";
                    GLuint lightDirectionAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(
                        lightDirectionAddress, 1, glm::value_ptr(spotLights[i]->direction));

                    address                = "spotLights[" + to_string(i) + "].coneSize";
                    GLuint coneSizeAddress = glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(coneSizeAddress, spotLights[i]->coneSize);

                    address = "spotLights[" + to_string(i) + "].color";
                    GLuint lightColorAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(lightColorAddress, 1, glm::value_ptr(spotLights[i]->color));

                    address = "spotLights[" + to_string(i) + "].ambientStrength";
                    GLuint ambientStrengthAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(ambientStrengthAddress, spotLights[i]->ambientStrength);

                    address = "spotLights[" + to_string(i) + "].ambientColor";
                    GLuint ambientColorAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform3fv(
                        ambientColorAddress, 1, glm::value_ptr(spotLights[i]->ambientColor));

                    address = "spotLights[" + to_string(i) + "].specularStrength";
                    GLuint specularStrengthAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(specularStrengthAddress, spotLights[i]->specularStrength);

                    address = "spotLights[" + to_string(i) + "].specularPhong";
                    GLuint specularPhongAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(specularPhongAddress, spotLights[i]->specularPhong);

                    address = "spotLights[" + to_string(i) + "].brightness";
                    GLuint brightnessAddress =
                        glGetUniformLocation(lightingProgram, address.c_str());
                    glUniform1f(brightnessAddress, spotLights[i]->brightness);
                }
            }
            //* - - - - - END OF MODEL LIGHTING - - - - -

            //* - - - - - MODEL TRANSFORM - - - - -
            model->update();
            unsigned int modelTransformAddress = glGetUniformLocation(lightingProgram, "transform");
            glUniformMatrix4fv(
                modelTransformAddress, 1, GL_FALSE, glm::value_ptr(model->getPositionMatrix()));
            //* - - - - - END OF MODEL TRANSFORM - - - - -

            //* - - - - - MODEL RENDERING - - - - -
            glUniform1i(modelTextureAddress, model->getTexture().getTextureCount());
            glDrawArrays(GL_TRIANGLES, 0, GLint(model->getFullVertexData().size() / 8));
            //* - - - - - END OF MODEL RENDERING - - - - -
        }

        // //* - - - - - MODEL LIGHTING - - - - -
        // glBindVertexArray(modelVAO);

        // GLuint modelTextureAddress = glGetUniformLocation(lightingProgram, "modelTexture");
        // glBindTexture(GL_TEXTURE_2D, texture);

        // GLuint directionalLightCountAddress =
        //     glGetUniformLocation(lightingProgram, "directionalLightCount");
        // glUniform1i(directionalLightCountAddress, GLint(directionalLights.size()));

        // for (int i = 0; i < directionalLights.size(); i++) {
        //     if (directionalLights[i]->enabled) {
        //         string address = "directionalLights[" + to_string(i) + "].direction";

        //         GLuint lightDirectionAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform3fv(
        //             lightDirectionAddress, 1, glm::value_ptr(directionalLights[i]->direction));

        //         address                  = "directionalLights[" + to_string(i) + "].color";
        //         GLuint lightColorAddress = glGetUniformLocation(lightingProgram,
        //         address.c_str()); glUniform3fv(lightColorAddress, 1,
        //         glm::value_ptr(directionalLights[i]->color));

        //         address = "directionalLights[" + to_string(i) + "].ambientStrength";
        //         GLuint ambientStrengthAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(ambientStrengthAddress, directionalLights[i]->ambientStrength);

        //         address = "directionalLights[" + to_string(i) + "].ambientColor";
        //         GLuint ambientColorAddress = glGetUniformLocation(lightingProgram,
        //         address.c_str()); glUniform3fv(
        //             ambientColorAddress, 1, glm::value_ptr(directionalLights[i]->ambientColor));

        //         address = "directionalLights[" + to_string(i) + "].specularStrength";
        //         GLuint specularStrengthAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(specularStrengthAddress, directionalLights[i]->specularStrength);

        //         address = "directionalLights[" + to_string(i) + "].specularPhong";
        //         GLuint specularPhongAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(specularPhongAddress, directionalLights[i]->specularPhong);

        //         address = "directionalLights[" + to_string(i) + "].brightness";
        //         GLuint brightnessAddress = glGetUniformLocation(lightingProgram,
        //         address.c_str()); glUniform1f(brightnessAddress,
        //         directionalLights[i]->brightness);
        //     }
        // }

        // GLuint pointLightCountAddress = glGetUniformLocation(lightingProgram, "pointLightCount");
        // glUniform1i(pointLightCountAddress, GLint(pointLights.size()));

        // for (int i = 0; i < pointLights.size(); i++) {
        //     if (pointLights[i]->enabled) {
        //         string address = "pointLights[" + to_string(i) + "].position";

        //         GLuint lightPositionAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform3fv(lightPositionAddress, 1, glm::value_ptr(pointLights[i]->position));

        //         address                  = "pointLights[" + to_string(i) + "].color";
        //         GLuint lightColorAddress = glGetUniformLocation(lightingProgram,
        //         address.c_str()); glUniform3fv(lightColorAddress, 1,
        //         glm::value_ptr(pointLights[i]->color));

        //         address = "pointLights[" + to_string(i) + "].ambientStrength";
        //         GLuint ambientStrengthAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(ambientStrengthAddress, pointLights[i]->ambientStrength);

        //         address                    = "pointLights[" + to_string(i) + "].ambientColor";
        //         GLuint ambientColorAddress = glGetUniformLocation(lightingProgram,
        //         address.c_str()); glUniform3fv(ambientColorAddress, 1,
        //         glm::value_ptr(pointLights[i]->ambientColor));

        //         address = "pointLights[" + to_string(i) + "].specularStrength";
        //         GLuint specularStrengthAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(specularStrengthAddress, pointLights[i]->specularStrength);

        //         address = "pointLights[" + to_string(i) + "].specularPhong";
        //         GLuint specularPhongAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(specularPhongAddress, pointLights[i]->specularPhong);

        //         address                  = "pointLights[" + to_string(i) + "].brightness";
        //         GLuint brightnessAddress = glGetUniformLocation(lightingProgram,
        //         address.c_str()); glUniform1f(brightnessAddress, pointLights[i]->brightness);
        //     }
        // }

        // GLuint spotLightCountAddress = glGetUniformLocation(lightingProgram, "spotLightCount");
        // glUniform1i(spotLightCountAddress, GLint(spotLights.size()));

        // for (int i = 0; i < spotLights.size(); i++) {
        //     if (spotLights[i]->enabled) {
        //         string address = "spotLights[" + to_string(i) + "].position";

        //         GLuint lightPositionAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform3fv(lightPositionAddress, 1, glm::value_ptr(spotLights[i]->position));

        //         address = "spotLights[" + to_string(i) + "].direction";
        //         GLuint lightDirectionAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform3fv(lightDirectionAddress, 1, glm::value_ptr(spotLights[i]->direction));

        //         address                = "spotLights[" + to_string(i) + "].coneSize";
        //         GLuint coneSizeAddress = glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(coneSizeAddress, spotLights[i]->coneSize);

        //         address                  = "spotLights[" + to_string(i) + "].color";
        //         GLuint lightColorAddress = glGetUniformLocation(lightingProgram,
        //         address.c_str()); glUniform3fv(lightColorAddress, 1,
        //         glm::value_ptr(spotLights[i]->color));

        //         address = "spotLights[" + to_string(i) + "].ambientStrength";
        //         GLuint ambientStrengthAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(ambientStrengthAddress, spotLights[i]->ambientStrength);

        //         address                    = "spotLights[" + to_string(i) + "].ambientColor";
        //         GLuint ambientColorAddress = glGetUniformLocation(lightingProgram,
        //         address.c_str()); glUniform3fv(ambientColorAddress, 1,
        //         glm::value_ptr(spotLights[i]->ambientColor));

        //         address = "spotLights[" + to_string(i) + "].specularStrength";
        //         GLuint specularStrengthAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(specularStrengthAddress, spotLights[i]->specularStrength);

        //         address = "spotLights[" + to_string(i) + "].specularPhong";
        //         GLuint specularPhongAddress =
        //             glGetUniformLocation(lightingProgram, address.c_str());
        //         glUniform1f(specularPhongAddress, spotLights[i]->specularPhong);

        //         address                  = "spotLights[" + to_string(i) + "].brightness";
        //         GLuint brightnessAddress = glGetUniformLocation(lightingProgram,
        //         address.c_str()); glUniform1f(brightnessAddress, spotLights[i]->brightness);
        //     }
        // }

        // GLuint cameraPositionAddress = glGetUniformLocation(lightingProgram, "cameraPosition");
        // glUniform3fv(cameraPositionAddress, 1, glm::value_ptr(cameraPosition));
        // //* - - - - - END OF MODEL LIGHTING - - - - -

        // //* - - - - - MODEL RENDERING - - - - -
        // glUniform1i(modelTextureAddress, 0);
        // glDrawArrays(GL_TRIANGLES, 0, GLint(fullVertexData.size() / 8));
        //* - - - - - END OF MODEL RENDERING - - - - -
        //* - - - - - END OF MODEL UPDATE - - - - -
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    //* - - - - - END OF RUNTIME - - - - -

    //* - - - - - CLEAN UP - - - - -
    // glDeleteVertexArrays(1, &modelVAO);
    // glDeleteBuffers(1, &modelVBO);
    glDeleteShader(lightingVertexShader);
    glDeleteShader(lightingFragmentShader);
    glDeleteShader(skyboxVertexShader);
    glDeleteShader(skyboxFragmentShader);
    //* - - - - - END OF CLEAN UP - - - - -
    glfwTerminate();
    return 0;
}