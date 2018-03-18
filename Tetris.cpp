#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<time.h>

using namespace std;

#define _console_header
#define consoleWidth 80
#define consoleHeight 25

#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1

#define MaxI    22  //I là hàng
#define MaxJ    10  //J là cột

#define LEFT 4
#define TOP 4
//Khoảng cách lề trái, trên



//--------------------------------------------------------


enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    PURPLE,
    GRAY,
    WHITE,
    LIGHTGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTPURPLE,
    LIGHTYELLOW,
    LIGHTWHITE
};
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void clrscr()
{
    COORD coord;
    DWORD written;
    CONSOLE_SCREEN_BUFFER_INFO info;

    coord.X = 0;
    coord.Y = 0;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
        info.dwSize.X * info.dwSize.Y, coord, &written);
    gotoxy (1, 1);
}
void textcolor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void delay(int x){ Sleep(x);}

void Nocursortype()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize=20;
    SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &Info);
}

int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return key_none;
	}

	return key_none;
}

int Board[MaxI][MaxJ];  //I là hàng, J là cột
wstring Tetromino[7];

void DrawBoard()
{
    int i,j;
    for(i=LEFT;i<=LEFT+10+1;i++)
        for(j=TOP;j<=TOP+20+1;j++)
        {
            if((j==TOP||j==TOP+20+1)&&i>LEFT&&i<LEFT+10+1)
            {
                gotoxy(i,j);
                textcolor(7);
                cout << char (205);
            }
            if((i==LEFT||i==LEFT+10+1)&&j>TOP&&j<TOP+20+1)
            {
                gotoxy(i,j);
                textcolor(7);
                cout << char (186);
            }
        }
        gotoxy(LEFT,TOP);
        textcolor(LIGHTBLUE);
        cout << char (219);
        gotoxy(LEFT+10+1,TOP);
        textcolor(LIGHTBLUE);
        cout << char (219);
        gotoxy(LEFT,TOP+20+1);
        textcolor(LIGHTBLUE);
        cout << char (219);
        gotoxy(LEFT+10+1,TOP+20+1);
        textcolor(LIGHTBLUE);
        cout << char (219);

}

int DrawTetromino()
{

}




int Rotate(int x,int y, int r) // r là góc xoay
{
    switch(r/90)
    {
        case 0: return y*4 +x;              // 0  độ
        case 1: return 12 + y - (x*4);      // 90 dộ
        case 2: return 15 - y - (x*4);      // 180 độ
        case 3: return 3  - y + (x*4);      // 270 độ
    }
    return 0;
}



int main ()
{
    	DrawBoard();
	return 0;
	
}








