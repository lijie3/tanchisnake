#include "tools.h"
#include <windows.h>
#include <stdio.h>

void SetWindowSize(int cols, int lines)//设置窗口大小(列，行)
{
	system("title 贪吃蛇");
	char cmd[30];
	sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);
	system(cmd);
}

void gotoxy(int x, int y)//设置光标位置
{
	COORD coord;
	coord.X = x * 2;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int colorID)//设置文本颜色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}
void SetBackColor()//设置文本背景色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE |
		BACKGROUND_BLUE |
		BACKGROUND_GREEN |
		BACKGROUND_RED);
}
void Print_point(int x, int y)//输出方块
{
	gotoxy(x, y);
	printf("■");
}
void Print_blank(int x, int y)//输出空白
{
	gotoxy(x, y);
	printf("  ");
}
void Print_food(int x, int y)//输出食物
{
	gotoxy(x, y);
	printf("●");
}