#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 20;

class Helicopter {
private:
    int x, y;

public:
    Helicopter(int startX, int startY) {
        x = startX;
        y = startY;
    }

    void draw() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "H";
    }

    void erase() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
    }

    void moveUp() {
        if (y > 1)
            y--;
    }

    void moveDown() {
        if (y < SCREEN_HEIGHT - 1)
            y++;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

class Obstacle {
private:
    int x, y;

public:
    Obstacle(int startX, int startY) {
        x = startX;
        y = startY;
    }

    void draw() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "X";
    }

    void erase() {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " ";
    }

    void moveLeft() {
        if (x > 1)
            x--;
        else
            x = SCREEN_WIDTH - 2;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

class Game {
private:
    Helicopter helicopter;
    Obstacle obstacle;

    bool gameover;
    int score;

public:
    Game() : helicopter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), obstacle(SCREEN_WIDTH - 2, SCREEN_HEIGHT / 2), gameover(false), score(0) {}

    void setup() {
        system("cls");
        score = 0;
        gameover = false;
        helicopter.draw();
        obstacle.draw();
    }

    void input() {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'w' || ch == 'W')
                helicopter.moveUp();
            else if (ch == 's' || ch == 'S')
                helicopter.moveDown();
            else if (ch == 'x' || ch == 'X')
                gameover = true;
        }
    }

    void update() {
        helicopter.erase();
        helicopter.draw();

        obstacle.erase();
        obstacle.moveLeft();
        obstacle.draw();

        if (helicopter.getX() == obstacle.getX() && helicopter.getY() == obstacle.getY())
            gameover = true;

        score++;
    }

    void render() {
        COORD coord;
        coord.X = 0;
        coord.Y = SCREEN_HEIGHT + 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "Score: " << score;

        Sleep(50);
    }

    void run() {
        setup();

        while (!gameover) {
            input();
            update();
            render();
        }

        system("cls");
        cout << "Game Over! Your Score: " << score << endl;
    }
};

int main() {
    Game game;
    game.run();

    return 0;
}

