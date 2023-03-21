#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateRectangle1(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangle(const std::string& name, glm::vec3 x, glm::vec3 y, glm::vec3 z, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangleWithShader(const std::string& name, glm::vec3 x, glm::vec3 y, glm::vec3 z, glm::vec3 color, bool fill);
}
