// Ball — ncurses version. Arrow keys move the ball, Q quits.
// If the ball leaves the terminal, ncurses simply doesn't draw it: it disappears.
#include <ncurses.h>

void drawBar(int row, int fromCol, int toCol) {
    for (int col = fromCol; col <= toCol; ++col) {
        mvaddch(row, col, '=');
    }
}

int main() {
    initscr();              // start ncurses
    cbreak();               // keys arrive immediately (no Enter needed)
    noecho();               // do not print the keys that are pressed
    curs_set(0);            // hide the cursor
    keypad(stdscr, TRUE);   // enable arrow keys

    int width, height;
    getmaxyx(stdscr, height, width);   // size of the terminal

    int ballX = width / 2;             // start in the middle
    int ballY = height / 2;
    int key = 0;

    while (key != 'q') {
        erase();                                           // clear the screen
        drawBar(height - 2, width / 2 - 10, width / 2 + 10);   // the bar
        mvaddch(ballY, ballX, 'O');                        // the ball
        mvprintw(0, 0, "Ball at (%d, %d)   Arrows: move   Q: quit", ballX, ballY);
        refresh();                                         // show it

        key = getch();                                     // wait for a key
        if (key == KEY_UP)    --ballY;
        if (key == KEY_DOWN)  ++ballY;
        if (key == KEY_LEFT)  --ballX;
        if (key == KEY_RIGHT) ++ballX;
    }

    endwin();               // give the terminal back to the shell
    return 0;
}

// TRY THIS:
// 1. Draw 5 balls in a row:      for (int i = 0; i < 5; ++i) mvaddch(5, 10 + i * 4, 'O');
// 2. Draw a vertical bar:        for (int row = 3; row < 10; ++row) mvaddch(row, 5, '|');
// 3. Draw a filled box (nested): for rows { for cols { mvaddch(row, col, '#'); } }
// 4. Draw a border around the whole terminal.
// 5. Make the ball jump 3 cells per key press.
