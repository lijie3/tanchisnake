/*void SetWindowSize(int cols, int lines)//设置窗口大小
{
	system("title 贪吃蛇");
	char cmd[30];
	_sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);
	system(cmd);
}

void SetColor(int colorID)//设置文本颜色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

void SetCursonPosition(int x, int y)//设置光标位置
{
	COORD position;
	position.X = x * 2;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}





#include <stdio.h>
#include <windows.h>
#include "tanchishe.h"
void SetWindowSize(int cols, int lines)//设置窗口大小
{
	system("title 贪吃蛇");
	char cmd[30];
	_sprintf(cmd, "mode con cols=%d lines=%d", cols * 2, lines);
	system(cmd);
}

void SetColor(int colorID)//设置文本颜色
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

void SetCursonPosition(int x,int y)//设置光标位置
{
	COORD position;
	position.X = x * 2;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
int main()
{
	SetWindowSize(41, 32);
	SetColor(2);
	SetCursorPosition(13, 26);
	printf("Press any key to start... ");
	SetCursorPosition(13, 27);
	system("pause");
	while (1);
	return 0;
}*/