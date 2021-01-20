#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

void gotoXY(int x, int y);
int whereX();
int whereY();
void Nocursortype();
void SetColor(int ForgC);
class Snake;


class Game
{
public:
    int width, height;
    int x, y;
    void drawWall();
    void stateTable();
    void showInfo();
    void showHint();

    void showInstructions();
    void scorebar();
};

class Bait
{
public:
    int baitx, baity , type;
    void appear();
    void disAppear();
    friend class Snake;
};

class Dodge
{
public:
    int dodx[77] , dody[77], dsize;
    void drawVertical(int x , int y,int in);
    void drawHorizontal(int x, int y,int in);
    void appear();
    void disapear();
    friend class Snake;
};



void Dodge::drawHorizontal(int x , int y,int in){
        gotoXY(x,y);
        SetColor(3);
        for(int i = 0 ; i < 7 ;i++){
        dodx[in] = whereX();
        dody[in] = whereY();
        cout<<"x";
        in++;
    }
    dsize = in - 1;
}

void Dodge::drawVertical(int x , int y,int in){
    gotoXY(x,y);
    for(int i = 0 ; i < 4 ; i++){
        dodx[in] = whereX();
        dody[in] = whereY();
        cout<<"x";
        in++;
        gotoXY(whereX()-1,whereY()+1);
    }
    dsize = in - 1;
}
void Dodge::appear(){
    dsize = 0;
    drawHorizontal(5,3,0);
    drawHorizontal(56,3,7);
    drawVertical(5,4,14);
    drawVertical(62,4,18);
    drawHorizontal(27,7,22);
    drawHorizontal(34,7,30);
    drawHorizontal(27,13,38);
    drawHorizontal(34,13,46);
    drawVertical(5,12,54);
    drawVertical(62,12,58);
    drawHorizontal(5,16,62);
    drawHorizontal(56,16,70);
}
class Snake
{
public:
    int dotx[30], doty[30], length, direct , dietime;
    float speed ;
    static int score;
    Game g;
    Bait b;
    Dodge d;
    void born();
    void drawSnake();
    void drawBlank();
    void direction();
    void moving();
    int eat();
    int die();
    int suicide();
    int hitWall();
    int notAppear();
    int baitInWall();
    int showScore();
    int winning();
    void ingame();

};


void Game::drawWall()
{
    width = 35, height = 20;
    SetColor(2);
    for(int i = 1; i<=height; i++)
    {
        for(int j = 1; j<=width; j++)
        {
            if(i>1 && i <height && j>1 && j<width)
            {
                cout<<"  ";
            }
            else
            {
                cout<<"# ";
            }
        }
        cout<<endl;
    }
    SetColor(15);

}
void Game::stateTable()
{
    SetColor(2);

    gotoXY(31,4);
    cout<<"Snake C++";
    gotoXY(31,9);
    cout<<"Start game";
    gotoXY(31,whereY()+2);
    cout<<"Info";
    gotoXY(31,whereY()+2);
    cout<<"Instruction";
    gotoXY(31,whereY()+2);
    cout<<"Quit";
    SetColor(15);
}

void Game::showInfo()
{
    SetColor(3);
    gotoXY(18,3);
    cout<<"Creator: Quy Long Nguyen";
    gotoXY(18,5);
    cout<<"Class  : KTPM2-K13-Haui";
    gotoXY(18,7);
    cout<<"Email  : longvip1810@gmail.com";
    gotoXY(18,9);
    cout<<"Fb     : https://bom.to/LwkewY";
    SetColor(15);
}

void Game::showHint(){
    gotoXY(16,18);
    SetColor(12);
    cout<<"Press W,S to move cursor , Enter to choose";
}

void Game::showInstructions(){
    SetColor(3);
    gotoXY(3,4);
    cout<<"- Press W A S D to move Snake, Z to quit";
    gotoXY(3,5);
    cout<<"- The bait will be appear in some seconds";
    gotoXY(3,6);
    cout<<"- If the bait disappear your snake will die";
    gotoXY(3,7);
    cout<<"- Snake's length , bait's exists time will decrease ";
    gotoXY(3,8);
    cout<<"  through the time";
    gotoXY(3,9);
    cout<<"- The shorter Snake's length, the faster Snake's speed";
    gotoXY(3,10);
    cout<<"- If Snake's langth equal 1 , you win and take 2000 point!";
}


void Game::scorebar(){
    gotoXY(0,21);
    SetColor(6);
    cout<<"Score: ";
    SetColor(15);
}
void Bait::appear()
{
    srand((int)time(0));
    baitx = rand() % 65 + 1;
    baity = rand() % 17 + 1;
    gotoXY(baitx,baity);
    type = rand() % 10 + 1;
    if(type <= 8){
    SetColor(4);
    cout<<"@";
    SetColor(15);
    }
    else {
    SetColor(13);
    cout<<"$";
    SetColor(15);
    }
}

void Bait::disAppear(){
    gotoXY(baitx,baity);
    cout<<" ";
}
int  Snake::notAppear()
{
    for(int i = length-1; i>0; i--)
    {
        if(b.baitx == dotx[i] && b.baity == doty[i])
        {
            return 1;
        }
    }
}


void Snake::born()
{
    length = 29;
    speed = 50;
    dietime = 75;
    g.x = 10, g.y = 10;
    gotoXY(g.x,g.y);
    for(int i = length-1 ; i >= 0 ; i--)
    {
        dotx[i]  = g.x;
        doty[i]  = g.y;
        g.x++;
    }
}

void Snake::drawSnake()
{
    SetColor(10);
    for(int i = length - 1 ; i > 0 ; i--)
    {
        gotoXY(dotx[i],doty[i]);
        cout<<"*";
    }
    SetColor(13);
    gotoXY(dotx[0],doty[0]);
    cout<<"*";
}
void Snake::drawBlank()
{
    for(int i = length - 1 ; i >= 0 ; i--)
    {
        gotoXY(dotx[i],doty[i]);
        cout<<" ";
    }
}


void Snake::moving()
{
    for(int i = length - 1; i > 0 ; i--)
    {
        dotx[i]  = dotx[i-1];
        doty[i]  = doty[i-1];
    }
    dotx[0]  = g.x;
    doty[0]  = g.y;
}

void Snake::direction()
{
    if(direct == 0)
    {
        g.y--;
    }
    else if(direct == 1)
    {
        g.y++;
    }
    else if(direct == 2)
    {
        g.x--;
    }
    else if(direct == 3)
    {
        g.x++;
    }
}

int Snake::baitInWall(){
    for(int i=0; i<=d.dsize;i++){
        if(b.baitx == d.dodx[i] && b.baity == d.dody[i]){
            return 1;
        }
    }
}

int Snake::eat()
{
    if(dotx[0] == b.baitx && doty[0] == b.baity)
    {

        if(b.type <= 8){
        score += 10;
        }
        else if (b.type > 8) {
        score += 30;
        }
        if(score % 20 == 0){
            length--;
            speed = speed - 0.5;
            dietime = dietime - 1;
        }
        return 1;
    }

    if(Snake::notAppear() == 1)
    {
        return 1;
    }
    if(Snake::baitInWall() == 1){
        return 2;
    }
    return 0;
}
int Snake::suicide()
{
    for(int i=1; i<length; i++)
    {
        if(dotx[0] == dotx[i] && doty[0] == doty[i])
        {
            return 0;
        }
    }

}

int Snake::hitWall(){
    for(int i=0; i<=d.dsize; i++)
    {
        if(dotx[0] == d.dodx[i] && doty[0] == d.dody[i])
        {
            return 0;
        }
    }

}


int Snake::die()
{
    if((dotx[0] == 0 || dotx[0] == 68) || (doty[0] == 0 ||doty[0] == 19))
    {
        return 0;
    }

}
int Snake::winning()
{
    if(length == 3){
        score += 2000;
        return 1;
    }

    return 0;
}
int Snake::score = 0;


int Snake::showScore()
{
    gotoXY(7,21);
    cout<<"       ";
    gotoXY(7,21);
    SetColor(6);
    cout<<score;
    SetColor(15);
    return score;
}
void Snake::ingame()
{
    int stop = 0,timer = 0;
    Snake::born();
    g.scorebar();

    b.appear();

    d.appear();
    direct = 3;
    Snake::showScore();
    while(Snake::suicide() != 0 && Snake::die() != 0 && Snake::hitWall() != 0 && stop == 0)
    {
        Snake::drawBlank();
        if(Snake::eat() == 1)
        {

            timer = 0;
            Snake::showScore();
            b.appear();
        }
        if(Snake::eat() == 2){
            timer = 0;
            d.appear();
            b.appear();
        }
        if(b.type > 0 && b.type <= 8){
            timer++;
            if(timer == dietime + 50){
                stop = 1;
            }
        }
        else if(b.type > 8){
            timer++;
            if(timer == dietime + 70 ){
                stop = 1;
            }
        }
        if(Snake::winning() == 1 || Snake::winning() == 2){
            stop = 1;
        }
        Snake::moving();
        Snake::drawSnake();
        if(direct == 0 || direct == 1)
        {
            Sleep(speed);
        }
        else
        {
            Sleep(speed - 10);
        }
        if(kbhit())
        {
            char key = getch();
            if(key == 'w' && direct != 1)
            {
                direct = 0;
            }
            else if(key == 's' && direct != 0)
            {
                direct = 1;
            }
            else if(key == 'a'&& direct != 3)
            {
                direct = 2;
            }
            else if(key == 'd' && direct != 2 )
            {
                direct = 3;
            }
            else if (key == 'z'){
                stop = 1;
            }
        }
        direction();
    }
}
class point{
public:
    int x , y;
    void born();
    void drawBlank();
    void drawPoint();
    void moveing();
};

void point::born(){
    x = 28 , y = 9;
    SetColor(2);
    gotoXY(x,y);
    cout<<">>";
}
void point::drawBlank(){
    gotoXY(x,y);
    cout<<"  ";
}
void point::drawPoint(){
    SetColor(2);
    gotoXY(x,y);
    cout<<">>";
    SetColor(15);
}
void point::moveing(){
    point::born();
    char key;
    while(key != 13){
    point::drawBlank();
    if(kbhit())
    {
            key = getch();
            if(key == 'w' && whereY() > 9 )
            {

                y = y - 2;

            }
            else if(key == 's' && whereY() < 15)
            {
               y = y + 2;
            }

    }
    point::drawPoint();
    Sleep(150);
    point::drawBlank();
    Sleep(150);
    point::drawPoint();
    }
    drawBlank();
    gotoXY(x,y);
}

int main()
{
    Game g;
    Snake r;
    Nocursortype();

    point p;
    int check1 = 0 , s , check2 ;
    while(check1 == 0){
    system("cls");
    g.drawWall();


    g.showHint();
    g.stateTable();
    p.moveing();
    r.score = 0;
    s = 0 , check2 = 0;
    while(check2 == 0){
            int key = whereY();
            if(key == 9 && s == 0)
            {
                system("cls");
                g.drawWall();;
                r.ingame();
                system("cls");
                g.drawWall();
                gotoXY(0,21);
                cout<<"            ";
                gotoXY(31,6);
                SetColor(10);
                cout<<"Your score ";
                if(r.winning() == 1){
                    gotoXY(32,9);
                    cout<<"You win!";
                }
                gotoXY(34,7);
                cout<<Snake::score;

                gotoXY(24,18);
                SetColor(12);
                cout<<"Press Spacebar to continue...";
                while(check2 == 0){
                if(kbhit()){
                    char k = getch();
                    if(k == 32){
                        check2 = 1;
                        }
                    }
                }

            }
            else if(key == 11 )
            {
                system("cls");
                g.drawWall();
                gotoXY(0,21);
                cout<<"            ";
                g.showInfo();
                gotoXY(24,18);
                SetColor(12);
                system("Pause");
                s = 1;
                check2 = 1;
            }
            else if(key == 13)
            {
                system("cls");
                g.drawWall();
                cout<<"            ";
                g.showInstructions();
                gotoXY(24,18);
                SetColor(12);
                system("Pause");
                check2 = 1;
            }
            else if(key == 15 && s == 0)
            {
                    system("cls");
                    check1 = 2;
                    check2 = 1;
            }
        }
    }

    return 0;
}

int whereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return -1;
}
//========= lay toa do y cua con tro hien tai =======
int whereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.Y;
    return -1;
}

//============== dich con tro hien tai den diem co toa do (x,y) ==========
void gotoXY(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x, y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void Nocursortype()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
 void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
