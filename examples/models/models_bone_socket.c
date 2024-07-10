/*******************************************************************************************
*
*   raylib [core] example - Using bones as socket for calculating the positioning of something
* 
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by iP (@ipzaur) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024 iP (@ipzaur)
*
********************************************************************************************/

#include "raylib.h"

#include "raymath.h"

#define BONE_SOCKETS        3
#define BONE_SOCKET_HAT     0
#define BONE_SOCKET_HAND_R  1
#define BONE_SOCKET_HAND_L  2

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - bone socket");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 5.0f, 5.0f, 5.0f }; // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 2.0f, 0.0f };  // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };      // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                            // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;         // RL_Camera projection type

    // Load gltf model
    RL_Model characterModel = RL_LoadModel("resources/models/gltf/greenman.glb"); // Load character model
    RL_Model equipModel[BONE_SOCKETS] = {
        RL_LoadModel("resources/models/gltf/greenman_hat.glb"),    // Index for the hat model is the same as BONE_SOCKET_HAT
        RL_LoadModel("resources/models/gltf/greenman_sword.glb"),  // Index for the sword model is the same as BONE_SOCKET_HAND_R
        RL_LoadModel("resources/models/gltf/greenman_shield.glb")  // Index for the shield model is the same as BONE_SOCKET_HAND_L
    };
    
    bool showEquip[3] = { true, true, true };   // Toggle on/off equip

    // Load gltf model animations
    int animsCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;
    RL_ModelAnimation *modelAnimations = RL_LoadModelAnimations("resources/models/gltf/greenman.glb", &animsCount);

    // indices of bones for sockets
    int boneSocketIndex[BONE_SOCKETS] = { -1, -1, -1 };

    // search bones for sockets 
    for (int i = 0; i < characterModel.boneCount; i++)
    {
        if (RL_TextIsEqual(characterModel.bones[i].name, "socket_hat"))
        {
            boneSocketIndex[BONE_SOCKET_HAT] = i;
            continue;
        }
        
        if (RL_TextIsEqual(characterModel.bones[i].name, "socket_hand_R"))
        {
            boneSocketIndex[BONE_SOCKET_HAND_R] = i;
            continue;
        }
        
        if (RL_TextIsEqual(characterModel.bones[i].name, "socket_hand_L"))
        {
            boneSocketIndex[BONE_SOCKET_HAND_L] = i;
            continue;
        }
    }

    RL_Vector3 position = { 0.0f, 0.0f, 0.0f }; // Set model position
    unsigned short angle = 0;           // Set angle for rotate character

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        
        // Rotate character
        if (RL_IsKeyDown(KEY_F)) angle = (angle + 1)%360;
        else if (RL_IsKeyDown(KEY_H)) angle = (360 + angle - 1)%360;

        // Select current animation
        if (RL_IsKeyPressed(KEY_T)) animIndex = (animIndex + 1)%animsCount;
        else if (RL_IsKeyPressed(KEY_G)) animIndex = (animIndex + animsCount - 1)%animsCount;

        // Toggle shown of equip
        if (RL_IsKeyPressed(KEY_ONE)) showEquip[BONE_SOCKET_HAT] = !showEquip[BONE_SOCKET_HAT];
        if (RL_IsKeyPressed(KEY_TWO)) showEquip[BONE_SOCKET_HAND_R] = !showEquip[BONE_SOCKET_HAND_R];
        if (RL_IsKeyPressed(KEY_THREE)) showEquip[BONE_SOCKET_HAND_L] = !showEquip[BONE_SOCKET_HAND_L];
        
        // Update model animation
        RL_ModelAnimation anim = modelAnimations[animIndex];
        animCurrentFrame = (animCurrentFrame + 1)%anim.frameCount;
        RL_UpdateModelAnimation(characterModel, anim, animCurrentFrame);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);
                // Draw character
                RL_Quaternion characterRotate = QuaternionFromAxisAngle((RL_Vector3){ 0.0f, 1.0f, 0.0f }, angle*DEG2RAD);
                characterModel.transform = MatrixMultiply(QuaternionToMatrix(characterRotate), MatrixTranslate(position.x, position.y, position.z));
                RL_UpdateModelAnimation(characterModel, anim, animCurrentFrame);
                RL_DrawMesh(characterModel.meshes[0], characterModel.materials[1], characterModel.transform);

                // Draw equipments (hat, sword, shield)
                for (int i = 0; i < BONE_SOCKETS; i++)
                {
                    if (!showEquip[i]) continue;

                    RL_Transform *transform = &anim.framePoses[animCurrentFrame][boneSocketIndex[i]];
                    RL_Quaternion inRotation = characterModel.bindPose[boneSocketIndex[i]].rotation;
                    RL_Quaternion outRotation = transform->rotation;
                    
                    // Calculate socket rotation (angle between bone in initial pose and same bone in current animation frame)
                    RL_Quaternion rotate = QuaternionMultiply(outRotation, QuaternionInvert(inRotation));
                    RL_Matrix matrixTransform = QuaternionToMatrix(rotate);
                    // Translate socket to its position in the current animation
                    matrixTransform = MatrixMultiply(matrixTransform, MatrixTranslate(transform->translation.x, transform->translation.y, transform->translation.z));
                    // RL_Transform the socket using the transform of the character (angle and translate)
                    matrixTransform = MatrixMultiply(matrixTransform, characterModel.transform);
                    
                    // Draw mesh at socket position with socket angle rotation
                    RL_DrawMesh(equipModel[i].meshes[0], equipModel[i].materials[1], matrixTransform);
                }

                RL_DrawGrid(10, 1.0f);
            RL_EndMode3D();

            RL_DrawText("Use the T/G to switch animation", 10, 10, 20, RL_GRAY);
            RL_DrawText("Use the F/H to rotate character left/right", 10, 35, 20, RL_GRAY);
            RL_DrawText("Use the 1,2,3 to toggle shown of hat, sword and shield", 10, 60, 20, RL_GRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadModelAnimations(modelAnimations, animsCount);
    RL_UnloadModel(characterModel);         // Unload character model and meshes/material
    
    // Unload equipment model and meshes/material
    for (int i = 0; i < BONE_SOCKETS; i++) RL_UnloadModel(equipModel[i]);

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}