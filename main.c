#include "raylib.h"
#include <stdio.h>
#include <math.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int POINT_WIDTH = 5;
const int POINT_HEIGHT = 5;

Vector3 points[] = {
    {0.5, 0.5, 1.0},
    {-0.5, 0.5, 1.0},
    {0.5, -0.5, 1.0},
    {-0.5, -0.5, 1.0},

    {0.5, 0.5, 2.0},
    {-0.5, 0.5, 2.0},
    {0.5, -0.5, 2.0},
    {-0.5, -0.5, 2.0},
};

float cz = 1.5;

int point_lines[][2] = {
    {0, 1},
    {0, 2},
    {1, 3},
    {2, 3},

    {4, 5},
    {4, 6},
    {5, 7},
    {6, 7},

    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7}
};

// Take a cartesian point {x,y} in {[-1,1], [-1,1]}
// and convert to a screen point
Vector2 ScreenPoint(Vector2 point) {
    Vector2 out;
    out.x = (point.x + 1.0) / 2.0 * SCREEN_WIDTH;
    out.y = (point.y + 1.0) / 2.0 * SCREEN_HEIGHT;
    return out;
}

Vector2 ProjectPoint(Vector3 point) {
    return (Vector2){
        point.x / point.z,
        point.y / point.z
    };
}

void DrawPoint(Vector2 point){
    DrawRectangle(point.x - (float)POINT_WIDTH / 2, point.y - (float)POINT_HEIGHT / 2, POINT_WIDTH, POINT_HEIGHT, GREEN);
}

void MovePoint(Vector3 *point, Vector3 displacement){
    (*point).x += displacement.x;
    (*point).y += displacement.y;
    (*point).z += displacement.z;
}

void RotateOnY(Vector3 *point, float theta, float center_z) {
    float c = cos(theta);
    float s = sin(theta);
    float x_ = (*point).x;
    float z_ = (*point).z - center_z;

    (*point).x = x_ * c - z_ * s;
    (*point).z = x_ * s + z_ * c + center_z;
}

void DrawLines() {
    size_t numlines = sizeof(point_lines) / sizeof(point_lines[0]);
    for (size_t i = 0; i < numlines; i++) {
        Vector2 p1 = ScreenPoint(ProjectPoint(points[point_lines[i][0]]));
        Vector2 p2 = ScreenPoint(ProjectPoint(points[point_lines[i][1]]));
        DrawLine(p1.x, p1.y, p2.x, p2.y, GREEN);
    }
}

void MovePoints(Vector3 d) {
    cz += d.z;
    size_t num_points = sizeof(points) / sizeof(points[0]);
    for (size_t i = 0; i < num_points; i++) {
        MovePoint(&points[i], (Vector3){d.x, d.y, d.z});
    }
}

void RotatePoints(float theta) {
    size_t num_points = sizeof(points) / sizeof(points[0]);
    for (size_t i = 0; i < num_points; i++) {
        RotateOnY(&points[i], theta, cz);
    }
}

void Draw() {
    BeginDrawing();
        ClearBackground(BLACK);
        // MovePoints((Vector3){0.0, 0.0, GetFrameTime()/3.0});
        RotatePoints(GetFrameTime());
        DrawLines();
    EndDrawing();
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3d-test");

    while (!WindowShouldClose()) {
        Draw();
    }

    CloseWindow();

    return 0;
}
