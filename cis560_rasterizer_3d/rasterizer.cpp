#include "rasterizer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Rasterizer::Rasterizer(const std::vector<Polygon>& polygons)
    : m_polygons(polygons), m_camera()
{}

//base on 3 vertes create bounbox to reduce calculate
std::array<float, 4> Rasterizer:: boundBox(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2){
    std::array<float,4> boundBox;
    boundBox[0] = glm::min(glm::min(v0.x, v1.x), v2.x); //box' min x
    boundBox[1] = glm::max(glm::max(v0.x, v1.x), v2.x); //box's max x
    boundBox[2] = glm::min(glm::min(v0.y, v1.y), v2.y); //box's min y
    boundBox[3] = glm::max(glm::max(v0.y, v1.y), v2.y); //box's max y
    return boundBox;
}

//barycentry interpolated
glm::vec3 Rasterizer::computeBarycentricCoordinates(glm::vec2 p, glm::vec2 v0, glm::vec2 v1, glm::vec2 v2){
    float area = (v1.x - v0.x)*(v2.y - v0.y) - (v2.x - v0.x)*(v1.y - v0.y);
    float s1 = ((v1.x - p.x)*(v2.y-p.y) - (v2.x - v0.x)*(v1.y -p.y))/area;
    float s2 = ((v2.x - p.x)*(v0.y-p.y) - (v0.x - p.x)*(v2.y - p.y))/area;
    float s3 = 1.0f - s1 -s2;

    return glm::vec3(s1, s2, s3);
}

//perspective interpolated, ok, not clear why, should check again
// big confuse !!!!!
// glm::vec3 perspectiveCorrectBarcentric(const glm::vec3& barycentric, const glm::vec3& oneOverz ){
//     glm::vec3 correctdBarycentric = glm::vec3(barycentric.x * oneOverz.x, barycentric.y * oneOverz.y, barycentric*oneOverz.z);
//     float sum = correctdBarycentric.x + correctdBarycentric.y + correctdBarycentric.z;

//     if(sum == 0.f){
//         return glm::vec3(-1.f, -1.f, -1.f);
//     }

//     correctdBarycentric /= sum;
//     return correctdBarycentric;
// }


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

    //init z buffer
    //set buffer size, w*h and set per pixel as the max z,
    //the farest distance from camera
    std::vector<float> zBuffer( width*height, std::numeric_limits<float>::max());


    //get camera output functions, projection and view
    glm::mat4 viewMatrix = m_camera.view();
    glm::mat4 projectionMatrix = m_camera.projection();

    for(Polygon& polygons: m_polygons){
        for(Triangle& tri: polygons.m_tris){
            std::cout << "get mesh"<< std::endl;

            //get world space vertex
            Vertex& worldV0 = polygons.m_verts[tri.m_indices[0]];
            Vertex& worldV1 = polygons.m_verts[tri.m_indices[1]];
            Vertex& worldV2 = polygons.m_verts[tri.m_indices[2]];

            //world space to clip space // order is important !!!
            glm::vec4 clipV0 = projectionMatrix * viewMatrix * worldV0.m_pos;
            glm::vec4 clipV1 = projectionMatrix * viewMatrix * worldV1.m_pos;
            glm::vec4 clipV2 = projectionMatrix * viewMatrix * worldV2.m_pos;

            //clip space to screen space
            glm::vec4 screenV0 = clipV0 / clipV0.w;
            glm::vec4 screenV1 = clipV1 / clipV1.w;
            glm::vec4 screenV2 = clipV2 / clipV2.w;


            std::cout << "Screen Space Vertices:" << std::endl;
            std::cout << glm::to_string(screenV0) << std::endl;
            std::cout << glm::to_string(screenV1) << std::endl;
            std::cout << glm::to_string(screenV2) << std::endl;

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
            // int x_min = std::min(static_cast<int>(boundingBox[0]),0);
            // int x_max = std::max(static_cast<int>(boundingBox[1]), result.width()-1);
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
                        std::cout << "get intersection "<< std::endl;
                        //not clear why use add 0.5f
                        glm::vec2 pixel = glm::vec2(x + 0.5f, y + 0.5f);

                        glm::vec3 baryCentry = computeBarycentricCoordinates(pixel, pixelV0, pixelV1, pixelV2);


                        //queation about perspective correct

                        float depth = baryCentry.x* screenV0.z + baryCentry.y* screenV1.z + baryCentry.z* screenV2.z;

                        int index = y * width + x;
                        //update depth, if pixel depth smaller, it means that pixel closed camera than perivous
                        //so we have to replace color as new depth's color

                        if(depth < zBuffer[index]){
                            zBuffer[index] = depth;

                            //normal interpolated
                            //glm::vec3 normal = baryCentry.x * worldV0.m_normal + baryCentry.y * worldV1.m_normal + baryCentry.z * worldV2.m_normal;

                            //uv interpolated
                            glm::vec2 uv = baryCentry.x * worldV0.m_uv + baryCentry.y * worldV1.m_uv + baryCentry.z * worldV2.m_uv;
                            glm::vec3 color = GetImageColor(uv, polygons.mp_texture);
                            color = glm::clamp(color, 0.0f, 1.0f);

                            result.setPixelColor(x, y, qRgb(color[0], color[1], color[2]));
                        }

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
