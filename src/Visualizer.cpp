//
// Created by Momo on 23/09/2026.
//

#include "Visualizer.h"
#include <raylib.h>

void runVisualizer() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Parking Sensor Visualizer");
    SetTargetFPS(60);

    Texture2D parkingView = LoadTexture("../assets/parking_view.png");

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        Rectangle source{
            0.0f,
            0.0f,
            static_cast<float>(parkingView.width),
            static_cast<float>(parkingView.height)
        };

        Rectangle destination{
            0.0f,
            0.0f,
            static_cast<float>(screenWidth),
            static_cast<float>(screenHeight)
        };

        Vector2 origin{0.0f, 0.0f};

        DrawTexturePro(
            parkingView,
            source,
            destination,
            origin,
            0.0f,
            WHITE
        );

        EndDrawing();
    }

    UnloadTexture(parkingView);
    CloseWindow();
}