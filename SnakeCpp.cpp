#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <ctime>


using namespace std;

bool gameover;
const int width = 20, height = 20;
int x, y, fruitx, fruity, score, ntail;
int tailx[100], taily[100];
enum edirection { STOP = 0, UP, DOWN, RIGHT, LEFT };
edirection dir;

void delaySeconds(int seconds) {
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(seconds);
    while (std::chrono::steady_clock::now() < endTime) {
    }
}

void setup()
{
    srand(time(0));
    gameover = false;
    dir = STOP;
    x = width / 2 - 1;
    y = height / 2 - 1;
    fruitx = rand() % (width - 2);
    fruity = rand() % height;
    score = 0;
}

void display()
{
    system("cls");
    for (int i = 0; i < width + 1; i++)
        cout << "# ";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 or j == width - 1)
                cout << "# ";
            if (i == y and j == x)
                cout << "0 ";
            else if (i == fruity and j == fruitx)
                cout << "F ";
            else
            {
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (tailx[k] == j and taily[k] == i)
                    {
                        print = true;
                        cout << "o ";
                    }
                }

                if (!print)
                {
                    cout << "  ";
                }
            }



        }
        cout << endl;
    }

    for (int i = 0; i < width + 1; i++)
        cout << "# ";
    cout << endl;
    cout << "Score: " << score << endl;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'x':
            gameover = true;
            break;

        }
    }

}

void logic()
{
    int prevx = tailx[0], prevy = taily[0], prev2x, prev2y;
    tailx[0] = x; taily[0] = y;
    for (int i = 1; i < ntail; i++)
    {
        prev2x = tailx[i];
        prev2y = taily[i];
        tailx[i] = prevx;
        taily[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;

    }

    switch (dir)
    {
    case UP:
        y--;
        break;
    case LEFT:
        x--;
        break;
    case DOWN:
        y++;
        break;
    case RIGHT:
        x++;
        break;
    }
    // if (y > height or y < 0 or x > width or x < 0)
    //     gameover = true;
    if (x >= width - 1)
        x = 0;
    else if (x < 0)
        x = width - 2;

    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 2;


    for (int i = 0; i < ntail; i++)
    {
        if (tailx[i] == x and taily[i] == y)
            gameover = true;

    }


    if (y == fruity and x == fruitx)
    {
        score += 10;
        fruitx = rand() % (width - 2);
        fruity = rand() % height;
        ntail++;
    }


}


int main() {


    setup();
    while (!gameover)
    {

        thread th(display);
        input();
        logic();
        delaySeconds(80);
        th.join();
    }



    return 0;
}
