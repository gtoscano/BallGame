// Ball — raylib version. Arrow keys move the ball, ESC quits.
// If the ball leaves the window, it is drawn outside the visible area: it disappears.
#include <raylib.h>

int main() {
    const int width  = 800;
    const int height = 450;
    InitWindow(width, height, "Ball");
    SetTargetFPS(60);

    float ballX = width / 2.0f;     // start in the middle
    float ballY = height / 2.0f;

    while (!WindowShouldClose()) {
        // 1. input: move while the key is held
        if (IsKeyDown(KEY_UP))    ballY -= 4;
        if (IsKeyDown(KEY_DOWN))  ballY += 4;
        if (IsKeyDown(KEY_LEFT))  ballX -= 4;
        if (IsKeyDown(KEY_RIGHT)) ballX += 4;

        // 2. paint
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(300, 400, 200, 20, BLUE);                   // the bar: x, y, w, h
        DrawCircle(static_cast<int>(ballX), static_cast<int>(ballY), 20, RED);   // the ball
        DrawText(TextFormat("Ball at (%.0f, %.0f)", ballX, ballY), 10, 10, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// TRY THIS:
// 1. Draw 5 balls in a row:  for (int i = 0; i < 5; ++i) DrawCircle(100 + i * 60, 100, 20, YELLOW);
// 2. Draw a wall of bricks with two nested for loops (rows and columns).
// 3. Change the ball's color when it touches the bar.
// 4. Make the ball come back on the other side when it leaves the window.
// 5. Move the bar with A / D.
