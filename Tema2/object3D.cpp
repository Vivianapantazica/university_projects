#include "lab_m1/Tema2/object3D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* object3D::CreateRaceTrack(
    const std::string& name,
    glm::vec3 center,
    std::vector<glm::vec3> initialPoints,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices = {};

    std::vector<glm::vec3> allPoints = {};

    std::vector<glm::vec3> inPoints = {};

    std::vector<glm::vec3> extPoints = {};

    initialPoints.push_back(initialPoints[0]);


    for (int i = 0; i < initialPoints.size() - 1; i++) {
        for (float j = 0; j < 1; j += 0.01) {
            allPoints.push_back(generateIntermediatePoints(initialPoints[i], initialPoints[i + 1], j));
        }
    }
    allPoints.push_back(initialPoints[initialPoints.size() - 1]);

    int i = 0;
    for (i; i < allPoints.size() - 1; i++) {
        std::vector<glm::vec3> morePoints = generateInnerAndOuterPoints(allPoints[i], allPoints[i + 1], 1.5f);
        inPoints.push_back(morePoints[0]);
        extPoints.push_back(morePoints[1]);
    }
    std::vector<glm::vec3> morePoints = generateInnerAndOuterPoints(allPoints[i], allPoints[0], 1.5f);
    inPoints.push_back(morePoints[0]);
    extPoints.push_back(morePoints[1]);

    for (int pointIndex = 0; pointIndex < allPoints.size() - 1; pointIndex++) {
        vertices.push_back(VertexFormat((center + inPoints[pointIndex]), color));
        vertices.push_back(VertexFormat((center + extPoints[pointIndex]), color));
    }

    Mesh* raceTrack = new Mesh(name);

    std::vector<unsigned int> indices = {};

    int teta = 0;
    for (teta = 0; teta < vertices.size(); teta++) {
        indices.push_back(teta);
        indices.push_back(teta + 1);
        indices.push_back(teta + 2);
    }
     
    if (!fill) {
        raceTrack->SetDrawMode(GL_LINE_LOOP);
    }
    
    raceTrack->InitFromData(vertices, indices);
    return raceTrack;
}

Mesh* object3D::CreateMiddleLine(
    const std::string& name,
    glm::vec3 center,
    std::vector<glm::vec3> initialPoints,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices = {};

    std::vector<glm::vec3> allPoints = {};

    std::vector<glm::vec3> inPoints = {};

    std::vector<glm::vec3> extPoints = {};

    initialPoints.push_back(initialPoints[0]);


    for (int i = 0; i < initialPoints.size() - 1; i++) {
        for (float j = 0; j < 1; j += 0.001) {
            allPoints.push_back(generateIntermediatePoints(initialPoints[i], initialPoints[i + 1], j));
        }
    }
    allPoints.push_back(initialPoints[initialPoints.size() - 1]);

    int i = 0;
    for (i; i < allPoints.size() - 1; i++) {
        std::vector<glm::vec3> morePoints = generateInnerAndOuterPointsForMiddleLine(allPoints[i], allPoints[i + 1], 0.8f);
        inPoints.push_back(morePoints[0]);
        extPoints.push_back(morePoints[1]);
    }
    std::vector<glm::vec3> morePoints = generateInnerAndOuterPointsForMiddleLine(allPoints[i], allPoints[0], 0.8f);
    inPoints.push_back(morePoints[0]);
    extPoints.push_back(morePoints[1]);

    for (int pointIndex = 0; pointIndex < allPoints.size() - 1; pointIndex++) {
        vertices.push_back(VertexFormat((center + inPoints[pointIndex]), color));
        vertices.push_back(VertexFormat((center + extPoints[pointIndex]), color));
    }

    Mesh* middleLine = new Mesh(name);

    std::vector<unsigned int> indices = {};

    int teta = 0;
    for (teta = 0; teta < vertices.size(); teta ++) {
        indices.push_back(teta);
        indices.push_back(teta + 1);
        indices.push_back(teta + 2);
    }

    if (!fill) {
        middleLine->SetDrawMode(GL_LINE_LOOP);
    }

    middleLine->InitFromData(vertices, indices);
    return middleLine;
}

std::vector<glm::vec3> object3D::generateInnerAndOuterPoints(glm::vec3 x1, glm::vec3 x2, float t) {
    std::vector<glm::vec3> morePoints = {};
    glm::vec3 D = glm::normalize(x2 - x1);
    glm::vec3 P = glm::cross(D, glm::vec3(0, 1, 0));
    glm::vec3 R = x1 + (t - 0.25f) * P;
    glm::vec3 A = x1 - (t - 0.75f) * P;
    // R exterior si A interior
    morePoints.push_back(R);
    morePoints.push_back(A);
    return morePoints;
}

std::vector<glm::vec3> object3D::generateInnerAndOuterPointsForMiddleLine(glm::vec3 x1, glm::vec3 x2, float t) {
    std::vector<glm::vec3> morePoints = {};
    glm::vec3 D = glm::normalize(x2 - x1);
    glm::vec3 P = glm::cross(D, glm::vec3(0, 1, 0));
    glm::vec3 R = x1 + (t - 0.79f) * P;
    glm::vec3 A = x1 - (t - 0.79f) * P;
    // R exterior si A interior
    morePoints.push_back(R);
    morePoints.push_back(A);
    return morePoints;
}

glm::vec3 object3D::generateIntermediatePoints(glm::vec3 x1, glm::vec3 x2, float j) {
   return glm::vec3(x1[0] + (x2[0] - x1[0]) * j, 0,
        x1[2] + (x2[2] - x1[2]) * j);
}