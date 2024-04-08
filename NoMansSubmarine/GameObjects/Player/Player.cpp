#include "Player.hpp"

using namespace models;
using namespace std;

//* ╔═══════════════════════════════╗
//* ║ Constructors & Deconstructors ║
//* ╚═══════════════════════════════╝
Player::Player()
    : model(new Model3D("Player Submarine",           //? Model Name
                        "Assets/MeepballSub.obj",     //? Model Path
                        "Assets/Submarine.png",       //? Texture Path
                        "",                           //? Normal Path
                        glm::vec3(0.0f, 0.0f, 0.0f),  //? Position
                        glm::mat4(1.0f),              //? Position Matrix
                        glm::vec3(1.0f),              //? Scale
                        glm::vec3(0.0f, 0.0f, 0.0f))  //? Orientation
            ),
      spotLight(new SpotLight("Player Spotlight",
                              true,
                              glm::vec3(0.0f, 1.0f, 0.0f),     //? Position
                              glm::vec3(0.0f, 0.0f, -1.0f),    //? Direction
                              12.5f,                           //? Cone Size
                              glm::vec3(0.99f, 0.97f, 0.91f),  //? Color
                              0.1f,                            //? Ambient Strength
                              glm::vec3(0.99f, 0.97f, 0.91f),  //? Ambient Color
                              0.5f,                            //? Specular Strength
                              16,                              //? Specular Phong
                              2.0f)                            //? Brightness
                ),
      firstPersonView(new PerspectiveCamera("First Person View",
                                            glm::vec3(0.0f, 0.0f, 0.0f),
                                            glm::vec3(0.0f, 0.0f, -1.0f),
                                            60.0f,
                                            1000.0f)),
      thirdPersonView(new PerspectiveCamera("Third Person View",
                                            glm::vec3(0.0f, 5.0f, 5.0f),
                                            glm::vec3(0.0f, 0.0f, -1.0f),
                                            60.0f,
                                            100.0f)),
      turnInput(0.0f),
      yInput(0.0f),
      zInput(0.0f),
      lightIntensity(0),
      activeCamera(this->thirdPersonView) {}

//* ╔═════════╗
//* ║ Methods ║
//* ╚═════════╝
void Player::playerKeyboardInput(int key, int action) {
    //* Movement: Forward & Backward
    if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
        if (this->zInput < 1.0f) this->zInput += 0.1f;
    }
    if (key == GLFW_KEY_S && action == GLFW_REPEAT) {
        if (this->zInput > -1.0f) this->zInput -= 0.1f;
    }
    //* Movement: Turn Left & Turn Right
    if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
        if (this->turnInput < 1.0f) this->turnInput += 0.1f;
    }
    if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
        if (this->turnInput > -1.0f) this->turnInput -= 0.1f;
    }
    //* Movement: Ascend & Turn Descend
    if (key == GLFW_KEY_E && action == GLFW_REPEAT) {
        if (this->yInput < 1.0f) this->yInput += 0.1f;
    }
    if (key == GLFW_KEY_Q && action == GLFW_REPEAT) {
        if (this->yInput > -1.0f) this->yInput -= 0.1f;
    }
    //* Cycle Light Intensity
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        this->cycleLightIntensity();
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        if (this->activeCamera == (Camera*)this->firstPersonView) {
            this->activeCamera = this->thirdPersonView;
            if (DEBUG_MODE) std::cout << "Swapped to Third Person View" << std::endl;
        } else {
            this->activeCamera = this->firstPersonView;
            if (DEBUG_MODE) std::cout << "Swapped to First Person View" << std::endl;
        }
    }
    //* Shoot Torpedo
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    }
}
void Player::playerMouseInput() {}
void Player::movePlayer() {
    if (this->yInput != 0) {
        this->model->setPosition(glm::vec3(this->model->getPosition().x,
                                           this->model->getPosition().y + (yInput * MOVE_SPEED),
                                           this->model->getPosition().z));
        if (this->model->getPosition().y >= 0.0f) {
            this->model->setPosition(
                glm::vec3(this->model->getPosition().x, -MOVE_SPEED, this->model->getPosition().z));
        }
    }

    if (this->zInput != 0) {
        float changeInX =
            -(zInput * MOVE_SPEED) * sin(this->model->getOrientation().y * 3.14159265f / 180.0f);
        float changeInZ =
            -(zInput * MOVE_SPEED) * cos(this->model->getOrientation().y * 3.14159265f / 180.0f);

        this->model->setPosition(glm::vec3(this->model->getPosition().x + changeInX,
                                           this->model->getPosition().y,
                                           this->model->getPosition().z + changeInZ));
    }
}
void Player::turnPlayer() {
    if (this->turnInput != 0) {
        this->model->setOrientation(
            glm::vec3(this->model->getOrientation().x,
                      this->model->getOrientation().y + (turnInput * ROTATE_SPEED),
                      this->model->getOrientation().z));
    }
}
void Player::cycleLightIntensity() {
    if (this->lightIntensity < 2)
        this->lightIntensity++;
    else
        this->lightIntensity = 0;

    switch (this->lightIntensity) {
        case 0:  //? LOW
            this->spotLight->update(true,
                                    {this->spotLight->getColor(),
                                     this->spotLight->getAmbientColor(),
                                     glm::vec3(0.0f),
                                     glm::vec3(0.0f)},
                                    {
                                       0.0f,
                                       0.0f,
                                       0.0f,
                                       LOW_INTENSITY_BRIGHTNESS,
                                       0.0f,
                                    });
            break;
        case 1:  //? MID
            this->spotLight->update(true,
                                    {this->spotLight->getColor(),
                                     this->spotLight->getAmbientColor(),
                                     glm::vec3(0.0f),
                                     glm::vec3(0.0f)},
                                    {
                                       0.0f,
                                       0.0f,
                                       0.0f,
                                       MID_INTENSITY_BRIGHTNESS,
                                       0.0f,
                                    });
            break;
        case 2:  //? HIGH
            this->spotLight->update(true,
                                    {this->spotLight->getColor(),
                                     this->spotLight->getAmbientColor(),
                                     glm::vec3(0.0f),
                                     glm::vec3(0.0f)},
                                    {
                                       0.0f,
                                       0.0f,
                                       0.0f,
                                       HIGH_INTENSITY_BRIGHTNESS,
                                       0.0f,
                                    });
            break;
    }
}
void Player::resetInputs() {
    if (this->turnInput != 0) {
        if (this->turnInput > 0)
            this->turnInput -= 0.01f;
        else
            this->turnInput += 0.01f;
    }
    if (this->yInput != 0) {
        if (this->yInput > 0)
            this->yInput -= 0.01f;
        else
            this->yInput += 0.01f;
    }
    if (this->zInput != 0) {
        if (this->zInput > 0)
            this->zInput -= 0.01f;
        else
            this->zInput += 0.01f;
    }
}
void Player::displayDepth() {
    system("cls");
    if (DEBUG_MODE) std::cout << "Y Input: " << std::setprecision(2) << this->yInput << std::endl;
    if (SHOW_DEPTH)
        std::cout << "SUBMARINE DEPTH: [" << std::setprecision(2)
                  << this->model->getPosition().y * -1 << " M] BELOW SEA LEVEL" << std::endl;
}
void Player::displayCoordinates() {
    if (DEBUG_MODE) std::cout << "Y Input: " << std::setprecision(2) << this->yInput << std::endl;
    if (SHOW_COORDINATES)
        std::cout << "SUBMARINE AT: [X: " << std::setprecision(2) << this->model->getPosition().x
                  << ", Z: " << this->model->getPosition().z << "]" << std::endl;
}
void Player::haveSpotlightFollowModel() {
    this->spotLight->setPosition(glm::vec3(this->model->getPosition().x,
                                           this->model->getPosition().y + 1,
                                           this->model->getPosition().z));
    this->spotLight->setDirection(glm::vec3(-1 * abs(sin(this->model->getOrientation().x)),
                                            -1 * abs(this->model->getOrientation().y),
                                            -1 * abs(cos(this->model->getOrientation().z))));
}
void Player::haveCamerasFollowModel() {
    this->firstPersonView->setPosition(this->model->getPosition());
    this->firstPersonView->setViewCenter(glm::vec3(this->model->getPosition().x,
                                                   this->model->getPosition().y,
                                                   this->model->getPosition().z - 5));
    this->thirdPersonView->setPosition(glm::vec3(this->model->getPosition().x,
                                                 this->model->getPosition().y + 3,
                                                 this->model->getPosition().z + 5));
    this->thirdPersonView->setViewCenter(glm::vec3(this->model->getPosition()));
}
//* ╔═══════════════════╗
//* ║ Getters & Setters ║
//* ╚═══════════════════╝
Model3D* Player::getModel() { return this->model; }
SpotLight* Player::getSpotLight() { return this->spotLight; }
PerspectiveCamera* Player::getFirstPersonView() { return this->firstPersonView; }
PerspectiveCamera* Player::getThirdPersonView() { return this->thirdPersonView; }
Camera* Player::getActiveCamera() { return this->activeCamera; }