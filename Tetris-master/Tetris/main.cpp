#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include "New-Tetris-1.h"

using namespace std;

int main()
{
    KhoiGach* currKhoi;
    INFO info;
    char c;
    currKhoi = TaoKhoiGach(Loai());
    InitGame(&info);
    int IDNext = Loai();
    clock_t Start,End;
    DrawBoard();
    do
    {
        VeBangDiem(info);
        VeKhoiGach(currKhoi);
        Xoa_Next();
        Ve_Next(IDNext);
        Start=clock();
        do
        {
            if(_kbhit())
            {
                c=toupper(_getch());
                XoaKhoiGach(currKhoi);
                switch(c)
                {
                    case 72:
                        XoayKhoiGach(currKhoi);
                        break;
                    case 75:
                        SangTrai(currKhoi);
                        break;
                    case 77:
                        SangPhai(currKhoi);
                        break;
                    case 80:
                        RoiXuong(currKhoi);
                        break;
                    }
                VeKhoiGach(currKhoi);
            }
            End=clock();
        }while(float(End-Start)/CLK_TCK<info.speed);
        XoaKhoiGach(currKhoi);
        if(RoiXuong(currKhoi)==0) //ko di chuyen xuong dc
        {
            GanGiaTri(currKhoi);
            int ketqua=KiemTra(currKhoi,&info);
            if(ketqua==-1)
                {
                    gotoxy(12,24 + 2);
                    cout << "Game over!";
                    gotoxy(12,24 + 3);
                    cout << "Your score: " << info.score;
                    break;
                }
            HuyKhoiGach(currKhoi); //Giai phong bo nho.
            currKhoi=TaoKhoiGach(IDNext);
            IDNext=Loai();
            DisplayBoard();
        }
    }while(1);
}
