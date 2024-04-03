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

/*References used:
Camera Rotation: Camera(n.d.).LearnOpenGL.https://learnopengl.com/Getting-started/Camera
*/

using namespace std;
using namespace models;

//* - - - - - PROGRAMMING CHALLENGE 2 VARIABLES - - - - -
bool controllingModel                       = true;
Light* activeLight                          = NULL;
vector<DirectionalLight*> directionalLights = {};
vector<PointLight*> pointLights             = {};
vector<SpotLight*> spotLights               = {};
vector<Light*> lights                       = {};
Model3D* activeModel                        = NULL;
vector<Model3D*> model3ds                   = {};

Camera* currentCamera;
//* - - - - - END OF PROGRAMMING CHALLENGE 2 VARIABLES - - - - -

//* - - - - - CAMERA PART 1 - - - - -

//* - - - - - END OF CAMERA PART 1 - - - - -

//? Reserved GLFW Function for Keyboard Inputs
void Key_Callback(
    GLFWwindow* window,  //? Which window did we get the event?
    int key,             //? What key was pressed?
    int scancode,        //? What exact physical key was pressed?
    int action,  //? What is being done to the key? [GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE]
    int mods) {  //? Which modifer keys are held? [alt, control, shift, Super, num lock, and
                 // caps
                 // lock]
}

int main(void) {
    //* - - - - - WINDOW CREATION - - - - -
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Quiz 3 - UBAY", NULL, NULL);
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

    GLuint lightingShaderProgram = glCreateProgram();
    glAttachShader(lightingShaderProgram, lightingVertexShader);
    glAttachShader(lightingShaderProgram, lightingFragmentShader);

    glLinkProgram(lightingShaderProgram);

    GLuint skyboxShaderProgram = glCreateProgram();
    glAttachShader(skyboxShaderProgram, skyboxVertexShader);
    glAttachShader(skyboxShaderProgram, skyboxFragmentShader);

    glLinkProgram(skyboxShaderProgram);
    //* - - - - - END OF SHADER CREATION - - - - -

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
    PerspectiveCamera* perspectiveCamera = new PerspectiveCamera("Main", 60.0f);
    currentCamera                        = perspectiveCamera;
    //* - - - - - END OF CAMERA PART 1 - - - - -

    //* - - - - - WORLD FACTS - - - - -
    glm::vec3 WorldUp                    = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Center                     = glm::vec3(0.0f);
    glm::vec3 ForwardVector =
        glm::vec3(currentCamera->getViewCenter() - currentCamera->getPosition());
    ForwardVector         = glm::normalize(ForwardVector);
    glm::vec3 RightVector = glm::normalize(glm::cross(ForwardVector, WorldUp));
    glm::vec3 UpVector    = glm::normalize(glm::cross(RightVector, ForwardVector));
    //* - - - - - END OF WORLD FACTS - - - - -

    //* - - - - - LIGHTS - - - - -
    directionalLights     = {
    //    new DirectionalLight("White Directional Light",
    //                         false,
    //                         glm::vec3(0.0f, 1.f, 0.0f),  //? Direction
    //                         glm::vec3(1.f, 1.f, 1.f),    //? Color
    //                         0.1f,                        //? Ambient Strength
    //                         glm::vec3(1.f, 1.f, 1.f),    //? Ambient Color
    //                         0.5f,                        //?Specular Strength
    //                         16,                          //?Specular Phong
    //                         2.0f),                       //? Brightness
    };
    for (DirectionalLight* directionalLight : directionalLights) lights.push_back(directionalLight);

    pointLights = {
       new PointLight("White Point Light",
                      true,
                      glm::vec3(0.0f, 0.8f, 0.2f),  //? Position
                      glm::vec3(1.f, 1.f, 1.f),     //? Color
                      0.1f,                         //? Ambient Strength
                      glm::vec3(1.f, 1.f, 1.f),     //? Ambient Color
                      0.5f,                         //?Specular Strength
                      16,                           //?Specular Phong
                      1.2f),                        //? Brightness
    };
    for (PointLight* pointLight : pointLights) lights.push_back(pointLight);

    spotLights = {
    //    new SpotLight("White Spotlight",
    //                  false,
    //                  glm::vec3(0.0f, 1.f, 0.0f),   //? Position
    //                  glm::vec3(0.0f, -1.f, 0.0f),  //? Direction
    //                  12.5f,                        //? Cone Size
    //                  glm::vec3(1.f, 1.f, 1.f),     //? Color
    //                  0.1f,                         //? Ambient Strength
    //                  glm::vec3(1.f, 1.f, 1.f),     //? Ambient Color
    //                  0.5f,                         //?Specular Strength
    //                  16,                           //?Specular Phong
    //                  1.0f),                        //? Brightness
    };
    for (SpotLight* spotLight : spotLights) lights.push_back(spotLight);
    for (Light* light : lights) {
        if (light->getEnabled()) activeLight = light;
    }

    //* - - - - - END OF LIGHTS - - - - -

    //* - - - - - MODEL LOADING - - - - -
    model3ds = {
       new Model3D("Brickwall",                           //? Model Name
                   "Assets/Models/plane.obj",             //? Model Path
                   0,                                     //? Model Count
                   "Assets/Models/brickwall.jpg",         //? Texture Path
                   "Assets/Models/brickwall_normal.jpg",  //? Normal Path
                   glm::vec3(0.0f, 0.0f, 0.0f),           //? Position
                   glm::mat4(1.0f),                       //? Position Matrix
                   glm::vec3(1.0f),                       //? Scale
                   glm::vec3(0.0f, 0.0f, 90.0f)),         //? Orientation
    };
    activeModel = model3ds.front();

    for (Model3D* model : model3ds) model->loadModel();
    //* - - - - - END OF MODEL LOADING - - - - -

    //* - - - - - RUNTIME - - - - -
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentCamera->setView(
            glm::lookAt(currentCamera->getPosition(), currentCamera->getViewCenter(), WorldUp));

        //* - - - - - UPDATE - - - - -
        activeModel->setOrientation(glm::vec3(activeModel->getOrientation().x + ROTATE_SPEED,
                                              activeModel->getOrientation().y,
                                              activeModel->getOrientation().z));
        //* - - - - - END OF UPDATE - - - - -

        //* - - - - - SKYBOX SHADER SWITCH - - - - -
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxShaderProgram);
        //* - - - - - END OF SKYBOX SHADER SWITCH - - - - -

        //* - - - - - SKYBOX RENDERING - - - - -
        glm::mat4 skyboxView           = glm::mat4(1.f);
        skyboxView                     = glm::mat4(glm::mat3(currentCamera->getView()));

        unsigned int skyboxViewAddress = glGetUniformLocation(skyboxShaderProgram, "view");
        glUniformMatrix4fv(skyboxViewAddress, 1, GL_FALSE, glm::value_ptr(skyboxView));

        unsigned skyboxProjectionAddress = glGetUniformLocation(skyboxShaderProgram, "projection");
        glUniformMatrix4fv(
            skyboxProjectionAddress, 1, GL_FALSE, glm::value_ptr(currentCamera->getProjection()));

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        if (DRAW_SKYBOX) glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //* - - - - - END OF SKYBOX RENDERING - - - - -

        //* - - - - - LIGHTING SHADER SWITCH - - - - -
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
        glUseProgram(lightingShaderProgram);
        //* - - - - - END OF LIGHTING SHADER SWITCH - - - - -

        //* - - - - - CAMERA UPDATE - - - - -
        unsigned int cameraProjectionAddress =
            glGetUniformLocation(lightingShaderProgram, "projection");
        glUniformMatrix4fv(
            cameraProjectionAddress, 1, GL_FALSE, glm::value_ptr(currentCamera->getProjection()));

        unsigned int cameraViewAddress = glGetUniformLocation(lightingShaderProgram, "view");
        glUniformMatrix4fv(
            cameraViewAddress, 1, GL_FALSE, glm::value_ptr(currentCamera->getView()));

        GLuint cameraPositionAddress =
            glGetUniformLocation(lightingShaderProgram, "cameraPosition");
        glUniform3fv(cameraPositionAddress, 1, glm::value_ptr(currentCamera->getPosition()));
        //* - - - - - END OF CAMERA UPDATE - - - - -

        //* - - - - - MODEL UPDATE - - - - -
        for (Model3D* model : model3ds) {
            //* - - - - - MODEL LIGHTING - - - - -
            glBindVertexArray(*model->getVAO());

            switch (model->getTexture().getTextureCount()) {
                case 0:
                    glActiveTexture(GL_TEXTURE0);
                    break;
                case 2:
                    glActiveTexture(GL_TEXTURE2);
                    break;
                case 4:
                    glActiveTexture(GL_TEXTURE4);
                    break;
                case 6:
                    glActiveTexture(GL_TEXTURE6);
                    break;
                case 8:
                    glActiveTexture(GL_TEXTURE8);
                    break;
                case 10:
                    glActiveTexture(GL_TEXTURE10);
                    break;
                case 12:
                    glActiveTexture(GL_TEXTURE12);
                    break;
                case 14:
                    glActiveTexture(GL_TEXTURE14);
                    break;
                case 16:
                    glActiveTexture(GL_TEXTURE16);
                    break;
                case 18:
                    glActiveTexture(GL_TEXTURE18);
                    break;
            }
            GLuint modelTextureAddress =
                glGetUniformLocation(lightingShaderProgram, "modelTexture");
            glBindTexture(GL_TEXTURE_2D, model->getTexture().getTexture());

            switch (model->getNormalMap().getNormalCount()) {
                case 1:
                    glActiveTexture(GL_TEXTURE1);
                    break;
                case 3:
                    glActiveTexture(GL_TEXTURE3);
                    break;
                case 5:
                    glActiveTexture(GL_TEXTURE5);
                    break;
                case 7:
                    glActiveTexture(GL_TEXTURE7);
                    break;
                case 9:
                    glActiveTexture(GL_TEXTURE9);
                    break;
                case 11:
                    glActiveTexture(GL_TEXTURE11);
                    break;
                case 13:
                    glActiveTexture(GL_TEXTURE13);
                    break;
                case 15:
                    glActiveTexture(GL_TEXTURE15);
                    break;
                case 17:
                    glActiveTexture(GL_TEXTURE17);
                    break;
                case 19:
                    glActiveTexture(GL_TEXTURE19);
                    break;
            }
            GLuint modelNormalAddress =
                glGetUniformLocation(lightingShaderProgram, "modelNormalTexture");
            glBindTexture(GL_TEXTURE_2D, model->getNormalMap().getNormal());

            GLuint directionalLightCountAddress =
                glGetUniformLocation(lightingShaderProgram, "directionalLightCount");
            glUniform1i(directionalLightCountAddress, GLint(directionalLights.size()));

            for (int i = 0; i < directionalLights.size(); i++) {
                if (directionalLights[i]->enabled) {
                    string address = "directionalLights[" + to_string(i) + "].direction";

                    GLuint lightDirectionAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(
                        lightDirectionAddress, 1, glm::value_ptr(directionalLights[i]->direction));

                    address = "directionalLights[" + to_string(i) + "].color";
                    GLuint lightColorAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(lightColorAddress, 1, glm::value_ptr(directionalLights[i]->color));

                    address = "directionalLights[" + to_string(i) + "].ambientStrength";
                    GLuint ambientStrengthAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(ambientStrengthAddress, directionalLights[i]->ambientStrength);

                    address = "directionalLights[" + to_string(i) + "].ambientColor";
                    GLuint ambientColorAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(
                        ambientColorAddress, 1, glm::value_ptr(directionalLights[i]->ambientColor));

                    address = "directionalLights[" + to_string(i) + "].specularStrength";
                    GLuint specularStrengthAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(specularStrengthAddress, directionalLights[i]->specularStrength);

                    address = "directionalLights[" + to_string(i) + "].specularPhong";
                    GLuint specularPhongAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(specularPhongAddress, directionalLights[i]->specularPhong);

                    address = "directionalLights[" + to_string(i) + "].brightness";
                    GLuint brightnessAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(brightnessAddress, directionalLights[i]->brightness);
                }
            }

            GLuint pointLightCountAddress =
                glGetUniformLocation(lightingShaderProgram, "pointLightCount");
            glUniform1i(pointLightCountAddress, GLint(pointLights.size()));

            for (int i = 0; i < pointLights.size(); i++) {
                if (pointLights[i]->enabled) {
                    string address = "pointLights[" + to_string(i) + "].position";

                    GLuint lightPositionAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(lightPositionAddress, 1, glm::value_ptr(pointLights[i]->position));

                    address = "pointLights[" + to_string(i) + "].color";
                    GLuint lightColorAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(lightColorAddress, 1, glm::value_ptr(pointLights[i]->color));

                    address = "pointLights[" + to_string(i) + "].ambientStrength";
                    GLuint ambientStrengthAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(ambientStrengthAddress, pointLights[i]->ambientStrength);

                    address = "pointLights[" + to_string(i) + "].ambientColor";
                    GLuint ambientColorAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(
                        ambientColorAddress, 1, glm::value_ptr(pointLights[i]->ambientColor));

                    address = "pointLights[" + to_string(i) + "].specularStrength";
                    GLuint specularStrengthAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(specularStrengthAddress, pointLights[i]->specularStrength);

                    address = "pointLights[" + to_string(i) + "].specularPhong";
                    GLuint specularPhongAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(specularPhongAddress, pointLights[i]->specularPhong);

                    address = "pointLights[" + to_string(i) + "].brightness";
                    GLuint brightnessAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(brightnessAddress, pointLights[i]->brightness);
                }
            }

            GLuint spotLightCountAddress =
                glGetUniformLocation(lightingShaderProgram, "spotLightCount");
            glUniform1i(spotLightCountAddress, GLint(spotLights.size()));

            for (int i = 0; i < spotLights.size(); i++) {
                if (spotLights[i]->enabled) {
                    string address = "spotLights[" + to_string(i) + "].position";

                    GLuint lightPositionAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(lightPositionAddress, 1, glm::value_ptr(spotLights[i]->position));

                    address = "spotLights[" + to_string(i) + "].direction";
                    GLuint lightDirectionAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(
                        lightDirectionAddress, 1, glm::value_ptr(spotLights[i]->direction));

                    address = "spotLights[" + to_string(i) + "].coneSize";
                    GLuint coneSizeAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(coneSizeAddress, spotLights[i]->coneSize);

                    address = "spotLights[" + to_string(i) + "].color";
                    GLuint lightColorAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(lightColorAddress, 1, glm::value_ptr(spotLights[i]->color));

                    address = "spotLights[" + to_string(i) + "].ambientStrength";
                    GLuint ambientStrengthAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(ambientStrengthAddress, spotLights[i]->ambientStrength);

                    address = "spotLights[" + to_string(i) + "].ambientColor";
                    GLuint ambientColorAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform3fv(
                        ambientColorAddress, 1, glm::value_ptr(spotLights[i]->ambientColor));

                    address = "spotLights[" + to_string(i) + "].specularStrength";
                    GLuint specularStrengthAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(specularStrengthAddress, spotLights[i]->specularStrength);

                    address = "spotLights[" + to_string(i) + "].specularPhong";
                    GLuint specularPhongAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(specularPhongAddress, spotLights[i]->specularPhong);

                    address = "spotLights[" + to_string(i) + "].brightness";
                    GLuint brightnessAddress =
                        glGetUniformLocation(lightingShaderProgram, address.c_str());
                    glUniform1f(brightnessAddress, spotLights[i]->brightness);
                }
            }
            //* - - - - - END OF MODEL LIGHTING - - - - -

            //* - - - - - MODEL TRANSFORM - - - - -
            model->update();
            unsigned int modelTransformAddress =
                glGetUniformLocation(lightingShaderProgram, "transform");
            glUniformMatrix4fv(
                modelTransformAddress, 1, GL_FALSE, glm::value_ptr(model->getPositionMatrix()));
            //* - - - - - END OF MODEL TRANSFORM - - - - -

            //* - - - - - MODEL RENDERING - - - - -
            glUniform1i(modelTextureAddress, model->getTexture().getTextureCount());
            if (model->getEnabled())
                glDrawArrays(
                    GL_TRIANGLES, 0, GLint(model->getFullVertexData().size() / STRIDE_LENGTH));
            //* - - - - - END OF MODEL RENDERING - - - - -
        }

        //* - - - - - END OF MODEL UPDATE - - - - -
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //* - - - - - END OF RUNTIME - - - - -

    //* - - - - - CLEAN UP - - - - -
    for (Model3D* model : model3ds) {
        glDeleteVertexArrays(1, model->getVAO());
        glDeleteBuffers(1, model->getVBO());
    }
    glDeleteShader(lightingVertexShader);
    glDeleteShader(lightingFragmentShader);
    glDeleteShader(skyboxVertexShader);
    glDeleteShader(skyboxFragmentShader);
    //* - - - - - END OF CLEAN UP - - - - -
    glfwTerminate();
    return 0;
}