#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"
#include "lab_m1/Tema2/object3D.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, 
            const glm::vec3& color, const glm::vec3& carPos, implemented::Camera2* camera);
        float intersect(glm::vec3 sphere, glm::vec3 other, float radius);
        bool isInsideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
        float getTriangleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c);
        bool isInsideRaceTrack(glm::vec3 p);
        void RenderScene(float deltaTimeSeconds, implemented::Camera2* camera);
        void GenerateTreeLocations();
        void GenerateCarTraces(std::vector<glm::vec3> initialPoints1);
        void GenerateRaceTrackLimits(std::vector<glm::vec3> initialPoints2);
        void CameraSetUp();

    protected:
        implemented::Camera2* camera;
        implemented::Camera2* miniCamera;

        GLfloat right;
        GLfloat left;
        GLfloat bottom;
        GLfloat top;
        GLfloat fov;

        ViewportArea miniViewportArea;

        glm::mat4 projectionMatrix;

        std::vector<glm::vec3> treePositionPoints = {};
        std::vector<glm::vec3> raceTrackLimits = {};
        std::vector<glm::vec3> carOnePoints = {};
        std::vector<glm::vec3> carTwoPoints = {};
        std::vector<glm::vec3> initialPoints = {};

        glm::vec3 startPoint = {};
        glm::vec3 secondPoint = {};

        float j = 0, x = 0;
        float rotationAngle = 0;
        float rotationAngle1 = 0;
        float rotationAngle2 = 0;
        float width, height;

        bool collisionDetectedWithCarOne = false;
        bool collisionDetectedWithCarTwo = false;
    };
}   // namespace m1
