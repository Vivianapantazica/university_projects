#include "lab_m1/Tema2/Tema2.h"



#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    initialPoints = {
            glm::vec3(-9, 0, 0),
            glm::vec3(-9, 0, 3),
            glm::vec3(-6, 0, 5),
            glm::vec3(-3, 0, 5),
            glm::vec3(-1, 0, 4),
            glm::vec3(2, 0, 2),
            glm::vec3(3.96f, 0, 1.43f),
            glm::vec3(7, 0, 2),
            glm::vec3(10, 0, 3),
            glm::vec3(14, 0, 2),
            glm::vec3(15.5f, 0, 0),
            glm::vec3(13, 0, -4),
            glm::vec3(11, 0, -5),
            glm::vec3(8, 0, -5),
            glm::vec3(5, 0, -4),
            glm::vec3(3, 0, -4),
            glm::vec3(-1, 0, -5),
            glm::vec3(-5.02f, 0, -5.49f),
            glm::vec3(-8, 0, -4),
            glm::vec3(-9.5f, 0, -2.49f)};

    // Set up pentru cele 2 camere (camera principala si cea din mini viewport)
    CameraSetUp();
    
    std::vector<glm::vec3> initialPoints1 = initialPoints;
    std::vector<glm::vec3> initialPoints2 = initialPoints;
    std::vector<glm::vec3> initialPoints3 = initialPoints;

    // Generare locatii copacei
    GenerateTreeLocations();

    // Generare traseu pentru masinutele obstacol
    GenerateCarTraces(initialPoints1);

    // Generare limite pista
    GenerateRaceTrackLimits(initialPoints2);

   
    // PLAN
    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // COPAC
    {
        Mesh* mesh = new Mesh("crown");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("crownSphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("trunk");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // MASINUTA obstacol
    {
        Mesh* mesh = new Mesh("car");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // PISTA
    {
        Mesh* raceTrack = object3D::CreateRaceTrack("raceTrack", glm::vec3(0, 0, 0), initialPoints, glm::vec3(0.01f, 0.01f, 0.02f), true);
        AddMeshToList(raceTrack);
    }

    // LINIE DE MIJLOC
    {
        Mesh* middleLine = object3D::CreateMiddleLine("middleLine", glm::vec3(0, 0, 0), initialPoints3, glm::vec3(1, 1, 1), true);
        AddMeshToList(middleLine);
    }

    // Shader Program
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // Initializare matricea de proiectie cu proiectia perspectiva
    right = 10.f;
    left = -10.f;
    bottom = -10.f;
    top = 10.f;
    fov = 0.f;
    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);

    // Setare rezolutie pentru mini viewport
    glm::ivec2 resolution = window->GetResolution();
    height = (float)resolution.y;
    width = (float)resolution.x;
    miniViewportArea = ViewportArea(width / resolution.x + 50, height / resolution.y + 50,  resolution.x / 5.f, resolution.y / 5.f);
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.45f, 0.8f, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    // Randam scena principala din perspectiva camerei 1
    RenderScene(deltaTimeSeconds, camera);

    glClear(GL_DEPTH_BUFFER_BIT);
    glm::ivec2 resolution = window->GetResolution();
    glViewport(width / resolution.x + 50, height / resolution.y + 50, resolution.x / 5.f, resolution.y / 5.f);

    // Randam scena din nou in mini viewport, din perspectiva mini camerei (orientata in jos, proiecte ortogonala)
    miniCamera->Set(glm::vec3(camera->GetTargetPosition().x, camera->GetTargetPosition().y + 10, camera->GetTargetPosition().z), camera->GetTargetPosition(), glm::vec3(0, 0, 1));
    RenderScene(deltaTimeSeconds, miniCamera);
}

void Tema2::RenderScene(float deltaTimeSeconds, implemented::Camera2* cam) {

    // Trimisa in Vertex Shader pentru a obtine efectul de curbura
    glm::vec3 carPosition = camera->GetTargetPosition();

    // TEREN
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(0.2f, 0.8f, 0.2f), carPosition, cam);
    }

    // PISTA
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
        RenderSimpleMesh(meshes["raceTrack"], shaders["LabShader"], modelMatrix, glm::vec3(0.01f, 0.01f, 0.02f), carPosition, cam);
    }

    // LINIA DE MIJLOC
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
        RenderSimpleMesh(meshes["middleLine"], shaders["LabShader"], modelMatrix, glm::vec3(0.9f, 0.9f, 0.8f), carPosition, cam);
    }

    // MASINUTA MEA
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, 0.127f, camera->GetTargetPosition().z));
        modelMatrix = glm::rotate(modelMatrix, -rotationAngle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.25f, 0.75f));
        RenderSimpleMesh(meshes["car"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0.6f, 0.6f), carPosition, cam);
    }

    // MASINUTELE obstacol

    // Calculam unghiurile de rotatie folosind formula cos(theta) = a*b / |a|*|b| => vectorii a, b fiind normalizati => numitorul este 1
    // Masina2 va fi mai rapida decat masina1
    if (j < carOnePoints.size() - 20) {
        j += deltaTimeSeconds * 50;
        rotationAngle1 = glm::acos(glm::dot(glm::normalize(carOnePoints[j + 1] - carOnePoints[j]), glm::vec3(0, 0, 1)));
    }
    else {
        rotationAngle1 = glm::acos(glm::dot(glm::normalize(carOnePoints[0] - carOnePoints[j]), glm::vec3(0, 0, 1)));
        j = 0;
    }

    if (x < carTwoPoints.size() - 40) {
        x += deltaTimeSeconds * 150;
        rotationAngle2 = glm::acos(glm::dot(glm::normalize(carTwoPoints[x + 1] - carTwoPoints[x]), glm::vec3(0, 0, 1)));
    }
    else {
        rotationAngle2 = glm::acos(glm::dot(glm::normalize(carTwoPoints[0] - carTwoPoints[x]), glm::vec3(0, 0, 1)));
        x = 0;
    }

    if (carOnePoints[j][2] < 0) {
        rotationAngle1 *= -1;
    }

    if (carTwoPoints[x][2] < 0) {
        rotationAngle2 *= -1;
    }

    {   
        // verificam daca traiectoria masinii conduse de noi se interesecteaza cu traiectoria prestabilita a masinii1
        collisionDetectedWithCarOne = intersect(glm::vec3(carOnePoints[j][0], carOnePoints[j][1] + 0.127f, carOnePoints[j][2]), camera->GetTargetPosition(), 0.5f);

        // randam masinuta 1 in scena
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(carOnePoints[j][0], carOnePoints[j][1] + 0.127f, carOnePoints[j][2]));
        modelMatrix = glm::rotate(modelMatrix, rotationAngle1, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.25f, 0.75f));
        RenderSimpleMesh(meshes["car"], shaders["LabShader"], modelMatrix, glm::vec3(0.2f, 0.2f, 1), carPosition, cam);
    }

    {
        // verificam daca traiectoria masinii conduse de noi se interesecteaza cu traiectoria prestabilita a masinii2
        collisionDetectedWithCarTwo = intersect(glm::vec3(carTwoPoints[x][0], carTwoPoints[x][1] + 0.127f, carTwoPoints[x][2]), camera->GetTargetPosition(), 0.5f);

        // randam masinuta 2 in scena
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(carTwoPoints[x][0], carTwoPoints[x][1] + 0.127f, carTwoPoints[x][2]));
        modelMatrix = glm::rotate(modelMatrix, rotationAngle2, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.25f, 0.75f));
        RenderSimpleMesh(meshes["car"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0.2f, 0.2f), carPosition, cam);
    }

    // Adaugare COPACI

    // Generam copacii pe conturul pistei, avand grija ca acestia sa nu se afle prea aproape de pista
    for (int i = 0; i < treePositionPoints.size(); i++) {
        float posX = treePositionPoints[i][0];
        float posY = treePositionPoints[i][1];
        float posZ = treePositionPoints[i][2];
        glm::vec3 trunkColor = glm::vec3(0.3f, 0.1f, 0.1f);

        // Am randat copaci ce au coroana de diferite forme (cub sau sfera)
        if (i % 3 == 0) {

            // Cazuri particulare (primul si ultimul copac interior care sunt generati)
            if (i == 21) {
                posX -= 0.75f;
            }

            if (i == 3) {
                posX += 0.75f;
            }

            // coroana tip cub
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(posX, posY + 1, posZ));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
                RenderSimpleMesh(meshes["crown"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0.5f, 0.2f), carPosition, cam);
            }
        }
        else {

            // coroana tip sfera
            {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(posX, posY + 1, posZ));
                RenderSimpleMesh(meshes["crownSphere"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0.2f, 0), carPosition, cam);
            }

        }

        // Desi coroana difera, trunchiul este identic pentru orice tip de copac
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(posX, posY + 0.375f, posZ));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f, 0.75f, 0.25f));
            RenderSimpleMesh(meshes["trunk"], shaders["LabShader"], modelMatrix, trunkColor, carPosition, cam);
        }
    }
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, const glm::vec3& carPos, implemented::Camera2* cam)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = cam->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    // Matricea de proiectie difera pentru scena principla si mini viewport
    if (cam == camera) {
        glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
        int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
        glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }
    else if (cam == miniCamera) {
        glm::mat4 projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
        int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
        glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }

    // Trimitem in Vertex Shader culoarea obiectului
    GLint locObject = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(locObject, 1, glm::value_ptr(color));

    // Trimitem in Vertex Shader pozitia curenta a masinii
    GLint locObjectCar = glGetUniformLocation(shader->program, "carPos");
    glUniform3fv(locObjectCar, 1, glm::value_ptr(carPos));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema2::FrameEnd()
{
    
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
        float cameraSpeed = 2.0f;
        
        // Pozitia curenta a masinii
        glm::vec3 myPosition = camera->GetTargetPosition();

        // Daca nu sunt detectate coliziuni cu niciuna dintre masinile obstacol, ne putem deplasa
        // in fata sau in spate in cazul in care si pozitia curenta a masinii este in interiorul pistei;

        // Altfel, verificam daca pozitia urmatoare este valida sau nu (valida == ne face sa ne intoarcem pe pista);

        // Deblocam tasta W (directia inainte) prin rotatiile permise (la stanga -> A, la dreapta -> D), 
        // dar putem da si cu spatele (S).

        // La fel trebuie verificat si ca masinuta sa nu iasa din pista cu spatele

        if (!collisionDetectedWithCarOne && !collisionDetectedWithCarTwo) {

            if (isInsideRaceTrack(myPosition)) {
                // Cat timp suntem pe pista, miscarea fata - spate e OK
                if (window->KeyHold(GLFW_KEY_W)) {
                    camera->TranslateForward(deltaTime * cameraSpeed);

                }

                if (window->KeyHold(GLFW_KEY_S)) {
                    camera->TranslateForward(-deltaTime * cameraSpeed);
                }
            }
            else {
                // Daca iesim de pe pista, avem nevoie de verificari suplimentare ca sa ne intoarcem pe aceasta:
                // Calculam pozitia urmatoare a masinii (cu fata, respectiv cu spatele)
                glm::vec3 nextFrontPosition = camera->position + glm::normalize(camera->forward) * deltaTime * cameraSpeed +
                    camera->forward * camera->distanceToTarget;

                glm::vec3 nextBackPosition = camera->position - glm::normalize(camera->forward) * deltaTime * cameraSpeed +
                    camera->forward * camera->distanceToTarget;
                
                // Mutam camera in fata doar daca verificam ca acest lucru este posibil,
                // adica nextPosition se afla in interiorul pistei
                if (window->KeyHold(GLFW_KEY_W)) {
                    if (isInsideRaceTrack(nextFrontPosition)) {
                        camera->TranslateForward(deltaTime * cameraSpeed);
                    }
                }

                // Mutam camera in spate doar daca verificam ca acest lucru este posibil,
                // adica nextBackPosition se afla in interiorul pistei
                if (window->KeyHold(GLFW_KEY_S)) {
                    if (isInsideRaceTrack(nextBackPosition)) {
                        camera->TranslateForward(-deltaTime * cameraSpeed);
                    }
                }
            }

            // Rotatiile stanga-dreapta sunt permise in orice caz in afara de cel din momentul coliziunilor
            // Modificam si rotationAngle al masinii (aceasta se va roti invers camerei)
            if (window->KeyHold(GLFW_KEY_A)) {
                rotationAngle -= deltaTime * cameraSpeed;
                camera->RotateThirdPerson_OY(deltaTime * cameraSpeed);
            }

            if (window->KeyHold(GLFW_KEY_D)) {
                rotationAngle += deltaTime * cameraSpeed;
                camera->RotateThirdPerson_OY(-deltaTime * cameraSpeed);
            }
        }
}


void Tema2::OnKeyPress(int key, int mods)
{

}

void Tema2::CameraSetUp() {
    // Retinem primele 2 puncte ale pistei (unde randam masinuta), pentru a o orienta corect in functie de pista 
    startPoint = glm::vec3(initialPoints[0][0], initialPoints[0][1] + 1, initialPoints[0][2]);
    secondPoint = glm::vec3(initialPoints[1][0], initialPoints[1][1] + 1, initialPoints[1][2]);

    // Pozitionam camera a.i. target ul sa fie masinuta noastra
    camera = new implemented::Camera2();
    camera->Set(secondPoint, startPoint, glm::vec3(0, 1, 0));

    // Pozitionam minicamera asa incat targetul sa fie tot masinuta, dar o orientam ca aceasta sa "priveasca" de sus
    miniCamera = new implemented::Camera2();
    miniCamera->Set(glm::vec3(0, 0, 0), camera->GetTargetPosition(), glm::vec3(0, 0, 1));
}

// Generam copaci de a lungul pistei, in interiorul si exteriorul ei, pe un contur putin mai departat,
// pentru ca acestia sa nu se intersecteze cu pista (treePositionPoints)
void Tema2::GenerateTreeLocations() {
    std::vector<glm::vec3> allPoints = {};

    std::vector<glm::vec3> inPoints = {};

    std::vector<glm::vec3> extPoints = {};

    initialPoints.push_back(initialPoints[0]);

    for (int i = 0; i < initialPoints.size() - 1; i++) {
        for (float j = 0; j < 1; j += 0.01) {
            allPoints.push_back(object3D::generateIntermediatePoints(initialPoints[i], initialPoints[i + 1], j));
        }
    }
    allPoints.push_back(initialPoints[initialPoints.size() - 1]);

    int i = 0;
    for (i; i < allPoints.size() - 1; i++) {
        std::vector<glm::vec3> morePoints = object3D::generateInnerAndOuterPoints(allPoints[i], allPoints[i + 1], 1.8f);
        inPoints.push_back(morePoints[0]);
        extPoints.push_back(morePoints[1]);
    }
    std::vector<glm::vec3> morePoints = object3D::generateInnerAndOuterPoints(allPoints[i], allPoints[0], 1.8f);
    inPoints.push_back(morePoints[0]);
    extPoints.push_back(morePoints[1]);

    for (int i = 0; i < inPoints.size() / 100; i++) {
        treePositionPoints.push_back(inPoints[i * 100]);
        treePositionPoints.push_back(extPoints[i * 100]);
    }
}

// Generam trasee prestabilite pentru cele 2 masinute-obstacol (carOnePoints si carTwoPoints)
void Tema2::GenerateCarTraces(std::vector<glm::vec3> initialPoints1) {
    std::vector<glm::vec3> allPoints1 = {};
    initialPoints1.push_back(initialPoints1[0]);

    for (int i = 0; i < initialPoints1.size() - 1; i++) {
        for (float j = 0; j < 1; j += 0.01) {
            allPoints1.push_back(object3D::generateIntermediatePoints(initialPoints1[i], initialPoints1[i + 1], j));
        }
    }

    allPoints1.push_back(initialPoints1[initialPoints1.size() - 1]);

    int q = 0;
    for (q; q < allPoints1.size() - 1; q++) {
        std::vector<glm::vec3> morePoints1 = object3D::generateInnerAndOuterPoints(allPoints1[q], allPoints1[q + 1], 1.2f);
        carOnePoints.push_back(morePoints1[0]);
        carTwoPoints.push_back(morePoints1[1]);
    }
    std::vector<glm::vec3> morePoints1 = object3D::generateInnerAndOuterPoints(allPoints1[q], allPoints1[0], 1.2f);
    carOnePoints.push_back(morePoints1[0]);
    carTwoPoints.push_back(morePoints1[1]);
}

// Generam limitele pistei pe care le folosim pentru a calcula daca masina se afla pe pista sau nu
void Tema2::GenerateRaceTrackLimits(std::vector<glm::vec3> initialPoints2) {
    std::vector<glm::vec3> allPoints2 = {};

    std::vector<glm::vec3> inPoints2 = {};

    std::vector<glm::vec3> extPoints2 = {};

    initialPoints2.push_back(initialPoints2[0]);

    for (int i = 0; i < initialPoints2.size() - 1; i++) {
        for (float j = 0; j < 1; j += 0.01) {
            allPoints2.push_back(object3D::generateIntermediatePoints(initialPoints2[i], initialPoints2[i + 1], j));
        }
    }
    allPoints2.push_back(initialPoints2[initialPoints2.size() - 1]);

    int r = 0;
    for (r; r < allPoints2.size() - 1; r++) {
        std::vector<glm::vec3> morePoints2 = object3D::generateInnerAndOuterPoints(allPoints2[r], allPoints2[r + 1], 1.5f);
        inPoints2.push_back(morePoints2[0]);
        extPoints2.push_back(morePoints2[1]);
    }
    std::vector<glm::vec3> morePoints2 = object3D::generateInnerAndOuterPoints(allPoints2[r], allPoints2[0], 1.5f);
    inPoints2.push_back(morePoints2[0]);
    extPoints2.push_back(morePoints2[1]);

    for (int i = 0; i < inPoints2.size() / 100; i++) {
        raceTrackLimits.push_back(inPoints2[i * 100]);
        raceTrackLimits.push_back(extPoints2[i * 100]);
    }
}

// Aria triunghiului format de punctele a, b, c
float Tema2::getTriangleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    glm::vec3 ab = glm::vec3(b[0] - a[0], 0, b[2] - a[2]);
    glm::vec3 ac = glm::vec3(c[0] - a[0], 0, c[2] - a[2]);
    return abs(ab[0] * ac[2] - ab[2] * ac[0]) / 2.f;
}

// Functie care returneaza daca un punct p se afla in interiorul triunghiului a, b, c 
bool Tema2::isInsideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    float tArea = getTriangleArea(a, b,c);
    float areaSum = getTriangleArea(a, b, p) + getTriangleArea(a, c, p) + getTriangleArea(b, c, p);
    if (abs(tArea - areaSum) <= 0.001f) {
        return true;
    }
    return false;
}

// Functie care verifica daca masinuta se afla pe pista
bool Tema2::isInsideRaceTrack(glm::vec3 p) {
    int i = 0;
    for (i; i < raceTrackLimits.size() - 2; i++) {
        if (isInsideTriangle(p, raceTrackLimits[i], raceTrackLimits[i + 1], raceTrackLimits[i + 2])) {
            return true;
        }
    }
    if (isInsideTriangle(p, raceTrackLimits[i], raceTrackLimits[i + 1], raceTrackLimits[0])) {
        return true;
    }
    if (isInsideTriangle(p, raceTrackLimits[i], raceTrackLimits[0], raceTrackLimits[1])) {
        return true;
    }
    return false;
}

// Functie folosita pt detectarea coliziunilor
float Tema2::intersect(glm::vec3 sphere, glm::vec3 other, float radius) {
    float distance = sqrt(
        (sphere.x - other.x) * (sphere.x - other.x) +
        (sphere.y - other.y) * (sphere.y - other.y) +
        (sphere.z - other.z) * (sphere.z - other.z)
    );
    return distance < 2 * radius;
}

void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
   
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
