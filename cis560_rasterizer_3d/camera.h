#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera();

private:
    // internal variables
    glm::vec4 forward; //{0,0,-1,0}
    glm::vec4 right;  //{1,0,0,0}
    glm::vec4 up;  //{0,1,0,0}
    glm::vec4 worldPos; //{0,0,10,1}

    float FOV;  //45d
    float nearClip; //0.01
    float farClip;  // 100.0
    float ratio; //screen width/height 512/512


public:
    // output
    glm::mat4 view();
    glm::mat4 projection();

    // input
    void translateForward(float z);
    void translateRight(float x);
    void translateUp(float y);

    void rotateLocalRight(float angle);
    void rotateLocalUp(float angle);
    void rotateLocalClock(float angle);
};

#endif // CAMERA_H
