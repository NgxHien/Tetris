#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<time.h>

using namespace std;

#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1

#define LEFT    4
#define TOP     4
#define RIGHT   16



//----------------------------------------------------------------------//

enum                    // màu
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

typedef struct                          // Khối gạch
{
    int **arr;
    int Row,Col;
    int iBoard,jBoard;
}KhoiGach;

typedef struct                          // thông tin trò chơi
{
    int score;
    int level;
    float speed;
}INFO;

void gotoxy(int x, int y);      // đưa con trỏ đến tọa độ (x,y)
void textcolor(WORD color);     // đổi màu chữ
void DrawBoard();               // Vẽ viền bảng chơi
void UpdateBoard(int Row);      // Cập nhật lại bảng
void DisplayBoard();            // Vẽ bảng chơi
KhoiGach *TaoKhoiGach(int ID);
int Inside(int i,int j);        //Xem i,j có thuộc mảng Board[24][10] hay không?
int Left(int i,int j);          //Xem bên trái viên gạch có gì không
int Right(int i,int j);         //Xem bên phải viên gạch có gì không
int Down(int i,int j);          //Xem bên đưới viên gạch có gì không
void SangTrai(KhoiGach *pkhoigach);
void SangPhai(KhoiGach *pkhoigach);
int RoiXuong(KhoiGach *pkhoigach);      //0: không thể rơi xuống, 1: có thể rơi xuống.
void GanGiaTri(KhoiGach* pkhoigach);    // Cập nhật khối gạch trên mảng Board
void XoayKhoiGach(KhoiGach* pkhoigach);
void VeKhoiGach(KhoiGach* pkhoigach);
void XoaKhoiGach(KhoiGach *pkhoigach);
void InitGame(INFO *info);              // thông tin đầu game
int CapNhat(INFO *info, int score);     // Ăn điểm, tăng độ khó
void VeBangDiem(INFO info);
int KiemTra(KhoiGach *pkhoigach,INFO *infogame); //-1: gameover 0: win
void HuyKhoiGach(KhoiGach* pkhoigach);         // giải phóng bộ nhớ khối gạch
int Loai();    // random ID cho khối gạch
void Ve_Next(int ID);   // Vẽ khối tiếp theo ở ngoài bảng
void Xoa_Next();        // Xóa khối tiếp theo ngoài bảng
void write_bestScore(INFO inf);
int bestScore();









