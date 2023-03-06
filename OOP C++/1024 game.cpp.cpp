#include <iostream>
#include <stdlib.h> 
#include <cstdlib>
#include <conio.h>
#include <iomanip>
using namespace std;
int pos[4][4] = { 0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0 };
void grid() {
    for (int i = 0; i < 4; i++) {
        cout << setw(52);
        cout << "|";
        for (int j = 0; j < 4; j++) {
            if (pos[i][j] != 0) {
                cout << pos[i][j];
                cout << "|";
            }

            else if (pos[i][j] == 0) {
                cout << " ";
                cout << "|";
            }
        }
        cout << endl;

    }

}
void ran() {
    int i = rand() % 4;
    int j = rand() % 4;
    while (pos[i][j] != 0)
    {
        int i = rand() % 4;
        int j = rand() % 4;
    }
    pos[i][j] = (rand() % 2) + 1;
}
void move() {
    char m;
    int temp = 0;
    int i = 0;
    int j = 1;
    cin >> m;
    if (m == 'l') {
        for (i = 0; i < 4; i++) {
            for (j = 1; j < 4; j++) {
                temp = j;
                while (pos[i][temp - 1] == 0 && temp > 0) {
                    pos[i][temp - 1] = pos[i][temp];
                    pos[i][temp] = 0;
                    temp--;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 1; j < 4; j++) {

                if (pos[i][j - 1] == pos[i][j] && pos[i][j] != 0) {
                    pos[i][j - 1] = (pos[i][j - 1] + pos[i][j]);
                    pos[i][j] = 0;
                }
            }

        }

    }
    if (m == 'r')
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 2; j >= 0; j--)
            {
                temp = j;
                while (temp < 3)
                {
                    if (pos[i][temp + 1] == 0)
                    {
                        pos[i][temp + 1] = pos[i][temp];
                        pos[i][temp] = 0;
                    }
                    else if (pos[i][temp + 1] == pos[i][temp])
                    {
                        pos[i][temp + 1] = pos[i][temp + 1] + pos[i][temp];
                        pos[i][temp] = 0;
                    }
                    temp++;
                }
            }
        }
    }
    if (m == 'u') {
        for (int i = 1; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                temp = i;
                while (temp > 0)
                {
                    if (pos[temp - 1][j] == 0)
                    {
                        pos[temp - 1][j] = pos[temp][j];
                        pos[temp][j] = 0;
                    }
                    else if (pos[temp - 1][j] == pos[temp][j])
                    {
                        pos[temp - 1][j] = pos[temp - 1][j] + pos[temp][j];
                        pos[temp][j] = 0;
                    }
                    temp--;
                }
            }
        }
    }

    if (m == 'd') {
        for (int i = 2; i >= 0; i--)
        {
            for (int j = 0; j < 4; j++)
            {
                temp = i;
                while (temp < 3)
                {
                    if (pos[temp + 1][j] == 0)
                    {
                        pos[temp + 1][j] = pos[temp][j];
                        pos[temp][j] = 0;
                    }
                    else if (pos[temp + 1][j] == pos[temp][j])
                    {
                        pos[temp + 1][j] = pos[temp + 1][j] + pos[temp][j];
                        pos[temp][j] = 0;
                    }
                    temp++;
                }
            }
        }
    }
}
void check() {
    int c = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (pos[i][j] == 1024) {
                cout << "Congratulation!!!YOU WON!";
                i = 3;
                break;
            }
            else if (pos[i][j] != 0) {
                c++;

            }
        }

    }
    if (c == 16) {
        cout << setw(55);
        cout << "YOU LOSE!!!" << endl;
        cout << "GAME OVER";
    }
}
int main() {
    srand(time(0));
    ran();
    ran();

    for (int i = 0; i < 123; i++) {
        cout << setw(50);
        cout << ":::::" << "1024 GAME" << ":::::" << endl;
        cout << setw(63.5);
        cout << "Press l for left" << endl;
        cout << setw(64);
        cout << "Press r for right" << endl;
        cout << setw(63);
        cout << "Press u for up" << endl;
        cout << setw(64);
        cout << "Press d for down" << endl;
        cout << "\n" << "\n" << "\n" << "\n";
        grid();
        move();
        ran();
        system("cls");

    }

    system("pause");
    return 0;
}