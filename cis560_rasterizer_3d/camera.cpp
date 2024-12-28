#include "camera.h"

Camera::Camera():forward(glm::vec4(0.0f,0.0f,-1.0f,0.0f)),
                right(glm::vec4(1.0f,0.0f,0.0f,0.0f)),
                up(glm::vec4(0.0f,1.0f,0.0f,0.0f)),
                worldPos(glm::vec4(0.0f,0.0f,10.0f,1.0f)),
                FOV(45.0f),
                nearClip(0.01f), farClip(100.0f),
                ratio(1.0f){}


//glm column major order!!
glm::mat4 Camera::view(){

    glm::mat4 orientation = glm::mat4(1.0f);
    glm::mat4 translateion = glm::mat4(1.0f);

    orientation[0] = glm::vec4(right.x, up.x, -forward.x, 0.0f);
    orientation[1] = glm::vec4(right.y, up.y, -forward.y, 0.0f);
    orientation[2] = glm::vec4(right.z, up.z, -forward.z, 0.0f);
    translateion[3] = glm::vec4(-worldPos.x, -worldPos.y, -worldPos.z, 1.0f);

    glm::mat4 view = orientation * translateion;

    return view;
}

glm::mat4 Camera::projection(){
    glm::mat4 projection = glm::mat4(0.0f);
    float tanHalfFOV = glm::tan(glm::radians(FOV/2.0F));

    projection[0][0] = 1.0f / (ratio * tanHalfFOV);
    projection[1][1] = 1.0f / tanHalfFOV;
    projection[2][2] = -(farClip + nearClip) / (farClip - nearClip);
    projection[2][3] = -1.0f;
    projection[3][2] = -(2.0f *farClip *nearClip)/(farClip - nearClip);

    return projection;
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
    //up = glm::vec4(glm::mat3(rotation)*glm::vec3(up),0.0f);
    up = glm::vec4(glm::normalize(glm::cross(glm::vec3(right), glm::vec3(forward))), 0.0f);
}
void Camera::rotateLocalUp(float angle){
    float radians = glm::radians(angle);
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), radians, glm::vec3(up));
    forward = glm::vec4(glm::mat3(rotation)* glm::vec3(forward), 0.0f);
    right = glm::vec4(glm::normalize(glm::cross(glm::vec3(forward), glm::vec3(up))), 0.0f);


}
void Camera::rotateLocalClock(float angle){
    float radians = glm::radians(angle);
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), radians, glm::vec3(forward));
    forward = glm::vec4(glm::mat3(rotation)* glm::vec3(forward), 0.0f);
    //up = glm::vec4(glm::mat3(rotation)*glm::vec3(up),0.0f);
    up = glm::vec4(glm::normalize(glm::cross(glm::vec3(right), glm::vec3(forward))), 0.0f);
}


