// Ball — iostream version. Type w/a/s/d + Enter to move the ball, q to quit.
// The screen is drawn with two for loops: one for the rows, one for the columns.
// If the ball leaves the grid, the loops never reach its position: it disappears.
#include <iostream>

constexpr int width  = 20;
constexpr int height = 10;

void draw(int ballX, int ballY) {
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            bool isBall = (col == ballX && row == ballY);
            bool isBar  = (row == height - 1 && col >= 5 && col < 15);   // the bar

            if (isBall)     std::cout << 'O';
            else if (isBar) std::cout << '=';
            else            std::cout << '.';
        }
        std::cout << '\n';
    }
    std::cout << "Ball at (" << ballX << ", " << ballY << ")\n";
}

int main() {
    int ballX = width / 2;     // start in the middle
    int ballY = height / 2;
    char key = ' ';

    while (key != 'q') {
        draw(ballX, ballY);
        std::cout << "w/a/s/d + Enter to move, q to quit: ";
        if (!(std::cin >> key)) break;

        if (key == 'w') --ballY;
        if (key == 's') ++ballY;
        if (key == 'a') --ballX;
        if (key == 'd') ++ballX;
    }
    return 0;
}

// TRY THIS:
// 1. Draw a second bar at the top (row == 0).
// 2. Draw a border: '#' when row == 0, row == height - 1, col == 0 or col == width - 1.
// 3. Draw a diagonal line: '\\' when row == col.
// 4. Stop the ball at the edges instead of letting it disappear.
// 5. Make the ball come back on the other side (wrap around).
