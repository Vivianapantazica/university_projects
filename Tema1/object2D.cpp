#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object2D::CreateRectangle1(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 x,
    glm::vec3 y,
    glm::vec3 z,
    glm::vec3 color,
    bool fill)

{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(x, color),
        VertexFormat(y , color),
        VertexFormat(z, color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2};

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(2);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateTriangleWithShader(
    const std::string& name,
    glm::vec3 x,
    glm::vec3 y,
    glm::vec3 z,
    glm::vec3 color,
    bool fill)

{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(x, color),
        VertexFormat(y , glm::vec3(0, 0, 0)),
        VertexFormat(z, color),
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(2);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}


Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices = {};

    for (int teta = 0; teta <= 360; teta++) {
         vertices.push_back(VertexFormat(glm::vec3(center[0] + cos(teta) * radius, 
             center[1] + sin(teta) * radius, 0), color));
    }
        
    Mesh* circle = new Mesh(name);

    std::vector<unsigned int> indices = {};

    for (int teta = 0; teta < 360; teta++) {
        indices.push_back(0);
        indices.push_back(teta + 1);
        indices.push_back(teta);
    }

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        for (int teta = 0; teta < 360; teta++) {
            indices.push_back(0);
            indices.push_back(teta);
            indices.push_back(teta + 1);
        }
    }

    circle->InitFromData(vertices, indices);
    return circle;
}