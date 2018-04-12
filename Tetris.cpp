#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include <vector>
#include "ColorDisplay.h"

using namespace std;

#define _console_header
#define consoleWidth 80
#define consoleHeight 25

#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1


//--------------------------------------------------------


ColorDisplay::ColorDisplay( short _xScreeSize , short _yScreenSize , COORD _origin )
{
    outConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    origin = _origin;
    xScreenSize = _xScreeSize;
    yScreenSize = _yScreenSize;
}

void ColorDisplay::setColorCharacterAtPosition( const ColorCharacter & colorchar , const COORD & position)
{
    DWORD garbage = 0;
    FillConsoleOutputCharacter(outConsole, colorchar.character, 1, position, &garbage);
    FillConsoleOutputAttribute(outConsole, colorchar.color, 1, position, &garbage);
}

void ColorDisplay::setColorCharacterAtPosition( const ColorCharacter & colorchar , short xPosition , short yPosition )
{
    COORD position = { xPosition , yPosition };
    setColorCharacterAtPosition(colorchar, position);
}

void ColorDisplay::resetDisplay()
{
    DWORD garbage = 0;
    COORD pos;
    ColorCharacter cc; cc.color = BRIGHT_WHITE;

    pos.X = origin.X; pos.Y = origin.Y - 1; cc.character = 196;
    FillConsoleOutputCharacter(outConsole, cc.character, xScreenSize, pos, &garbage);
    FillConsoleOutputAttribute(outConsole, cc.color, xScreenSize, pos, &garbage);

    pos.X = origin.X - 1; pos.Y = origin.Y - 1; cc.character = 218;
    setColorCharacterAtPosition(cc, pos);

    pos.X = origin.X + xScreenSize; pos.Y = origin.Y - 1; cc.character = 191;
    setColorCharacterAtPosition(cc, pos);

    pos.X = origin.X; pos.Y = origin.Y + yScreenSize; cc.character = 196;
    FillConsoleOutputCharacter(outConsole, cc.character, xScreenSize, pos, &garbage);
    FillConsoleOutputAttribute(outConsole, cc.color, xScreenSize, pos, &garbage);

    pos.X = origin.X - 1; pos.Y = origin.Y + yScreenSize; cc.character = 192;
    setColorCharacterAtPosition(cc, pos);

    pos.X = origin.X + xScreenSize; pos.Y = origin.Y + yScreenSize; cc.character = 217;
    setColorCharacterAtPosition(cc, pos);

    cc.character = 179;
    short yPosScreen = yScreenSize + origin.Y;
    for (pos.Y = origin.Y; pos.Y < yPosScreen; pos.Y++)
    {
        pos.X = origin.X - 1;
        setColorCharacterAtPosition(cc, pos);
        pos.X = origin.X + xScreenSize;
        setColorCharacterAtPosition(cc, pos);
    }
//    pos.X = origin.X; cc.character = ' '; cc.color = BLACK * 16;
//    for (pos.Y = origin.Y; pos.Y < yPosScreen; pos.Y++)
//    {
//        FillConsoleOutputCharacter(outConsole, cc.character, xScreenSize, pos, &garbage);
//        FillConsoleOutputAttribute(outConsole, cc.color, xScreenSize, pos, &garbage);
//    }
}

void ColorDisplay::displayImage( const Image & img, const COORD & position )
{
    COORD pos;
    pos.Y = position.Y + origin.Y;
    for (unsigned short row = 0; row < img.image.size(); row++, pos.Y++)
    {
        pos.X = position.X + origin.X;
        for (unsigned short col = 0; col < img.image[row].size(); col++, pos.X++)
        {
            setColorCharacterAtPosition(img.image[row][col], pos);
        }
    }

}

void ColorDisplay::DeleteShape()
{
    DWORD garbage = 0;
    COORD pos;
    ColorCharacter ccNull,cc;
    pos.Y = origin.Y - 1;
    short yPosScreen = yScreenSize + origin.Y;
    pos.X = origin.X; ccNull.character = ' '; ccNull.color = BLACK * 16;
    cc.character = 219;
    for (pos.Y = origin.Y; pos.Y < yPosScreen; pos.Y++)
    {
        if(ReadConsoleOutputCharacter(outConsole,
                                      cc.character,
                                      xScreenSize,
                                      pos,
                                      &garbage)
           == 1)
            FillConsoleOutputCharacter(outConsole, ccNull.character, xScreenSize, pos, &garbage);
            FillConsoleOutputAttribute(outConsole, ccNull.color, xScreenSize, pos, &garbage);
    }
}


//int Rotate(int &x,int &y, int &t)
//{
//    if(_kbhit())   //Nếu bàn phím đc nhấn
//        {
//            char c= toupper(_getch());  //Lấy mã phím vừa đc bấm
//            if (c == 'W')
//                {
//
//                case 0: return y*4 + x;              // 0  độ
//                case 1: return 12 + y - (x*4);      // 90 dộ
//
//            }
//        }
//}




void MoveShape(int &x, int &t,int &y,int &z)
{
    if(_kbhit())   //Nếu bàn phím đc nhấn
            {
                char c= toupper(_getch());  //Lấy mã phím vừa đc bấm
                switch(c)
                {
                case 'A':
                    if (x>0) x--;
                    break;
                case 'D':
                    if( x<t) x++;
                    break;
                case 'S':
                    if (y+z<17)y++;
                    break;
                }
            }

}


int main ()
{

    ColorDisplay cd( 10 , 20 , {5,4} ); // ColorDisplay(x,y,pos) với x là độ dài hàng, y là độ dài cột
    COORD pos;                          // pos{x,y} với x là hoành độ, y là tung độ
    ColorCharacter cc,ccNull;                  // màu chữ
    cc.character = 219;
    cc.color = RED;
    ccNull.character = ' ';
    ccNull.color = BLACK;
    Image tShape(2,3); tShape.image[0][1] = tShape.image[1][0] = tShape.image[1][1] = tShape.image[1][2] = cc;
    tShape.image[0][0] = tShape.image[0][2] = ccNull;
    cc.color = GREEN;
    Image lShape(3,2); lShape.image[0][0] = lShape.image[1][0] = lShape.image[2][0] = lShape.image[2][1] = cc;
    lShape.image [0][1] = lShape.image[1][1] = ccNull;
    cc.color = YELLOW;
    Image iShape(1,4); iShape.image[0][0] = iShape.image[0][1] = iShape.image[0][2] = iShape.image[0][3] = cc;
    cc.color = PURPLE;
    Image sShape(2,3); sShape.image[1][0] = sShape.image[0][1] = sShape.image[1][1] = sShape.image[0][2] = cc;
    sShape.image[0][0] = sShape.image [1][2] = ccNull;
    cc.color = WHITE;
    Image zShape(2,3); zShape.image[0][0] = zShape.image[0][1] = zShape.image[1][1] = zShape.image[1][2] = cc;
    zShape.image[1][0] = zShape.image[0][2] = ccNull;
    cc.color = AQUA;
    Image jShape(3,2); jShape.image[0][1] = jShape.image[1][1] = jShape.image[2][1] = jShape.image[2][0] = cc;
    jShape.image[1][0] = jShape.image[0][0] = ccNull;
    cc.color = BLUE;
    Image oShape(2,2); oShape.image[0][0] = oShape.image[1][0] = oShape.image[0][1] = oShape.image[1][1] = cc;
    Image Shape(0,0);
    int y = 0; // tọa độ y của khối ban đầu
    int x = 4; // tọa độ x của khối ban đầu
    int t,z = 0;     // biến để trành chạm thành phải
    srand (time(NULL));
    switch(rand()%7+1)
        {
            case 1:
                Shape = tShape;
                t = 7;
                z = 0;
                break;
            case 2:
                Shape = oShape;
                t = 8;
                z = 0;
                break;
            case 3:
                Shape = zShape;
                t = 7;
                z = 0;
                break;
            case 4:
                Shape = jShape;
                t = 8;
                z = 1;
                break;
            case 5:
                Shape = lShape;
                t = 8;
                z = 1;
                break;
            case 6:
                Shape = sShape;
                t = 7;
                z = 0;
                break;
            case 7:
                Shape = iShape;
                t = 6;
                z = -1;
                break;
        }
    cd.resetDisplay();
    while (true)
    {

        if (y+z==19)
            {
            x=4;
            y=0;
            switch(rand()%7+1)
                {
                case 1:
                    Shape = tShape;
                    t = 7;z = 0;
                    break;
                case 2:
                    Shape = oShape;
                    t = 8;z = 0;
                    break;
                case 3:
                    Shape = zShape;
                    t = 7;z = 0;
                    break;
                case 4:
                    Shape = jShape;
                    t = 8;
                    z = 1;
                    break;
                case 5:
                    Shape = lShape;
                    t = 8;
                    z = 1;
                    break;
                case 6:
                    Shape = sShape;
                    t = 7;z = 0;
                    break;
                case 7:
                    Shape = iShape;
                    t = 6;z = -1;
                    break;
                }
            }
            else cd.DeleteShape();
        cd.resetDisplay();
        MoveShape(x,t,y,z);
//        Rotate(x,y,t);
        pos = {x,y};
        cd.displayImage(Shape, pos);
        if (y<20) y++;
        Sleep(200);
    }

}








