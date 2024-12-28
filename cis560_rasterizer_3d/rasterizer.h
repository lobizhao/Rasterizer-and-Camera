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
    //I think this is create a camera in scene
    Camera m_camera;

public:
    Rasterizer(const std::vector<Polygon>& polygons);

    //bounding box - in iput triangle's 3 points
    std::array<float, 4>boundBox(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2);
    glm::vec3 computeBarycentricCoordinates(glm::vec2 p, glm::vec2 v0, glm::vec2 v1, glm::vec2 v2);

    QImage RenderScene();
    void ClearScene();
};
