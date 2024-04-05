// clang-format off
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "GameObjects/Cameras/Camera.hpp"
#include "GameObjects/Cameras/OrthographicCamera/OrthographicCamera.hpp"
#include "GameObjects/Cameras/PerspectiveCamera/PerspectiveCamera.hpp"
#include "GameObjects/Cameras/FirstPersonCamera/FirstPersonCamera.hpp"

#include "GameObjects/Lights/Light.hpp"
#include "GameObjects/Lights/DirectionalLight/DirectionalLight.hpp"
#include "GameObjects/Lights/SpotLight/SpotLight.hpp"
#include "GameObjects/Lights/PointLight/PointLight.hpp"
#include "GameObjects/MyTexture/MyTexture.hpp"
#include "GameObjects/MyNormal/MyNormal.hpp"
#include "GameObjects/Model3D/Model3D.hpp"
#include "GameObjects/Player/Player.hpp"
#include "GameObjects/Shader/Shader.hpp"
#include "stdafx.h"
// clang-format on

/*References used:
Camera Rotation: Camera(n.d.).LearnOpenGL.https://learnopengl.com/Getting-started/Camera
*/

using namespace std;
using namespace models;

//* - - - - - POINTERS AND CONTAINERS - - - - -
vector<DirectionalLight*> directionalLights = {};
vector<PointLight*> pointLights             = {};
vector<SpotLight*> spotLights               = {};
vector<Light*> lights                       = {};
Model3D* activeModel                        = NULL;

vector<Model3D*> model3ds                   = {};
Player* player                              = NULL;

PerspectiveCamera* perspectiveCamera = new PerspectiveCamera("Main", 90.0f);
FirstPersonCamera* firstPOVCamera = new FirstPersonCamera("first POV", 50.0f);
OrthographicCamera* orthographicCamera = new OrthographicCamera("Ortho Cam");

vector<Camera*> cameras                     = {};
Camera* currentCamera                       = perspectiveCamera;

const float radius = 5.0f;
double xpos = 0.0f, ypos = 0.0f;
float x_mod = 0.0f, y_mod = 0.0f, z_mod = 0.0f;
bool bStart = true;
int nCameraCounter = 1;

bool firstMouse = true, bPerspective = false;
float yaw = -90.0f;
float pitch;
float lastX, lastY;
float x_direction = 0.0f, z_direction = 0.0f, y_direction = 0.0f;
glm::vec3 direction;
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//* - - - - - END OF POINTERS AND CONTAINERS - - - - -

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;


    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}  

/*GLFW built-in method that checks if the mouse is within the program's window, else otherwise*/
void cursor_enter_callback(GLFWwindow* window, int entered)
{
    //if the mouse enters the screen and the current camera is the perspective Camera
    if (entered)
    {
        std::cout << "mouse enters window" << std::endl;
             glfwGetCursorPos(window, &xpos, &ypos);
             glfwSetCursorPosCallback(window, mouse_callback);
    }
    else
    {
        std::cout << "mouse leaves window" << std::endl;
        //restats cameraFront
    }
}

//? Reserved GLFW Function for Keyboard Inputs
void Key_Callback(
    GLFWwindow* window,  //? Which window did we get the event?
    int key,             //? What key was pressed?
    int scancode,        //? What exact physical key was pressed?
    int action,  //? What is being done to the key? [GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE]
    int mods) {  //? Which modifer keys are held? [alt, control, shift, Super, num lock, and caps
                 //?lock]
    switch (key) {
        //| TODO: Toggle Bird's Eye View: Choose whether the player can still press 1 to exit
        //| bird's eye view, or require them to toggle back using 2 before being able to switch to
        //| 1st & 3rd  person view
        case GLFW_KEY_1:
            if (nCameraCounter % 2 != 0) {
                currentCamera = firstPOVCamera;
            }
            else {
                currentCamera = perspectiveCamera;
            }
            std::cout << currentCamera->getName() << " has been enabled!" << std::endl;

            if (action == GLFW_RELEASE)nCameraCounter++;
            break;
        case GLFW_KEY_2:
            currentCamera = orthographicCamera;
            std::cout << "Orthographic Camera has been enabled!" << std::endl;
            break;
            
        //| TODO: Pan Bird's Eye View Camera: Player does NOT own this camera.)
        case GLFW_KEY_UP:
            break;
            z_mod += 1.0f;
            break;
        case GLFW_KEY_DOWN:
            z_mod -= 1.0f;
            break;
        case GLFW_KEY_LEFT:
            x_mod -= 1.0f;
            break;
        case GLFW_KEY_RIGHT:
            x_mod += 1.0f;
            break;
        default:
            player->playerKeyboardInput(key, action);
            break;

    }
}

int main(void) {
    //* - - - - - WINDOW CREATION - - - - -
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "No Marios Submarine", NULL, NULL);
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

    //* - - - - - PLAYER INITIALIZATION - - - - -
    player = new Player();
    //* - - - - - END OF PLAYER INITIALIZATION - - - - -

    //* - - - - - SHADER CREATION - - - - -
    Shader lightingFragmentShader("Shaders/main.frag", ShaderType::FRAGMENT);
    lightingFragmentShader.loadShader();
    Shader lightingVertexShader("Shaders/main.vert", ShaderType::VERTEX);
    lightingVertexShader.loadShader();
    Shader skyboxFragmentShader("Shaders/skybox.frag", ShaderType::FRAGMENT);
    skyboxFragmentShader.loadShader();
    Shader skyboxVertexShader("Shaders/skybox.vert", ShaderType::VERTEX);
    skyboxVertexShader.loadShader();

    GLuint lightingShaderProgram = glCreateProgram();
    glAttachShader(lightingShaderProgram, lightingVertexShader.getShader());
    glAttachShader(lightingShaderProgram, lightingFragmentShader.getShader());

    glLinkProgram(lightingShaderProgram);

    GLuint skyboxShaderProgram = glCreateProgram();
    glAttachShader(skyboxShaderProgram, skyboxVertexShader.getShader());
    glAttachShader(skyboxShaderProgram, skyboxFragmentShader.getShader());

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
       -1.0f, -1.0f,  1.0f, //? 0 - Near Bottom Left Corner
        1.0f, -1.0f,  1.0f, //? 1 - Near Bottom Right Corner
        1.0f, -1.0f, -1.0f, //? 2 - Far Bottom Right Corner
       -1.0f, -1.0f, -1.0f, //? 3 - Far Bottom Left Corner
       -1.0f,  1.0f,  1.0f, //? 4 - Near Top Left Corner
        1.0f,  1.0f,  1.0f, //? 5 - Near Top Right Corner
        1.0f,  1.0f, -1.0f, //? 6 - Far Top Right Corner
       -1.0f,  1.0f, -1.0f  //? 7 - Far Top Left Corner
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
    string skyboxTexturePaths[]{"Assets/Skybox/underwater_rt.png",
                                "Assets/Skybox/underwater_lf.png",
                                "Assets/Skybox/underwater_up.png",
                                "Assets/Skybox/underwater_dn.png",
                                "Assets/Skybox/underwater_ft.png",
                                "Assets/Skybox/underwater_bk.png"};

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
                         GL_RGBA,
                         w,
                         h,
                         0,
                         GL_RGBA,
                         GL_UNSIGNED_BYTE,
                         data);

            stbi_image_free(data);
        }

        stbi_set_flip_vertically_on_load(true);
    }
    //* - - - - - END OF SKYBOX TEXTURING - - - - -

    //* - - - - - CAMERAS - - - - -
    //| TODO: Add the Bird's Eye View Camera to the vector below using:
    //| new OrthographicCamera()
    //| Tip: Checkout MODEL LOADING & LIGHTS
    cameras           = {player->getThirdPersonView(), player->getFirstPersonView(), new OrthographicCamera("Ortho Cam")};

    //? You may use this value however you need.
    currentCamera     = cameras.front();
    //* - - - - - END OF CAMERAS - - - - -

    //* - - - - - WORLD FACTS - - - - -
    glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Center  = glm::vec3(0.0f);
    glm::vec3 ForwardVector =
        glm::vec3(currentCamera->getViewCenter() - currentCamera->getPosition());
    ForwardVector         = glm::normalize(ForwardVector);
    glm::vec3 RightVector = glm::normalize(glm::cross(ForwardVector, WorldUp));
    glm::vec3 UpVector    = glm::normalize(glm::cross(RightVector, ForwardVector));
    //* - - - - - END OF WORLD FACTS - - - - -

    //* - - - - - LIGHTS - - - - -
    directionalLights     = {
       new DirectionalLight("Light Blue Directional Light",
                            true,
                            glm::vec3(0.0f, 1.0f, 0.0f),     //? Direction
                            glm::vec3(0.23f, 0.26f, 0.92f),  //? Color
                            0.1f,                            //? Ambient Strength
                            glm::vec3(0.63f, 0.86f, 0.92f),  //? Ambient Color
                            0.5f,                            //? Specular Strength
                            16,                              //? Specular Phong
                            3.0f),                           //? Brightness
    };
    for (DirectionalLight* directionalLight : directionalLights) lights.push_back(directionalLight);

    pointLights = {
       //    new PointLight("White Point Light",
       //                   true,
       //                   glm::vec3(0.0f, 0.8f, 0.2f),  //? Position
       //                   glm::vec3(1.0f, 1.0f, 1.0f),     //? Color
       //                   0.1f,                         //? Ambient Strength
       //                   glm::vec3(1.0f, 1.0f, 1.0f),     //? Ambient Color
       //                   0.5f,                         //? Specular Strength
       //                   16,                           //? Specular Phong
       //                   1.2f),                        //? Brightness
    };
    for (PointLight* pointLight : pointLights) lights.push_back(pointLight);

    spotLights = {
       //    new SpotLight("White Spotlight",
       //                  false,
       //                  glm::vec3(0.0f, 1.0f, 0.0f),   //? Position
       //                  glm::vec3(0.0f, -1.0f, 0.0f),  //? Direction
       //                  12.5f,                        //? Cone Size
       //                  glm::vec3(1.0f, 1.0f, 1.0f),     //? Color
       //                  0.1f,                         //? Ambient Strength
       //                  glm::vec3(1.0f, 1.0f, 1.0f),     //? Ambient Color
       //                  0.5f,                         //? Specular Strength
       //                  16,                           //? Specular Phong
       //                  1.0f),                        //? Brightness
    };
    spotLights.push_back(player->getSpotLight());
    for (SpotLight* spotLight : spotLights) lights.push_back(spotLight);

    //* - - - - - END OF LIGHTS - - - - -

    //* - - - - - MODEL LOADING - - - - -
    //| TODO: Add the remaining Subs please. Feel free to add other models too if you want.
    model3ds = {
       player->getModel(),
       new Model3D("Enemy Submarine 1",             //? Model Name
                   "Assets/MeepballSub.obj",        //? Model Path
                   "Assets/Enemies/Enemy_1.png",    //? Texture Path
                   "",                              //? Normal Path
                   glm::vec3(-1.0f, 0.0f, -2.0f),   //? Position
                   glm::mat4(1.0f),                 //? Position Matrix
                   glm::vec3(1.0f),                 //? Scale
                   glm::vec3(0.0f, 180.0f, 0.0f)),  //? Orientation
       new Model3D("Enemy Submarine 2",             //? Model Name
                   "Assets/MeepballSub.obj",        //? Model Path
                   "Assets/Enemies/Enemy_2.png",    //? Texture Path
                   "",                              //? Normal Path
                   glm::vec3(1.0f, 0.0f, -2.0f),    //? Position
                   glm::mat4(1.0f),                 //? Position Matrix
                   glm::vec3(1.0f),                 //? Scale
                   glm::vec3(0.0f, 180.0f, 0.0f)),  //? Orientation
        new Model3D("Enemy Submarine 3",             //? Model Name
                   "Assets/MeepballSub.obj",        //? Model Path
                   "Assets/Enemies/Enemy_3.png",    //? Texture Path
                   "",                              //? Normal Path
                   glm::vec3(2.0f, 0.0f, -2.0f),    //? Position
                   glm::mat4(1.0f),                 //? Position Matrix
                   glm::vec3(1.0f),                 //? Scale
                   glm::vec3(0.0f, 180.0f, 0.0f)),  //? Orientation
        new Model3D("Enemy Submarine 4",             //? Model Name
                   "Assets/MeepballSub.obj",        //? Model Path
                   "Assets/Enemies/Enemy_4.png",    //? Texture Path
                   "",                              //? Normal Path
                   glm::vec3(-2.0f, 0.0f, -2.0f),    //? Position
                   glm::mat4(1.0f),                 //? Position Matrix
                   glm::vec3(1.0f),                 //? Scale
                   glm::vec3(0.0f, 180.0f, 0.0f)),  //? Orientation
        new Model3D("Enemy Submarine 5",             //? Model Name
                   "Assets/MeepballSub.obj",        //? Model Path
                   "Assets/Enemies/Enemy_5.png",    //? Texture Path
                   "",                              //? Normal Path
                   glm::vec3(3.0f, 0.0f, -2.0f),    //? Position
                   glm::mat4(1.0f),                 //? Position Matrix
                   glm::vec3(1.0f),                 //? Scale
                   glm::vec3(0.0f, 180.0f, 0.0f)),  //? Orientation
        new Model3D("Enemy Submarine 6",             //? Model Name
                   "Assets/MeepballSub.obj",        //? Model Path
                   "Assets/Enemies/Enemy_6.png",    //? Texture Path
                   "",                              //? Normal Path
                   glm::vec3(-3.0f, 0.0f, -2.0f),    //? Position
                   glm::mat4(1.0f),                 //? Position Matrix
                   glm::vec3(1.0f),                 //? Scale
                   glm::vec3(0.0f, 180.0f, 0.0f)),  //? Orientation


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
        //| TODO: Add here the stuff you need to happen every frame, like moving some of the enemy subs
        player->movePlayer();


        glfwSetCursorEnterCallback(window, cursor_enter_callback);

        if (currentCamera == perspectiveCamera){perspectiveCamera->setPosition(direction + activeModel->getPosition());}
        else if (currentCamera == firstPOVCamera){firstPOVCamera->setPosition(glm::vec3(activeModel->getPosition().x,
                                                                              1.0f + activeModel->getPosition().y,
                                                                              0.5f + activeModel->getPosition().z));}
        else if (currentCamera == orthographicCamera){orthographicCamera->setPosition(glm::vec3(x_mod + activeModel->getPosition().x,
                                                                                               10.0f + activeModel->getPosition().y,
                                                                                               z_mod + 5.0f + activeModel->getPosition().z));}


        player->turnPlayer();
        player->resetInputs();
        //player->displayDepth();
        player->haveSpotlightFollowModel();
        //* - - - - - END OF UPDATE - - - - -

        //* - - - - - SKYBOX SHADER SWITCH - - - - -
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxShaderProgram);
        //* - - - - - END OF SKYBOX SHADER SWITCH - - - - -

        //* - - - - - SKYBOX RENDERING - - - - -
        glm::mat4 skyboxView           = glm::mat4(1.0f);
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

            glActiveTexture(GL_TEXTURE0);
            GLuint modelTextureAddress =
                glGetUniformLocation(lightingShaderProgram, "modelTexture");
            glBindTexture(GL_TEXTURE_2D, model->getTexture().getTexture());

            glActiveTexture(GL_TEXTURE1);
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
    glDeleteShader(lightingVertexShader.getShader());
    glDeleteShader(lightingFragmentShader.getShader());
    glDeleteShader(skyboxVertexShader.getShader());
    glDeleteShader(skyboxFragmentShader.getShader());
    //* - - - - - END OF CLEAN UP - - - - -
    glfwTerminate();
    return 0;
}