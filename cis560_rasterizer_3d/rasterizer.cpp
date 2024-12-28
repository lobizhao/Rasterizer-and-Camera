#include "rasterizer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Rasterizer::Rasterizer(const std::vector<Polygon>& polygons)
    : m_polygons(polygons), m_camera()
{}

std::array<float, 4> Rasterizer:: boundBox(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2){
    std::array<float,4> boundBox;
    boundBox[0] = glm::min(glm::min(v0.x, v1.x), v2.x); //box' min x
    boundBox[1] = glm::max(glm::max(v0.x, v1.x), v2.x); //box's max x
    boundBox[2] = glm::min(glm::min(v0.y, v1.y), v2.y); //box's min y
    boundBox[3] = glm::max(glm::max(v0.y, v1.y), v2.y); //box's max y
    return boundBox;
}

glm::vec3 Rasterizer::computeBarycentricCoordinates(glm::vec2 p, glm::vec2 v0, glm::vec2 v1, glm::vec2 v2){
    float area = (v1.x - v0.x)*(v2.y - v0.y) - (v2.x - v0.x)*(v1.y - v0.y);
    float s1 = ((v1.x - p.x)*(v2.y-p.y) - (v2.x - v0.x)*(v1.y -p.y))/area;
    float s2 = ((v2.x - p.x)*(v0.y-p.y) - (v0.x - p.x)*(v2.y - p.y))/area;
    float s3 = 1.0f - s1 -s2;

    return glm::vec3(s1, s2, s3);
}


QImage Rasterizer::RenderScene()
{
    QImage result(512, 512, QImage::Format_RGB32);
    // Fill the image with black pixels.
    // Note that qRgb creates a QColor,
    // and takes in values [0, 255] rather than [0, 1].
    result.fill(qRgb(0.f, 0.f, 0.f));


    //get pixel size
    int width = result.width();
    int height = result.height();

    //camera output functions
    glm::mat4 viewMatrix = m_camera.view();
    glm::mat4 projectionMatrix = m_camera.projection();

    for(Polygon& polygons: m_polygons){
        for(Triangle& tri: polygons.m_tris){
            //get world space vertex
            Vertex& worldV0 = polygons.m_verts[tri.m_indices[0]];
            Vertex& worldV1 = polygons.m_verts[tri.m_indices[1]];
            Vertex& worldV2 = polygons.m_verts[tri.m_indices[2]];

            //world space to clip space
            glm::vec4 clipV0 = worldV0.m_pos * viewMatrix * projectionMatrix;
            glm::vec4 clipV1 = worldV1.m_pos * viewMatrix * projectionMatrix;
            glm::vec4 clipV2 = worldV2.m_pos * viewMatrix * projectionMatrix;

            //clip space to screen space
            glm::vec4 screenV0 = clipV0 / clipV0.w;
            glm::vec4 screenV1 = clipV1 / clipV1.w;
            glm::vec4 screenV2 = clipV2 / clipV2.w;

            //screen space to pixel space
            glm::vec2 pixelV0 = glm::vec2( ((screenV0.x + 1)/2)*width,
                                          ((screenV0.y +1)/2)*height);
            glm::vec2 pixelV1 = glm::vec2( ((screenV1.x + 1)/2)*width,
                                          ((screenV1.y +1)/2)*height);
            glm::vec2 pixelV2 = glm::vec2( ((screenV2.x + 1)/2)*width,
                                          ((screenV2.y +1)/2)*height);

            //calculate bounding box
            std::array<float,4> boundingBox = boundBox(pixelV0, pixelV1, pixelV2);

            //bounding box with pixel edge
            int x_min = std::min(static_cast<int>(boundingBox[0]),0);
            int x_max = std::max(static_cast<int>(boundingBox[1]), result.width()-1);
            int y_min = std::min(static_cast<int>(boundingBox[2]),0);
            int y_max = std::max(static_cast<int>(boundingBox[3]), result.height()-1);

            //calculate intersection x
            for(int y = y_min; y < y_max; y++){
                std::vector<float> intersections;

                //segemtn input a edge, edge: two vertex
                Segment edge1({pixelV0.x, pixelV0.y}, {pixelV1.x, pixelV1.y});
                Segment edge2({pixelV1.x, pixelV1.y}, {pixelV2.x, pixelV2.y});
                Segment edge3({pixelV2.x, pixelV2.y}, {pixelV0.x, pixelV0.y});

                float x;
                if(edge1.isIntersection(&x, y)){
                    intersections.push_back(x);
                }

                if(edge2.isIntersection(&x, y)){
                    intersections.push_back(x);
                }

                if(edge3.isIntersection(&x, y)){
                    intersections.push_back(x);
                }

                //there are two intersection point
                if(intersections.size() == 2){
                    std::sort(intersections.begin(), intersections.end());
                    int x_start = static_cast<int>(std::ceil(intersections[0]));
                    int x_end = static_cast<int>(std::floor(intersections[1]));

                    for(int x = x_start; x < x_end; x++){
                        glm::vec2 pixel = glm::vec2(x, y);

                        glm::vec3 baryCentry = computeBarycentricCoordinates(pixel, pixelV0, pixelV1, pixelV2);

                        float depth = baryCentry.x* screenV0.z + baryCentry.x* screenV1.z + baryCentry.x* screenV2.z;

                    }




                }





            }








        }


    }


    return result;
}




void Rasterizer::ClearScene()
{
    m_polygons.clear();
}
