#include "tools.h"
#include <windows.h>
#include <stdio.h>

void SetWindowSize(int cols, int lines)//���ô��ڴ�С(�У���)
{
	system("title ̰����");
	char cmd[30];
	sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);
	system(cmd);
}

void gotoxy(int x, int y)//���ù��λ��
{
	COORD coord;
	coord.X = x * 2;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int colorID)//�����ı���ɫ
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
void SetBackColor()//�����ı�����ɫ
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE |
		BACKGROUND_BLUE |
		BACKGROUND_GREEN |
		BACKGROUND_RED);
}
void Print_point(int x, int y)//�������
{
	gotoxy(x, y);
	printf("��");
}
void Print_blank(int x, int y)//����հ�
{
	gotoxy(x, y);
	printf("  ");
}
void Print_food(int x, int y)//���ʳ��
{
	gotoxy(x, y);
	printf("��");
}