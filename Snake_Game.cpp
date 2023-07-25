#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

void setUp(Direction *dir, int *headX, int *headY, int width, int height, int *fruitX, int *fruitY, int *score)
{
    *dir = STOP;
    *headX = width / 2;
    *headY = height / 2;
    srand(time(0));
    *fruitX = rand() % width;
    *fruitY = rand() % height;
    *score = 0;
}

void draw(int *headX, int *headY, int width, int height, int *fruitX, int *fruitY, int *score, int *tailLength, int tailX[], int tailY[])
{
    system("cls");
    // upper border
    cout << "\t\t";
    for (int i = 0; i < (width - 8); i++)
        cout << "||";
    cout << endl;

    // snake,fruit,space and side borders
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // left border
            if (j == 0)
                cout << "\t\t||";
            // snake head
            if ((i == (*headY)) && (j == (*headX)))
                cout << "O";
            // fruit
            else if ((i == (*fruitY)) && (j == (*fruitX)))
                cout << "*";
            // space , snake tail
            else
            {
                bool print = false;
                // tail
                for (int k = 0; k < (*tailLength); k++)
                {
                    if (i == tailY[k] && j == tailX[k])
                    {
                        cout << "o";
                        print = true;
                    }
                }
                // space
                if (!print)
                    cout << " ";
            }
            // right border
            if (j == (width - 1))
                cout << "||";
        }
        cout << endl;
    }
    // lower border
    cout << "\t\t";
    for (int i = 0; i < (width - 8); i++)
        cout << "||";
    cout << "\n\t\t\tScore : " << *score;
}

void input(Direction *dir)
{
    if (_kbhit())
    {
        switch (getch())
        {
        case 'a':
            *dir = LEFT;
            break;
        case 'w':
            *dir = UP;
            break;
        case 'd':
            *dir = RIGHT;
            break;
        case 's':
            *dir = DOWN;
            break;
        default:
            break;
        }
    }
}

void logic(Direction *dir, bool *gameOver, int *headX, int *headY, int width, int height, int *fruitX, int *fruitY, int *score, int *tailLength, int tailX[], int tailY[])
{
    // tail logic
    int prevx = tailX[0], prevy = tailY[0], prev2x, prev2y;
    tailX[0] = *headX;
    tailY[0] = *headY;
    for (int i = 1; i < (*tailLength); i++)
    {
        prev2x = tailX[i];
        prev2y = tailY[i];
        tailX[i] = prevx;
        tailY[i] = prevy;
        prevx = prev2x;
        prevy = prev2y;
    }

    // direction logic
    switch ((*dir))
    {
    case UP:
        (*headY)--;
        break;
    case RIGHT:
        (*headX)++;
        break;
    case LEFT:
        (*headX)--;
        break;
    case DOWN:
        (*headY)++;
        break;
    }

    // touch walls
    if ((*headX) >= width)
        *headX = 0;
    else if ((*headX) < 0)
        *headX = width - 1;

    if ((*headY) >= height)
        *headY = 0;
    else if ((*headY) < 0)
        *headY = height - 1;

    // snake bite itself
    for (int i = 0; i < (*tailLength); i++)
    {
        if ((tailX[i] == (*headX)) && (tailY[i] == (*headY)))
            *gameOver = true;
    }

    // snake eats fruit
    if (((*headX) == (*fruitX)) && ((*headY) == (*fruitY)))
    {
        *score = *score + 10;
        *fruitX = rand() % width;
        *fruitY = rand() % height;
        *tailLength = *tailLength + 1;
    }
}

void instructions()
{
    cout << "--------------------- Instructions ---------------------\n\n";
    cout << "1) Press 'A' key to move the snake in left direction.\n2) Press 'W' key to move the snake in upward direction.\n1) Press 'S' key to move the snake in downward direction.\n1) Press 'D' key to move the snake in right direction.\n5) Try to eat the fruit in order to cool down the hunger of snake.\n6) After eating each fruit you will get '10' points.\n7) You can pass the walls and will be coming from the opposite directions of the walls at the same lane.\n8) If you try to bite a snake by itself your game will be over :(";
}

int main()
{
    char start;
    int choice;
    while (1)
    {
        Direction dir;
        bool gameOver = false;
        const int height = 20, width = 20;
        int headX = 0, headY = 0, fruitX = 0, fruitY = 0, score = 0, tailLength = 0, tailX[100], tailY[100];
        system("cls");
        cout << "******************************* SNAKE GAME *******************************\n";
        cout << "1) Start the Game\n2) Instructions\n3) Exit\nEnter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            cout << "\t-----------------------------\n";
            cout << "\t\t :Snake King:  \n";
            cout << "\t-----------------------------\n";
            cout << "Press S to start : ";
            cin >> start;
            if (start == 's' || start == 'S')
            {
                setUp(&dir, &headX, &headY, width, height, &fruitX, &fruitY, &score);
                while (!gameOver)
                {
                    draw(&headX, &headY, width, height, &fruitX, &fruitY, &score, &tailLength, tailX, tailY);
                    input(&dir);
                    logic(&dir, &gameOver, &headX, &headY, width, height, &fruitX, &fruitY, &score, &tailLength, tailX, tailY);
                    Sleep(30);
                }
            }
            cout << "\n You have bitten yourself :(\n Better luck next time :)\n Your score : " << score;
            cout << "\n\nPress any key to continue  ";
            getch();
            break;
        case 2:
            system("cls");
            instructions();
            cout << "\n\nPress any key to continue  ";
            getch();
            break;
        case 3:
            system("cls");
            cout << "Thanks for playing the game.\nI hope you enjoyed the game :)\n";
            cout << "\n\nPress any key to exit the game  ";
            getch();
            exit(0);
            break;

        default:
            cout << "Invalid Input \n";
            cout << "\n\nPress any key to exit the game  ";
            getch();
            break;
        }
    }

    return 0;
}