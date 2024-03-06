#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
enum ConsoleColor {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Yellow = 6,
    White = 7,
    Gray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    LightYellow = 14,
    BrightWhite = 15
};
using namespace std;
const char Enter = 13;
const char UP    = 72;
const char DOWN = 80;
const char RIGHT = 77;
const char LEFT = 75;
const char PAUSE = 37;
const int FieldY = 25;
const int FieldX = 80;
int maxMoves = 0;

char FootballField[FieldY][FieldX];
void CursorZeroCoordinates() 
{
COORD position = { 0,0 }; //позиция x и y
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(hConsole, position);
}
void FieldRendering()
{
    
    CursorZeroCoordinates();
    for (int k = 0; k < FieldX + 2; k++)
    {
        cout << "-";
    }
    cout << "\n";
    for (int i = 0; i < FieldY; i++)
    {
        cout << "|";
        for (int j = 0; j < FieldX; j++)
        {
            cout << FootballField[i][j];
        }
        cout << "|";
        cout << "\n";
    }
    for (int k = 0; k < FieldX + 2; k++)
    {
        cout << "-";
    }
    cout << "\n";
}

void PlayerMovementRendering(int lastX, int lastY, int X, int Y, char symbol)
{
    FootballField[lastY][lastX] = ' ';
    FootballField[Y][X] = symbol;
    FieldRendering();
}
class FootballPlayer
{
private:
int horizontallyX;
int verticallyY;
public:
bool FlagBall;
char texstur;
public:
    FootballPlayer() {}
    FootballPlayer(int x,int y) 
    {
        horizontallyX = x;
        verticallyY = y;
        FlagBall = false;
    }
public :
       int GetX()
       {
           return horizontallyX;
       }
    void SetX(int x)
       {
           if (x < 80 && x >= 0)
               horizontallyX = x;
           else if (x >= 80)
               horizontallyX = 79;
           else
               horizontallyX = 0;
       }


       int GetY()
       {
           return verticallyY;
       }
       void SetY(int y)
       {
           if (y < 25 && y >= 0)
               verticallyY = y;
           else if (y >= 25)
               verticallyY = 24;
           else
               verticallyY = 0;
       }
};
FootballPlayer FirstTeam[11];
FootballPlayer SecondTeam[11];
bool CheckingForObstacles(int y, int x)
{
    if (FootballField[y][x] == ' ')
    {
        return true;
    }
    else
    {
        return false;
    }
}
void kickTheBall()
{

}
void MovingPlayer(FootballPlayer& player)
{
    char lastSymbol = ' ';
    char symbol;
    char in;
    bool flag = true;
    while (flag)
    {
        int CurrentPositionX = player.GetX();
        int CurrentPositionY = player.GetY();
        symbol = FootballField[CurrentPositionY][CurrentPositionX];
        in = _getch();
        switch (in) {
        case UP:
            if (CheckingForObstacles(player.GetY() - 1, player.GetX()))
            player.SetY(player.GetY() - 1);
            flag = false;
            break;
        case DOWN:
            if (CheckingForObstacles(player.GetY() + 1, player.GetX()))
            player.SetY(player.GetY() + 1);
            flag = false;
            break;
        case RIGHT:
            if (CheckingForObstacles(player.GetY(), player.GetX() + 1))
            player.SetX(player.GetX() + 1);
            flag = false;
            break;
        case LEFT:
            if(CheckingForObstacles(player.GetY(), player.GetX() - 1))
            player.SetX(player.GetX() - 1);
            flag = false;
            break;
        //case PAUSE:
            //if (player.FlagBall == true) 
            //{
            //    kickTheBall();
            //}
        }
        
        PlayerMovementRendering(CurrentPositionX, CurrentPositionY, player.GetX(), player.GetY(), symbol);
    }

}
void CreateFields() 
{
    for (int y = 0; y < FieldY; y++)
    {
        for (int x = 0; x < FieldX; x++)
        {
            if (y >= 10 && y < 15 && (x == 2 || x == 78))
            {
                FootballField[y][x] = '|';
                continue;
            }
            if ((y == 9 || y == 15) && (x == 3 || x == 77 || x == 4 || x == 76 || x == 2 || x == 78))
            {
                FootballField[y][x] = '~';
                continue;
            }
            if(x == 39)
            {
            FootballField[y][x] = '|';
            continue;
            }

            FootballField[y][x] = ' ';
        }
    }
}
void SelectStandardLocation(FootballPlayer(&player)[11], char symbol)
{   

    char in;
    bool flag = true;
    for (int i = 0; i < 10; i++)
    {
        while (flag)
        {
         int CurrentPositionX = player[i].GetX();
          int CurrentPositionY = player[i].GetY();

            in = _getch();
            switch (in) {
            case UP:
                if (CheckingForObstacles(player[i].GetY() - 1, player[i].GetX()))
                    player[i].SetY(player[i].GetY() - 1);

                break;
            case DOWN:
                if (CheckingForObstacles(player[i].GetY() + 1, player[i].GetX()))
                    player[i].SetY(player[i].GetY() + 1);
                break;
            case RIGHT:
                if (CheckingForObstacles(player[i].GetY(), player[i].GetX() + 1))
                    player[i].SetX(player[i].GetX() + 1);
                break;
            case LEFT:
                if (CheckingForObstacles(player[i].GetY(), player[i].GetX() - 1))
                    player[i].SetX(player[i].GetX() - 1);
                break;
            case Enter:
                flag = false;
                break;

            }
            PlayerMovementRendering(CurrentPositionX,CurrentPositionY,player[i].GetX(), player[i].GetY(), symbol);
        }
        flag = true;
    }

}
void PrintWASD(char w, char a, char s, char d)
{
    cout << "         _____         \n";
    cout << "        |     |         \n";
    cout << "        |  " << w << "  |         \n";
    cout << "        |_____|         ";
    cout << "\n";
    cout << " _____  ";
    cout << " _____  ";
    cout << " _____  ";
    cout << "\n";
    cout << "|     | ";
    cout << "|     | ";
    cout << "|     | ";
    cout << "\n";
    cout << "|  " << a << "  | ";
    cout << "|  " << s << "  | ";
    cout << "|  " << d << "  | ";
    cout << "\n";
    cout << "|_____| ";
    cout << "|_____| ";
    cout << "|_____| ";
    cout << "\n";
}
void PrintSpase()
{
    cout << " _____________________         \n";
    cout << "|                     |         \n";
    cout << "|        Space        |         \n";
    cout << "|_____________________|         ";

}
void PrintControl() 
{
    cout << "\n     Player Control\n";
    PrintWASD('W', 'A', 'S', 'D');
    cout << "\n     Player choice\n";
    PrintWASD('^', '<', '+', '>');
    cout << "\n     Kick the ball\n";
    PrintSpase();
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
}
void flipCoinAnimation() {
    std::cout << "Flipping coin..." << std::endl;

    // Задержка перед началом анимации
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Генерация случайного числа для определения результата
    srand(time(0));
    int result = rand() % 2; // 0 - орел, 1 - решка

    // Анимация переворота монетки
    for (int i = 0; i < 10; i++) {
        std::cout << "\r";

        // Вывод случайного символа для анимации
        if (rand() % 2 == 0) {
            std::cout << "Квад";
        }
        else {
            std::cout << "Круг";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Вывод результата
    std::cout << "\r";
    if (result == 0) {
        std::cout << "Квадрат" << std::endl;
    }
    else {
        std::cout << "Круг" << std::endl;
    }
}
void prit(FootballPlayer player[], char (&FootballField)[25][80], char simvol)
{
    for(int i = 0 ; i < 11; i++)
    FootballField[player[i].GetY()][player[i].GetX()] = simvol;
}
void StandardPlayerArrangement(FootballPlayer FirstTeam[],FootballPlayer SecondTeam[])
{
    for (int i = 0; i < 10; i++)
    {
        FirstTeam[i].SetX(38);
        FirstTeam[i].SetY(7 + i);
        FirstTeam[i].texstur = '(';
    }
        FirstTeam[10].texstur = '(';
    FirstTeam[10].SetX(4);
    FirstTeam[10].SetY(12);
    for (int i = 0; i < 10; i++)
    {
        SecondTeam[i].SetX(40);
        SecondTeam[i].SetY(7 + i);
        SecondTeam[i] .texstur = ']';
    }
        SecondTeam[10] .texstur = ']';
    SecondTeam[10].SetX(76);
    SecondTeam[10].SetY(12);

}
void FieldPreparation()
{
    CreateFields();
    StandardPlayerArrangement(FirstTeam, SecondTeam);
    prit(FirstTeam, FootballField, '(');
    prit(SecondTeam, FootballField, ']');
    FieldRendering();
    SelectStandardLocation(FirstTeam, '(');
    SelectStandardLocation(SecondTeam, ']');
    for (int i = 0; i < 25; i++)
    {
        FootballField[i][39] = ' ';

    }
    FootballField[12][39] = '*';
    FieldRendering();
}
void HideCursor()
{
    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &structCursorInfo);
}
void SetColor(int text, int bg) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}
void WhatPlayer(FootballPlayer player)
{
    //system("cls");
    CursorZeroCoordinates();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    for (int k = 0; k < FieldX + 2; k++)
    {
        cout << "-";
    }
    cout << "\n";
    for (int i = 0; i < FieldY; i++)
    {
        cout << "|";
        for (int j = 0; j < FieldX; j++)
        {
            if (player.GetX() == j && player.GetY() == i)
            {
                SetConsoleTextAttribute(hConsole, ConsoleColor(1));
                cout << player.texstur;
                SetConsoleTextAttribute(hConsole, ConsoleColor(White));
                
            }
            else
            {
            cout << FootballField[i][j];
            }
        }
        cout << "|";
        cout << "\n";
    }
    for (int k = 0; k < FieldX + 2; k++)
    {
        cout << "-";
    }
    cout << "\n";
}
int PlayerMove(FootballPlayer FirstTeam[]) 
{
    char in;
    bool flag = true;
    int number = 0;
    while (flag)
    {
        WhatPlayer(FirstTeam[number]);

        ;
        in = _getch();
        switch (in) {
        case DOWN:
            if (number == 10)
            {
                number = 0;
            }else
            {
                number++;
            
            }
            break;
        case UP:
            if (number == 0)
            {
                number = 10;
            }
            else
            {
                number--;
                

            }
            break;
        case Enter:
            flag = false;
            break;
        }

    }
    return number;
}
void renderingNumberMovesLeft(int number)
{
    if (number >= 2)
        cout << "осталось : " << number << " ходов";
    else
        cout << "ход противника";


    
}
void PlayerMakesSeveralMoves(FootballPlayer FirstTeam[],int number)
{
char in;
maxMoves = 30;
bool flag = true;
while (flag)
{
    renderingNumberMovesLeft(maxMoves);
    MovingPlayer(FirstTeam[number]);
    maxMoves--;
    in = _getch();
    if (in == Enter || maxMoves <= 0)
    {
        flag = false;
    }
}
}
int main()
{
    bool flagWin = false;
    int number;
    bool flagWhoseMove = true;
    setlocale(LC_ALL, "Russian");
    HideCursor();
    FieldPreparation();
    while (!flagWin)
    {
        if (flagWhoseMove)
        {
            number = PlayerMove(FirstTeam);
            PlayerMakesSeveralMoves(FirstTeam, number);
            flagWhoseMove = false;
        }
        else
        {
            number = PlayerMove(SecondTeam);
            PlayerMakesSeveralMoves(SecondTeam, number);
            flagWhoseMove = true;
        }

    }
    /*
    flipCoinAnimation();
    PrintControl();
    printf("press any key");
    _getch();
    */

    return 0;
}


