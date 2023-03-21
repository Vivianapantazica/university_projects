#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // Window's limits
    height = (float)resolution.y;
    width = (float)resolution.x;

    // Clock counter initialization
    counter = 0;

    // Start time 
    startTime = glfwGetTime();

    // Randomized start positions
    startX = 100 + static_cast <float> (rand())
        / static_cast <float> (RAND_MAX / (width - 100));
    startY = 100 + static_cast <float> (rand())
        / static_cast <float> (RAND_MAX / (height - 500));

    // Number of ducks displayed in scene
    noOfDucks = 0;

    // Duck's center's coordinates
    cx = 55.5f;
    cy = 45;

    // Translation steps initialization
    translateX = 0;
    translateY = 0;

    // Scalar steps initialization
    scaleX = 0;
    scaleY = 0;

    // Starting speed
    speed = 40;

    // Angular step and angular rand initialization
    angularStep = 0;    
    angularRand = LOW_ANGLE + static_cast <float> (rand())
        / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
    if (angularRand == M_PI / 2) {
        LOW_ANGLE + static_cast <float> (rand())
            / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
    }

    // Flag's initialization
    displayDuck = 1;
    duckIsAlive = 1;     
    duckIsEscaped = 0;

    // Counters used to indicate player's attributes 
    noOfBullets = 3;
    noOfLives = 3;
    countKills = 0;

    // MESHES INITIALIZATION
    Mesh* hiddenBox = object2D::CreateRectangle1("hiddenBox", glm::vec3(-60, -45, 0), 111, 90, screenColor, false);
    AddMeshToList(hiddenBox);

    Mesh* leftWing = object2D::CreateTriangleWithShader("leftWing", glm::vec3(-20, 25, 0), glm::vec3(0, 15, 0), glm::vec3(0, 45, 0), brown, true);
    AddMeshToList(leftWing);

    Mesh* rightWing = object2D::CreateTriangleWithShader("rightWing", glm::vec3(-20, -25, 0), glm::vec3(0, -15, 0), glm::vec3(0, -45, 0), brown, true);
    AddMeshToList(rightWing);

    Mesh* body = object2D::CreateTriangle("body", glm::vec3(-60, 0, 0), glm::vec3(0, 20, 0), glm::vec3(0, -20, 0), brown, true);
    AddMeshToList(body);

    Mesh* feathering = object2D::CreateCircle("feathering", glm::vec3(0, 0, 0), 20, green, true);
    AddMeshToList(feathering);

    Mesh* head = object2D::CreateCircle("head", glm::vec3(30, 0, 0), 10, green, true);
    AddMeshToList(head);

    Mesh* beak = object2D::CreateTriangle("beak", glm::vec3(46, 0, 0), glm::vec3(40, 3, 0), glm::vec3(40, -3, 0), golden, true);
    AddMeshToList(beak);

    Mesh* blood = object2D::CreateCircle("blood", glm::vec3(0, 0, 0), 40, red, true);
    AddMeshToList(blood);

    Mesh* bloodDrop = object2D::CreateCircle("bloodDrop", glm::vec3(-40, -70, 0), 10, red, true);
    AddMeshToList(bloodDrop);

    Mesh* bloodDrop1 = object2D::CreateCircle("bloodDrop1", glm::vec3(70, 90, 0), 15, red, true);
    AddMeshToList(bloodDrop1);

    Mesh* bloodDrop2 = object2D::CreateCircle("bloodDrop2", glm::vec3(-80, 0, 0), 15, red, true);
    AddMeshToList(bloodDrop2);


    // MESHES USED FOR SCORE DISPLAY
    Mesh* life = object2D::CreateCircle("life", glm::vec3(0, 0, 0), 15, red, true);
    AddMeshToList(life);

    Mesh* bullet = object2D::CreateRectangle1("bullet", glm::vec3(1100, 660, 0), 10, 15, grassGreen, true);
    AddMeshToList(bullet);

    Mesh* bullet1 = object2D::CreateRectangle1("bullet1", glm::vec3(1150, 660, 0), 10, 15, grassGreen, true);
    AddMeshToList(bullet1);

    Mesh* bullet2 = object2D::CreateRectangle1("bullet2", glm::vec3(1200, 660, 0), 10, 15, grassGreen, true);
    AddMeshToList(bullet2);

    Mesh* scoreBox = object2D::CreateRectangle1("scoreBox", glm::vec3(1100, 640, 0), 110, 10, grassGreen, false);
    AddMeshToList(scoreBox);

    Mesh* score = object2D::CreateRectangle1("score", glm::vec3(1100, 640, 0), 2.75f, 10, golden, true);
    AddMeshToList(score);

    // START MESHES
    
    Mesh* starT1 = object2D::CreateTriangle("starT1", glm::vec3(625, 360, 0), glm::vec3(655, 360, 0), glm::vec3(640, 405, 0), golden, true);
    AddMeshToList(starT1);

    Mesh* starT2 = object2D::CreateTriangle("starT2", glm::vec3(595, 360, 0), glm::vec3(655, 360, 0), glm::vec3(670, 300, 0), golden, true);
    AddMeshToList(starT2);

    Mesh* starT3 = object2D::CreateTriangle("starT3", glm::vec3(625, 360, 0), glm::vec3(685, 360, 0), glm::vec3(610, 300, 0), golden, true);
    AddMeshToList(starT3);

    Mesh* starT11 = object2D::CreateTriangle("starT11", glm::vec3(625, 360, 0), glm::vec3(655, 360, 0), glm::vec3(640, 405, 0), red, true);
    AddMeshToList(starT11);

    Mesh* starT22 = object2D::CreateTriangle("starT22", glm::vec3(595, 360, 0), glm::vec3(655, 360, 0), glm::vec3(670, 300, 0), red, true);
    AddMeshToList(starT22);

    Mesh* starT33 = object2D::CreateTriangle("starT33", glm::vec3(625, 360, 0), glm::vec3(685, 360, 0), glm::vec3(610, 300, 0), red, true);
    AddMeshToList(starT33);

    // GRASS
    Mesh* grass = object2D::CreateRectangle1("grass", glm::vec3(0, 0, 0), width, 100, grassGreen, true);
    AddMeshToList(grass);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.3f, 0, 0.8f, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::CreateDuck(float startX, float startY, float deltaTimeSeconds, float speed, glm::mat3 duck)
{

    // HiddenBox movement
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(startX, startY);

    translateX += deltaTimeSeconds * cos(angularRand) * speed;
    translateY += deltaTimeSeconds * sin(angularRand) * speed;
    
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= duck;

    // Use them to calculate the area
    GetHiddenBoxVertexes();

    RenderMesh2D(meshes["hiddenBox"], shaders["VertexColor"], modelMatrix);
    
    // First wing movement
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(startX, startY);

    translateX += deltaTimeSeconds * cos(angularRand) * speed;
    translateY += deltaTimeSeconds * sin(angularRand) * speed;
   
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= duck;
    modelMatrix *= transform2D::Translate(20, -25);
    if (angularStep >= 0.4f) {
        angularStep = 0;
    }
    angularStep += deltaTimeSeconds * 0.3f;
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-20, 25);
    RenderMesh2D(meshes["leftWing"], shaders["VertexColor"], modelMatrix);


    // Second wing movement
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(startX, startY);

    translateX += deltaTimeSeconds * cos(angularRand) * speed;
    translateY += deltaTimeSeconds * sin(angularRand) * speed;
 

    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= duck;
    modelMatrix *= transform2D::Translate(20, 25);
    if (angularStep >= 0.4f) {
        angularStep = 0;
    }
    angularStep += deltaTimeSeconds * 0.3f;
    modelMatrix *= transform2D::Rotate(-angularStep);
    modelMatrix *= transform2D::Translate(-20, -25);
    RenderMesh2D(meshes["rightWing"], shaders["VertexColor"], modelMatrix);

    // Body movement
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(startX, startY);

    translateX += deltaTimeSeconds * cos(angularRand) * speed;
    translateY += deltaTimeSeconds * sin(angularRand) * speed;
   
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= duck;
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    // Feathering movement
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(startX, startY);

    translateX += deltaTimeSeconds * cos(angularRand) * speed;
    translateY += deltaTimeSeconds * sin(angularRand) * speed;
   
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= duck;
    RenderMesh2D(meshes["feathering"], shaders["VertexColor"], modelMatrix);

    // Head movement
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(startX, startY);

    translateX += deltaTimeSeconds * cos(angularRand) * speed;
    translateY += deltaTimeSeconds * sin(angularRand) * speed;

    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= duck;
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

    // Beak movement
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(startX, startY);

    translateX += deltaTimeSeconds * cos(angularRand) * speed;
    translateY += deltaTimeSeconds * sin(angularRand) * speed;
   
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= duck;
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);
}

void Tema1::Update(float deltaTimeSeconds)
{
    
    PrepareScene();

    // Counting flying time for duck
    counter = glfwGetTime() - startTime;

    // Maximum number of ducks in order to win is 20
    if (countKills == 20) {
        // score bar completed
        DisplayWinStar(deltaTimeSeconds);
    }

    // Player has no lives
    if (noOfLives == 0) {
        // game over
        DisplayGameOver(deltaTimeSeconds);
    }

    if (displayDuck) {
        // Player can still shoot
        if (noOfDucks <= 5) {
            if (duckIsAlive) {
                // Duck has still time to fly
                if (counter < 5) {
                    // Bullets max number was consumed => duck escape
                    if (noOfBullets == 0) {
                        duckIsEscaped = 1;
                        FlyAwayOrKilled(deltaTimeSeconds, M_PI / 2, speed * 2);
                        // If duck escaped, new duck appears in scene
                        if (translateY + startY + cx > height) {
                            startX = 100 + static_cast <float> (rand())
                                / static_cast <float> (RAND_MAX / (width - 100));
                            startY = 100 + static_cast <float> (rand())
                                / static_cast <float> (RAND_MAX / (height - 500));
                            angularRand = LOW_ANGLE + static_cast <float> (rand())
                                / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
                            if (angularRand == M_PI / 2) {
                                LOW_ANGLE + static_cast <float> (rand())
                                    / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
                            }
                            ResetDuck();
                            noOfDucks++;
                            noOfLives--;
                            startTime = glfwGetTime();
                            CreateDuck(startX, startY, deltaTimeSeconds, speed, RotateFirst(angularRand));
                        }
                    }
                    else {
                        // CALCULATE COLLISION ANGLES
                        CalculateCollisionAngles();
                        CreateDuck(startX, startY, deltaTimeSeconds, speed, RotateFirst(angularRand));
                    }
                }
                else {
                    // Flying time is up => duck escape
                    duckIsEscaped = 1;
                    FlyAwayOrKilled(deltaTimeSeconds, M_PI / 2, speed * 2);
                    // If duck escaped, new duck appears in scene
                    if (translateY + startY + cx > height) {
                        startX = 100 + static_cast <float> (rand())
                            / static_cast <float> (RAND_MAX / (width - 100));
                        startY = 100 + static_cast <float> (rand())
                            / static_cast <float> (RAND_MAX / (height - 500));
                        angularRand = LOW_ANGLE + static_cast <float> (rand())
                            / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
                        if (angularRand == M_PI / 2) {
                            LOW_ANGLE + static_cast <float> (rand())
                                / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
                        }
                        ResetDuck();
                        noOfDucks++;
                        noOfLives--;
                        startTime = glfwGetTime();
                        CreateDuck(startX, startY, deltaTimeSeconds, speed, RotateFirst(angularRand));
                    }
                }
            }
            else {
                // Player shot a duck
                duckIsEscaped = 1;
                FlyAwayOrKilled(deltaTimeSeconds, 3 * M_PI / 2, speed * 2);
                // If duck died, new duck appears in scene
                if (translateY + startY + cx < 0) {
                    startX = 100 + static_cast <float> (rand())
                        / static_cast <float> (RAND_MAX / (width - 100));
                    startY = 100 + static_cast <float> (rand())
                        / static_cast <float> (RAND_MAX / (height - 500));
                    angularRand = LOW_ANGLE + static_cast <float> (rand())
                        / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
                    if (angularRand == M_PI / 2) {
                        LOW_ANGLE + static_cast <float> (rand())
                            / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
                    }
                    ResetDuck();
                    noOfDucks++;
                    startTime = glfwGetTime();
                    CreateDuck(startX, startY, deltaTimeSeconds, speed, RotateFirst(angularRand));
                }
            }
        }
        else {
            // Max number of ducks in a round
            // Next round
            // Speed increases
            startX = 100 + static_cast <float> (rand())
                / static_cast <float> (RAND_MAX / (width - 100));
            startY = 100 + static_cast <float> (rand())
                / static_cast <float> (RAND_MAX / (height - 500));
            angularRand = LOW_ANGLE + static_cast <float> (rand())
                / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
            if (angularRand == M_PI / 2) {
                LOW_ANGLE + static_cast <float> (rand())
                    / static_cast <float> (RAND_MAX / (DIFF_ANGLE));
            }
            ResetDuck();
            speed *= 1.5f;
            noOfDucks = 0;
            startTime = glfwGetTime();
            CreateDuck(startX, startY, deltaTimeSeconds, speed, RotateFirst(angularRand));
        }
    }
}


void Tema1::ResetDuck() {
    // Reset flags
    translateX = 0;
    translateY = 0;
    noOfBullets = 3;
    duckIsEscaped = 0;
    duckIsAlive = 1;
}


void Tema1::PrepareScene() {
    // GRASS
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    // Score box
    RenderMesh2D(meshes["scoreBox"], shaders["VertexColor"], modelMatrix);

    // Update score bar (2 points for each killed duck => total is 10)    
    if (countKills >= 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1100, 640);
        scaleX = 2 * countKills;
        modelMatrix *= transform2D::Scale(scaleX, 1);
        modelMatrix *= transform2D::Translate(-1100, -640);
        RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);
    }

    // Bullets
    modelMatrix = glm::mat3(1);
    if (noOfBullets >= 1) {
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }
    if (noOfBullets >= 2) {
        RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], modelMatrix);
    }
    if (noOfBullets == 3) {
        RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], modelMatrix);
    }

    // Lives
    modelMatrix = glm::mat3(1);
    if (noOfLives >= 1) {
        modelMatrix *= transform2D::Translate(1105, 700);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }

    if (noOfLives >= 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1155, 700);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }

    if (noOfLives == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1205, 700);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::DisplayWinStar(float deltaTimeSeconds) {
    displayDuck = 0;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(640, 340);
    angularStep += deltaTimeSeconds * 0.3f;
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-640, -340);
    RenderMesh2D(meshes["starT1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(640, 340);
    angularStep += deltaTimeSeconds * 0.3f;
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-640, -340);
    RenderMesh2D(meshes["starT2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(640, 340);
    angularStep += deltaTimeSeconds * 0.3f;
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-640, -340);
    RenderMesh2D(meshes["starT3"], shaders["VertexColor"], modelMatrix);
}

void Tema1::DisplayGameOver(float deltaTimeSeconds) {
    displayDuck = 0;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(640, 340);
    angularStep += deltaTimeSeconds * 0.3f;
    modelMatrix *= transform2D::Rotate(-angularStep);
    modelMatrix *= transform2D::Translate(-640, -340);
    RenderMesh2D(meshes["starT11"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(640, 340);
    angularStep += deltaTimeSeconds * 0.3f;
    modelMatrix *= transform2D::Rotate(-angularStep);
    modelMatrix *= transform2D::Translate(-640, -340);
    RenderMesh2D(meshes["starT22"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(640, 340);
    angularStep += deltaTimeSeconds * 0.3f;
    modelMatrix *= transform2D::Rotate(-angularStep);
    modelMatrix *= transform2D::Translate(-640, -340);
    RenderMesh2D(meshes["starT33"], shaders["VertexColor"], modelMatrix);
}

void Tema1::CalculateCollisionAngles() {
    // Up
    if (translateY + startY - cx > height) {
        angularRand = 2 * M_PI - angularRand;
        translateX -= 10;
    }
    // Right
    else if (translateX + startX - cx > width) {
        if (angularRand >= M_PI) {
            angularRand = 3 * M_PI - angularRand;
        }
        else {
            angularRand = M_PI - angularRand;
        }
        translateY += 10;
    }
    // Left
    else if (translateX + startX - cx < 0) {
        if (angularRand >= M_PI) {
            angularRand = 3 * M_PI - angularRand;
        }
        else {
            angularRand = M_PI - angularRand;
        }
        translateY -= 10;
    }
    // Down
    else if (translateY + startY - cx < 0) {
        angularRand = 2 * M_PI - angularRand;
        translateX += 10;
    }
    // Negative angle
    if (angularRand >= 2 * M_PI) {
        angularRand -= 2 * M_PI;
    }
}

glm::mat3 Tema1::RotateFirst(float angularRand)
{
    // Calculate rotation matrix to indicate given orientation
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Rotate(angularRand);
    modelMatrix *= transform2D::Translate(cx, cy);
    return modelMatrix;
}

void Tema1::FlyAwayOrKilled(float deltaTimeSeconds, float angle, float speed)
{
      
   glm::mat3 duck = RotateFirst(angle);

   // HiddenBox movement
   modelMatrix = glm::mat3(1);
   modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
   translateY += deltaTimeSeconds * sin(angle) * speed;
   modelMatrix *= transform2D::Translate(0, translateY);
   modelMatrix *= duck;
   RenderMesh2D(meshes["hiddenBox"], shaders["VertexColor"], modelMatrix);

   // First wing movement
   modelMatrix = glm::mat3(1);
   modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
   translateY += deltaTimeSeconds * sin(angle) * speed;
   modelMatrix *= transform2D::Translate(0, translateY);
   modelMatrix *= duck;

   // Duck dead, no wing movement
   if (duckIsAlive) {
       modelMatrix *= transform2D::Translate(20, -25);
       if (angularStep >= 0.4f) {
           angularStep = 0;
       }
       angularStep += deltaTimeSeconds * 0.3f;
       modelMatrix *= transform2D::Rotate(angularStep);
       modelMatrix *= transform2D::Translate(-20, 25);
   }
   RenderMesh2D(meshes["leftWing"], shaders["VertexColor"], modelMatrix);

   // Second wing movement
   modelMatrix = glm::mat3(1);
   modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
   translateY += deltaTimeSeconds * sin(angle) * speed;
   modelMatrix *= transform2D::Translate(0, translateY);
   modelMatrix *= duck;

   // Duck dead, no wing movement
   if (duckIsAlive) {
       modelMatrix *= transform2D::Translate(20, 25);
       if (angularStep >= 0.4f) {
           angularStep = 0;
       }
       angularStep += deltaTimeSeconds * 0.3f;
       modelMatrix *= transform2D::Rotate(-angularStep);
       modelMatrix *= transform2D::Translate(-20, -25);
   }
   RenderMesh2D(meshes["rightWing"], shaders["VertexColor"], modelMatrix);

   // Body movement
   modelMatrix = glm::mat3(1);
   modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
   translateY += deltaTimeSeconds * sin(angle) * speed;
   modelMatrix *= transform2D::Translate(0, translateY);
   modelMatrix *= duck;
   RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

   // Feathering movement
   modelMatrix = glm::mat3(1);
   modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
   translateY += deltaTimeSeconds * sin(angularRand) * speed;
   modelMatrix *= transform2D::Translate(0, translateY);
   modelMatrix *= duck;
   RenderMesh2D(meshes["feathering"], shaders["VertexColor"], modelMatrix);

   // Head movement
   modelMatrix = glm::mat3(1);
   modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
   translateY += deltaTimeSeconds * sin(angle) * speed;
   modelMatrix *= transform2D::Translate(0, translateY);
   modelMatrix *= duck;
   RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

   // Death animation
   if (duckIsAlive == 0) {
       modelMatrix = glm::mat3(1);
       modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
       translateY += deltaTimeSeconds * sin(angle) * speed;
       modelMatrix *= transform2D::Translate(0, translateY);
       modelMatrix *= duck;
       RenderMesh2D(meshes["blood"], shaders["VertexColor"], modelMatrix);

       modelMatrix = glm::mat3(1);
       modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
       translateY += deltaTimeSeconds * sin(angle) * speed;
       modelMatrix *= transform2D::Translate(0, translateY);
       modelMatrix *= duck;
       RenderMesh2D(meshes["bloodDrop"], shaders["VertexColor"], modelMatrix);

       modelMatrix = glm::mat3(1);
       modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
       translateY += deltaTimeSeconds * sin(angle) * speed;
       modelMatrix *= transform2D::Translate(0, translateY);
       modelMatrix *= duck;
       RenderMesh2D(meshes["bloodDrop1"], shaders["VertexColor"], modelMatrix);

       modelMatrix = glm::mat3(1);
       modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
       translateY += deltaTimeSeconds * sin(angle) * speed;
       modelMatrix *= transform2D::Translate(0, translateY);
       modelMatrix *= duck;
       RenderMesh2D(meshes["bloodDrop2"], shaders["VertexColor"], modelMatrix);
   }

   // Beak movement
   modelMatrix = glm::mat3(1);
   modelMatrix *= transform2D::Translate(startX + translateX - cx, startY);
   translateY += deltaTimeSeconds * sin(angle) * speed;
   modelMatrix *= transform2D::Translate(0, translateY);
   modelMatrix *= duck;
   RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{  
}


void Tema1::OnKeyPress(int key, int mods)
{   
}


void Tema1::OnKeyRelease(int key, int mods)
{
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{   
}

float Tema1::Area(float x1, float y1, float x2, float y2,
    float x3, float y3)
{
    return abs((x1 * (y2 - y3) + x2 * (y3 - y1) +
        x3 * (y1 - y2)) / 2.0);
}

bool Tema1::Check(float x1, float y1, float x2, float y2, float x3,
    float y3, float x4, float y4, float x, float y)
{
    float A = 4 * cx * cy;
    float A1 = Area(x1, y1, x2, y2, x, y);
    float A2 = Area(x2, y2, x3, y3, x, y);
    float A3 = Area(x3, y3, x4, y4, x, y);
    float A4 = Area(x1, y1, x4, y4, x, y);
    return (A >= A1 + A2 + A3 + A4);
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    
    glm::ivec2 resolution = window->GetResolution();
    mouseX *= width / resolution.x;
    mouseY *= height / resolution.y;

    // Check if the player shot the duck
    if (Check(x1, y1, x2, y2, x3, y3, x4, y4, mouseX, height - mouseY)) {
        duckIsAlive = 0;
        countKills += 1;
    }

    // Bullets are consumed if player clicks on screen
    if (button && !duckIsEscaped && displayDuck) {
        noOfBullets--;
    }
}

void Tema1::GetHiddenBoxVertexes() {
    x1 = startX + translateX - cx;
    y1 = startY + translateY - cy;
    x2 = startX + translateX + cx;
    y2 = startY + translateY - cy;
    x3 = startX + translateX - cx;
    y3 = startY + translateY + cy;
    x4 = startX + translateX - cx;
    y4 = startY + translateY + cy;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}