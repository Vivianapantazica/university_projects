#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object3D
{
    Mesh* CreateRaceTrack(
        const std::string& name,
        glm::vec3 center,
        std::vector<glm::vec3> initialPoints,
        glm::vec3 color,
        bool fill);
    Mesh* CreateMiddleLine(
        const std::string& name,
        glm::vec3 center,
        std::vector<glm::vec3> initialPoints,
        glm::vec3 color,
        bool fill);
    std::vector<glm::vec3> generateInnerAndOuterPoints(glm::vec3 x1, glm::vec3 x2, float t);
    std::vector<glm::vec3> generateInnerAndOuterPointsForMiddleLine(glm::vec3 x1, glm::vec3 x2, float t);
    glm::vec3 generateIntermediatePoints(glm::vec3 x1, glm::vec3 x2, float j);
}
