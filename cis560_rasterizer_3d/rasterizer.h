#pragma once
#include <polygon.h>
#include <QImage>
#include <segment.h>
#include <camera.h>

class Rasterizer
{
private:
    //This is the set of Polygons loaded from a JSON scene file
    std::vector<Polygon> m_polygons;

    // scalingFactor
    int scalingAA;


public:
    Rasterizer(const std::vector<Polygon>& polygons);
    //camera
    Camera m_camera;

    //bounding box - in iput triangle's 3 points
    std::array<float, 4>boundBox(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2);
    glm::vec3 computeBarycentricCoordinates(glm::vec2 p, glm::vec2 v0, glm::vec2 v1, glm::vec2 v2);
    glm::vec3 perspectiveCorrectBarcentric(const glm::vec3& barycentric, const glm::vec3& oneOverz);

    QImage RenderScene();
    void ClearScene();
    void setScaling(int scale);
};
