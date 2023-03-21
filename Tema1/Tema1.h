#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

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
        void CreateDuck(float startX, float startY, float deltaTimeSeconds, float speed, glm::mat3 modelMatrix);
        glm::mat3 Tema1::RotateFirst(float angularRand);
        void Tema1::FlyAwayOrKilled(float deltaTimeSeconds, float angle, float speed);
        float Tema1::Area(float x1, float y1, float x2, float y2,
            float x3, float y3);
        bool Tema1::Check(float x1, float y1, float x2, float y2, float x3,
            float y3, float x4, float y4, float x, float y);
        void Tema1::GetHiddenBoxVertexes();
        void Tema1::ResetDuck();
        void Tema1::CalculateCollisionAngles();
        void Tema1::DisplayWinStar(float deltaTimeSeconds);
        void Tema1::DisplayGameOver(float deltaTimeSeconds);
        void Tema1::PrepareScene();

    protected:
        glm::mat3 modelMatrix;
        glm::ivec2 resolution;
        float translateX, translateY, angularStep, angularRand, startX, startY, scaleX, scaleY,
            height, width, counter, startTime, speed, x1, y1, x2, y2, x3, y3, x4, y4, cx, cy;
        int noOfDucks, noOfBullets, noOfLives, duckIsEscaped, duckIsAlive, displayDuck;
        int countKills;
        
        const float LOW_ANGLE = (M_PI / 10);
        const float HIGH_ANGLE = ((5 * M_PI) / 12);
        const float DIFF_ANGLE = ((7 * M_PI) / 20);
        const glm::vec3 grassGreen = glm::vec3(0.5f, 0.8f, 0.2f);
        const glm::vec3 screenColor = glm::vec3(0.3f, 0, 0.8f);
        const glm::vec3 brown = glm::vec3(0.6f, 0.3f, 0.2f);
        const glm::vec3 golden = glm::vec3(1, 0.75f, 0);
        const glm::vec3 green = glm::vec3(0, 0.2f, 0);
        const glm::vec3 red = glm::vec3(1, 0.2f, 0);
    };
}   // namespace m1
