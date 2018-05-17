#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<fstream>
#include "New-Tetris-1.h"

//----------------------------------------------------------------------//
#define MaxI    24
#define MaxJ    10
int Board[MaxI][MaxJ];

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
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

//----------------------------------------------------------------------//

void DrawBoard()
{
    int i,j;
    for(i=LEFT;i<=LEFT+10+1;i++)
        for(j=TOP;j<=TOP+20+1;j++)
        {
            if((j==TOP||j==TOP+20+1)&&i>LEFT&&i<LEFT+10+1)
            {
                gotoxy(i,j);textcolor(7); cout<<char(196);
            }
            if((i==LEFT||i==LEFT+10+1)&&j>TOP&&j<TOP+20+1)
            {
                gotoxy(i,j);
                textcolor(WHITE);
                if (i==LEFT+10+1 && j == TOP +5) cout << char (195);
                else cout<<char(179);
            }
        }
    gotoxy(LEFT,TOP);textcolor(WHITE); cout<<char(218);
    gotoxy(LEFT+10+1,TOP);textcolor(WHITE); cout<<char(194);
    gotoxy(LEFT,TOP+20+1);textcolor(WHITE); cout<<char(192);
    gotoxy(LEFT+10+1,TOP+20+1);textcolor(WHITE); cout<<char(193);
    for(i=RIGHT;i<RIGHT +8;i++)
	{
		textcolor(7);
		gotoxy(i,9);
		if (i == RIGHT +8) continue;
        cout << char (196);
        gotoxy(i,TOP +20+1);
        cout << char (196);
        gotoxy(i,TOP);
        cout << char (196);

    }
    gotoxy(RIGHT+8,TOP);
    cout << char (191);
    gotoxy(RIGHT+8,TOP+5);
    cout << char (180);
    gotoxy(RIGHT+8,TOP+20+1);
    cout << char (217);
    for (i=TOP ; i< MaxI+1 ; i++)
    {
        if ( i == TOP || i == TOP + 20 +1 || i == TOP + 5) continue;
        gotoxy(RIGHT + 8,i);
        cout << char (179);
        gotoxy(80,i);
        cout << char (179);
    }

}

void UpdateBoard(int Row)
{
	int i,j;
	for(i=Row;i>0;i--)
	for(j=0;j<MaxJ;j++)
	{
		Board[i][j]=Board[i-1][j];
	}
}

void DisplayBoard()
{
    int i,j;
    for(i=0;i<MaxI;i++)
        for(j=0;j<MaxJ;j++)
        {
            if(Board[i][j]==1&&i>=4)
            {
                gotoxy(j+LEFT+1,i+TOP+1-4);textcolor(15);cout << char (2);
            }
            if(Board[i][j]==0&&i>=4)
            {
                textcolor(BLACK);gotoxy(j+LEFT+1,i+TOP+1-4);cout << " ";
            }
        }
}

KhoiGach *TaoKhoiGach(int ID)
{
    KhoiGach *pkhoigach = new KhoiGach[sizeof(KhoiGach)];
    switch(ID)
    {
    case 15:
        pkhoigach->Row=1;
        pkhoigach->Col=4;
        pkhoigach->iBoard=0;
        pkhoigach->jBoard=5;
        break;
    case 31:
        pkhoigach->Row=pkhoigach->Col=2;
        pkhoigach->iBoard=2;
        pkhoigach->jBoard=5;
        break;
    default:
        pkhoigach->Row=2;
        pkhoigach->Col=3;
        pkhoigach->iBoard=2;
        pkhoigach->jBoard=5;
        break;
    }
    pkhoigach->arr = new int*[pkhoigach->Row];
    for(int i=0;i<pkhoigach->Row;i++)
    {
        pkhoigach-> arr[i] = new int [pkhoigach->Col];
    }
    for(int k=0;k<pkhoigach->Col*pkhoigach->Row;k++)
    {
        pkhoigach->arr[k/pkhoigach->Col][k%pkhoigach->Col]=(ID>>(pkhoigach->Col*pkhoigach->Row-1-k))&1;
    }
    return pkhoigach;
}

int Inside(int i,int j) //Xem i,j có thuộc mảng Board[24][10] hay không?
{
    if (i>=0&&i<MaxI&&j>=0&&j<MaxJ) return 1;
    return 0;
}
int Left(int i,int j)
{
    if(j>0&&Inside(i,j)&&Board[i][j-1]==0) return 1;
    return 0;
}
int Right(int i,int j)
{
    if(j<MaxJ-1&&Inside(i,j)&&Board[i][j+1]==0) return 1;
    return 0;
}
int Down(int i,int j)
{
    if(i<MaxI-1&&Inside(i,j)&&Board[i+1][j]==0) return 1;
return 0;
}

void SangTrai(KhoiGach *pkhoigach)
{
    for(int i=0;i<pkhoigach->Row;i++)
    for(int j=0;j<pkhoigach->Col;j++)
    if(pkhoigach->arr[i][j]==1)
    {
        if(Left(pkhoigach->iBoard+i,pkhoigach->jBoard+j)==0||pkhoigach->iBoard<=3)
        return;
    }
    pkhoigach->jBoard-=1; //Dich vi tri cua bang trang thai sang trai 1 so voi Board[22][10].
}

void SangPhai(KhoiGach *pkhoigach)
{
    for(int i=0;i<pkhoigach->Row;i++)
    for(int j=0;j<pkhoigach->Col;j++)
    if(pkhoigach->arr[i][j]==1)
    {
        if(Right(pkhoigach->iBoard+i,pkhoigach->jBoard+j)==0||pkhoigach->iBoard<=3)
        return;
    }
    pkhoigach->jBoard+=1; //Dich vi tri cua bang trang thai sang phai 1 so voi Board[22][10]
}

int RoiXuong(KhoiGach *pkhoigach) //0 : không thể rơi xuống,1 : có thể rơi xuống.
{
    for(int i=0;i<pkhoigach->Row;i++)
    for(int j=0;j<pkhoigach->Col;j++)
    if(pkhoigach->arr[i][j]==1)
    {
        if(Down(pkhoigach->iBoard+i,pkhoigach->jBoard+j)==0) return 0;
    }
    pkhoigach->iBoard+=1; //Roi xuong 1 so voi Board[22][10]
    return 1;
}

void GanGiaTri(KhoiGach* pkhoigach)
{
    for(int i=0;i<pkhoigach->Row;i++)
        for(int j=0;j<pkhoigach->Col;j++)
            if(pkhoigach->arr[i][j]==1)
            {
                Board[pkhoigach->iBoard+i][pkhoigach->jBoard+j]=1;
            }
}

void XoayKhoiGach(KhoiGach* pkhoigach)
{
    int i,j;
    int** tmpArr;
    int tmpCol = pkhoigach->Row;
    int tmpRow = pkhoigach->Col;
    tmpArr = new int* [tmpRow];
    for (i=0;i<tmpRow;i++)
    {
        tmpArr[i] = new int [tmpCol];
    }
    for (i=pkhoigach->Row-1;i>=0;i--)
    {
        for (j=pkhoigach->Col-1;j>=0;j--)
        {
            tmpArr[j][pkhoigach->Row-i-1]=pkhoigach->arr[i][j];
        }
    }
    for (i=0;i<tmpRow;i++)
    {
        for (j=0;j<tmpCol;j++)
        {
            if (Inside(pkhoigach->iBoard+i,pkhoigach->jBoard+j) == false|| Board[pkhoigach->iBoard+i][pkhoigach->jBoard+j]==1)
                return;
        }
    }
    for (i=0;i<pkhoigach->Row;i++)
    {
        delete [] pkhoigach->arr[i];
    }
    delete [] pkhoigach->arr;
    pkhoigach->Col=tmpCol;
    pkhoigach->Row=tmpRow;
    pkhoigach->arr=tmpArr;

}

void VeKhoiGach(KhoiGach* pkhoigach)
{
    int i;
    int j;
    for(i=0;i<pkhoigach->Row;i++)
        for(j=0;j<pkhoigach->Col;j++)
            if(pkhoigach->arr[i][j]==1&&(pkhoigach->iBoard+i)>3)
            {
                textcolor(LIGHTRED);
                gotoxy(LEFT+pkhoigach->jBoard+j+1,TOP+pkhoigach->iBoard+i-3);
                cout << char (2);
            }
}

void XoaKhoiGach(KhoiGach *pkhoigach)
{
    int i;
    int j;
    for(i=0;i<pkhoigach->Row;i++)
        for(j=0;j<pkhoigach->Col;j++)
            if(pkhoigach->arr[i][j]==1&&(pkhoigach->iBoard+i)>3)
            {
                textcolor(BLACK);
                gotoxy(LEFT+pkhoigach->jBoard+j+1,TOP+pkhoigach->iBoard+i-3);
                cout << " ";
            }
}

void InitGame(INFO *info)
{
    info->level=1;
    info->score=0;
    info->speed=0.4;
}
int CapNhat(INFO *info, int score)
{
    info->score+=score;
    if(info->score>=200&&info->level<2 && info->score<=300)
    {
        info->level++;
        info->speed-=0.1;
    }
    if(info->score>=300&&info->level<3)
    {
        info->level++;
        info->speed-=0.1;
    }
    return 0; //Chua win game.
}
void VeBangDiem(INFO info)
{
    textcolor(LIGHTYELLOW);
    gotoxy(LEFT+MaxJ+2,12);cout << " SCORE " ;
    gotoxy(LEFT+MaxJ+2,13);cout << "   "<<info.score;
    gotoxy(LEFT+MaxJ+2,16);cout << " LEVEL " ;
    gotoxy(LEFT+MaxJ+2,17);cout << "   "<<info.level;
    gotoxy(LEFT+MaxJ+2,20);cout << " HIGH  ";
    gotoxy(LEFT+MaxJ+2,21);cout << " SCORE ";
    if (info.score > bestScore()) {
		write_bestScore(info);
	}
    gotoxy(LEFT+MaxJ+2,22);cout << "  "<<bestScore();
}

void write_bestScore(INFO inf)
{
	fstream fileScore;
	fileScore.open("score.txt", ios::out);
	fileScore << inf.score;
	fileScore.close();
}

int bestScore()
{
	int score;
	fstream fileScore;
	fileScore.open("score.txt", ios::in);
	fileScore >> score;
	fileScore.close();
	return score;
}


int KiemTra(KhoiGach *pkhoigach,INFO *infogame) //-1 : gameover 0: win
{
    int i,j,dem;
    i=pkhoigach->Row-1;
    if(pkhoigach->iBoard<=3) return -1;//Gameover
    do
    {
        dem=0;
        for(j=0;j<MaxJ;j++)
        {
            if(Board[pkhoigach->iBoard+i][j]==1) dem++;
        }
        if(dem==MaxJ)
        {
            CapNhat(infogame,20);
            UpdateBoard(pkhoigach->iBoard+i);
            DisplayBoard();
        }
        else
        {
            i=i-1;
        }
    }while(i>=0);
    return 1;
}

void HuyKhoiGach(KhoiGach* pkhoigach)
{
    int i;
    //Huy bo nho cua ma tran trang thai arr.
    for(i=0;i<pkhoigach->Row;i++) free(pkhoigach->arr[i]);
    free(pkhoigach->arr);
    //Sau do moi free(pkhoigach)
    free(pkhoigach);
    pkhoigach=NULL;
}

int Loai()
{
    srand (time(NULL));
    int x=rand()%7;
    switch(x)
    {
        case 0:
            return 15;
            break;
        case 1:
            return 31;
            break;
        case 2:
            return 51;
            break;
        case 3:
            return 30;
            break;
        case 4:
            return 58;
            break;
        case 5:
            return 57;
            break;
        case 6:
            return 60;
            break;
    }
}

void Ve_Next(int ID)
{
    KhoiGach *pnext=TaoKhoiGach(ID);
    int iRoot=LEFT+MaxJ+4;
    int jRoot=TOP+2;
    for(int i=0;i<pnext->Row;i++)
    {
        for (int j=0;j<pnext->Col;j++)
        {
            if(pnext->arr[i][j]==1)
            {
                textcolor(LIGHTGREEN);
                gotoxy(iRoot+j,jRoot+i);
                cout << char (2);
            }
        }
    }
    HuyKhoiGach(pnext);
}

void Xoa_Next()
{
    int iRoot=LEFT+MaxJ+4;
    int jRoot=TOP+2;
    for(int i=0;i<3;i++)
    {
        for (int j=0;j<4;j++)
        {
            textcolor(BLACK);
            gotoxy(iRoot+j,jRoot+i);
            cout << " ";
        }
    }
}



