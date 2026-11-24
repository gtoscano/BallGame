// Ball — Qt version. Arrow keys move the ball, ESC quits.
// If the ball leaves the window, it is painted outside the visible area: it disappears.
#include <QApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QWidget>

class BallWindow : public QWidget {
public:
    BallWindow() {
        setWindowTitle("Ball");
        setFixedSize(800, 450);
    }

protected:
    // Qt calls this whenever the window must be painted
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.fillRect(rect(), Qt::black);
        painter.fillRect(300, 400, 200, 20, Qt::blue);        // the bar: x, y, w, h

        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::red);
        painter.drawEllipse(QPoint(ballX, ballY), 20, 20);    // the ball

        painter.setPen(Qt::white);
        painter.drawText(10, 20, QString("Ball at (%1, %2)").arg(ballX).arg(ballY));
    }

    // Qt calls this when a key is pressed (and repeats it while held)
    void keyPressEvent(QKeyEvent* event) override {
        if (event->key() == Qt::Key_Up)     ballY -= 10;
        if (event->key() == Qt::Key_Down)   ballY += 10;
        if (event->key() == Qt::Key_Left)   ballX -= 10;
        if (event->key() == Qt::Key_Right)  ballX += 10;
        if (event->key() == Qt::Key_Escape) close();
        update();   // ask Qt to call paintEvent() again
    }

private:
    int ballX = 400;   // start in the middle
    int ballY = 225;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    BallWindow window;
    window.show();
    return app.exec();
}

// TRY THIS (inside paintEvent):
// 1. Draw 5 balls in a row:  for (int i = 0; i < 5; ++i) painter.drawEllipse(QPoint(100 + i * 60, 100), 20, 20);
// 2. Draw a wall of bricks with two nested for loops (rows and columns).
// 3. Use a different color for each ball: QColor::fromHsv(i * 60, 255, 255).
// 4. Change the ball's color when it touches the bar.
// 5. Make the ball come back on the other side when it leaves the window.
