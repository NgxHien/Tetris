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
                    case 'W':
                        XoayKhoiGach(currKhoi);
                        break;
                    case 'A':
                        SangTrai(currKhoi);
                        break;
                    case 'D':
                        SangPhai(currKhoi);
                        break;
                    case 'S':
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
                    gotoxy(45,TOP + 16);
                    cout << "Game over!";
                    break;
                }
            if (ketqua == 0)
                {
                    gotoxy(45,TOP + 16);
                    cout << "Win !!!";
                    break;
                }
            HuyKhoiGach(currKhoi); //Giai phong bo nho.
            currKhoi=TaoKhoiGach(IDNext);
            IDNext=Loai();
            DisplayBoard();
        }
    }while(1);
}
