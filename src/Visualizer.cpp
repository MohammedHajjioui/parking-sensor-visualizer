//
// Created by Momo on 23/09/2026.
//

#include "Visualizer.h"
#include <raylib.h>

namespace {
    constexpr int SCREEN_WIDTH = 924;
    constexpr int SCREEN_HEIGHT = 615;

    constexpr float IMAGE_X = 0.0f;
    constexpr float IMAGE_Y = 0.0f;

    constexpr float IMAGE_WIDTH = 924.0f;
    constexpr float IMAGE_HEIGHT = 615.0f;

    constexpr float ARC_INNER_RADIUS = 80.0f;
    constexpr float ARC_OUTER_RADIUS = 90.0f;

    constexpr int ARC_SEGMENTS = 32;

    const Color SENSOR_COLOR{255, 255, 255, 220};
}

void drawSensorArcs(Vector2 center, float startAngle, float endAngle, Color color) {
    constexpr int ARC_COUNT = 4;
    constexpr float ARC_SPACING = 22.0f;

    for (int i = 0; i < ARC_COUNT; ++i) {
        const float innerRadius = ARC_INNER_RADIUS + i * ARC_SPACING;

        const float outerRadius = ARC_OUTER_RADIUS + i * ARC_SPACING;

        DrawRingLines(
            center,
            innerRadius,
            outerRadius,
            startAngle,
            endAngle,
            ARC_SEGMENTS,
            color
        );
    }
}

void runVisualizer() {
    InitWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Parking Sensor Visualizer");

    SetTargetFPS(60);

    Texture2D parkingView = LoadTexture("../assets/parking_view.png");

    const float imageCenterX = IMAGE_X + IMAGE_WIDTH / 2.0f;

    const float imageCenterY = IMAGE_Y + IMAGE_HEIGHT / 2.0f;

    const Vector2 frontLeftCenter{
        imageCenterX - 250.0f,
        imageCenterY - 180.0f
    };

    const Vector2 frontRightCenter{
        imageCenterX + 250.0f,
        imageCenterY - 180.0f
    };

    const Vector2 rearLeftCenter{
        imageCenterX - 250.0f,
        imageCenterY + 180.0f
    };

    const Vector2 rearRightCenter{
        imageCenterX + 250.0f,
        imageCenterY + 180.0f
    };

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
            IMAGE_X,
            IMAGE_Y,
            IMAGE_WIDTH,
            IMAGE_HEIGHT
        };

        DrawTexturePro(
            parkingView,
            source,
            destination,
            Vector2{0.0f, 0.0f},
            0.0f,
            WHITE
        );

        drawSensorArcs(
            frontLeftCenter,
            210.0f,
            330.0f,
            SENSOR_COLOR
        );

        drawSensorArcs(
            frontRightCenter,
            210.0f,
            330.0f,
            SENSOR_COLOR
        );

        drawSensorArcs(
            rearLeftCenter,
            30.0f,
            150.0f,
            SENSOR_COLOR
        );

        drawSensorArcs(
            rearRightCenter,
            30.0f,
            150.0f,
            SENSOR_COLOR
        );

        EndDrawing();
    }

    UnloadTexture(parkingView);
    CloseWindow();
}

/*void runVisualizer() {
    const int screenWidth = 924;
    const int screenHeight = 615;

    InitWindow(screenWidth, screenHeight, "Parking Sensor Visualizer");
    SetTargetFPS(60);

    Texture2D parkingView = LoadTexture("../assets/parking_view.png");

    while (!WindowShouldClose()) {
        BeginDrawing();

        //immagine di sfondo
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

        //accensione sensore
        Vector2 frontLeftCenter{
            258.0f,
            104.0f
        };

        Color sensorColor{
            255,
            0,
            0,
            180
        };

        DrawRingLines(
            frontLeftCenter,
            80.0f,
            90.0f,
            197.0f,
            250.0f,
            32,
            sensorColor
        );

        EndDrawing();
    }

    UnloadTexture(parkingView);
    CloseWindow();
}*/