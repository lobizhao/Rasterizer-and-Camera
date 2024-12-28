#include "camera.h"

Camera::Camera():forward(glm::vec4(0.0f,0.0f,-1.0f,0.0f)),
                right(glm::vec4(1.0f,0.0f,0.0f,0.0f)),
                up(glm::vec4(0.0f,1.0f,0.0f,0.0f)),
                worldPos(glm::vec4(0.0f,0.0f,10.0f,1.0f)),
                FOV(45.0f),
                nearClip(0.01f), farClip(100.0f),
                ratio(1.0f){}


glm::mat4 Camera::view(){

    glm::mat4 orientation = glm::mat4(1.0f);
    glm::mat4 translateion = glm::mat4(1.0f);

    orientation[0][0] = right.x;
    orientation[0][1] = right.y;
    orientation[0][2] = right.z;

    orientation[1][0] = up.x;
    orientation[1][1] = up.y;
    orientation[1][2] = up.z;

    orientation[2][0] = forward.x;
    orientation[2][1] = forward.y;
    orientation[2][2] = forward.z;

    translateion[0][3] = -worldPos.x;
    translateion[1][3] = -worldPos.y;
    translateion[2][3] = -worldPos.z;

    glm::mat4 view = orientation*translateion;

    return view;
}

glm::mat4 Camera::projection(){
    glm::mat4 projection = glm::mat4(0.0f);
    projection[0][0] = 1/glm::tan(ratio*glm::radians(FOV/2.0f));
    projection[1][1] = 1/glm::tan(glm::radians(FOV/2.0f));
    projection[2][2] = farClip/(farClip - nearClip);
    projection[2][3] = -farClip*nearClip / (farClip - nearClip);
    projection[3][3] = 0;
    projection[3][2] = 1;
}

void Camera::translateForward(float z){
    worldPos += forward * z;
}
void Camera::translateRight(float x){
    worldPos += right * x;
}
void Camera::translateUp(float y){
    worldPos += up * y;
}

void Camera::rotateLocalRight(float angle){
    float radians = glm::radians(angle);
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), radians, glm::vec3(right));
    forward = glm::vec4(glm::mat3(rotation)* glm::vec3(forward), 0.0f);
    up = glm::vec4(glm::mat3(rotation)*glm::vec3(up),0.0f);
}
void Camera::rotateLocalUp(float angle){
    float radians = glm::radians(angle);
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), radians, glm::vec3(up));
    forward = glm::vec4(glm::mat3(rotation)* glm::vec3(forward), 0.0f);
    up = glm::vec4(glm::mat3(rotation)*glm::vec3(up),0.0f);

}
void Camera::rotateLocalClock(float angle){
    float radians = glm::radians(angle);
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), radians, glm::vec3(forward));
    forward = glm::vec4(glm::mat3(rotation)* glm::vec3(forward), 0.0f);
    up = glm::vec4(glm::mat3(rotation)*glm::vec3(up),0.0f);
}


