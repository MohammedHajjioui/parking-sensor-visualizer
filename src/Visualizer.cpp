//
// Created by Momo on 23/09/2026.
//

#include "Visualizer.h"

#include <array>
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

    constexpr int ARC_SEGMENTS = 42;

    const Color SENSOR_COLOR{255, 255, 255, 220};
}

void drawSensorArcs(Vector2 center, float startAngle, float endAngle, Color color);
bool drawSensorArcs2(const Sensor& sensor, Vector2 center, float startAngle, float endAngle);
float getSensorColor(AlertLevel level);

void runVisualizer(std::array<Sensor, SENSOR_COUNT>& sensors) {
    InitWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Parking Sensor Visualizer");
    SetTargetFPS(60);
    Texture2D parkingView = LoadTexture("../assets/parking_view.png");

    //drawing of sensors
    const Vector2 frontLeftCenter{
        420.0f,
        140.0f
    };

    const Vector2 frontRightCenter{
        490.0f,
        140.0f
    };

    const Vector2 rearLeftCenter{
        420.0f,
        460.0f
    };

    const Vector2 rearRightCenter{
        490.0f,
        460.0f
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
            180.0f,
            270.0f,
            SENSOR_COLOR
        );

        drawSensorArcs(
            frontRightCenter,
            270.0f,
            360.0f,
            SENSOR_COLOR
        );

        drawSensorArcs(
            rearLeftCenter,
            90.0f,
            180.0f,
            SENSOR_COLOR
        );

        drawSensorArcs(
            rearRightCenter,
            360.0f,
            445.0f,
            SENSOR_COLOR
        );

        //new code


        drawSensorArcs2(sensors[0],
            frontLeftCenter,
            180.0f,
            270.0f
        );

        drawSensorArcs2(
            sensors[1],
            frontRightCenter,
            270.0f,
            360.0f
        );

        drawSensorArcs2(
            sensors[2],
            rearLeftCenter,
            90.0f,
            180.0f
        );

        drawSensorArcs2(
            sensors[3],
            rearRightCenter,
            360.0f,
            445.0f
        );


        EndDrawing();
    }

    UnloadTexture(parkingView);
    CloseWindow();
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

bool drawSensorArcs2(const Sensor& sensor, Vector2 center, float startAngle, float endAngle) {
    constexpr float ARC_SPACING = 22.0f;
    float numOfRed = getSensorColor(sensor.getAlertLevel());
    if (numOfRed < 0 || numOfRed > 4)
        return false;

    float i=0 ;
    while ( i < 4.0f - numOfRed) {
        const float innerRadius = ARC_INNER_RADIUS + i * ARC_SPACING;
        const float outerRadius = ARC_OUTER_RADIUS + i * ARC_SPACING;

        DrawRing(
        center,
        innerRadius,
        outerRadius,
        startAngle,
        endAngle,
        ARC_SEGMENTS,
        GREEN
        );

        i++;

    }

    while ( i < 4) {
        const float innerRadius = ARC_INNER_RADIUS + i * ARC_SPACING;
        const float outerRadius = ARC_OUTER_RADIUS + i * ARC_SPACING;

        DrawRing(
        center,
        innerRadius,
        outerRadius,
        startAngle,
        endAngle,
        ARC_SEGMENTS,
        RED
        );

        i++;
    }
    return true;
}

float getSensorColor(const AlertLevel level) {
    switch (level) {
        case AlertLevel::Safe:
            return 0;

        case AlertLevel::ObstacleDetected:
            return 1;

        case AlertLevel::Warning:
            return 2;

        case AlertLevel::Brake:
            return 3;

        case AlertLevel::Stop:
            return 4;

        case AlertLevel::NotDetected:
            return 5;
    }
    return -1;
}
