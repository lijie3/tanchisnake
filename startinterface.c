#include <stdio.h>
#include <windows.h>
#include "tools.h"
#include "startinterface.h"

void startinterface()//开场动画
{
	SetColor(5);
	int snake[41] = { 14,14,15,16,17,18,17,16,15,14,15,16,17,18,17,16,15,14,15,16,17,18,17,16,15,14,15,16,17,18,17,16,15,14,15,16,17,18,17,16,15 };
	for (int i = 0; i < 10; i++)
	{
		Print_point(i, snake[i]);
		Sleep(35);
	}
	for (int i = 10; i < 41; i++)
	{
		Print_point(i, snake[i]);
		Print_blank(i - 10, snake[i - 10]);
		Sleep(35);
	}
	for (int i = 31; i < 41; i++)
	{
		Print_blank(i, snake[i]);
		Sleep(35);
	}
	system("cls");//清屏
	//字母SNAKE
	int SNAKE[53][2] = { {-26,14},{-25,14},{-27,15},{-26,16},{-25,17},{-27,18},{-26,18},
						{-23,14},{-23,15},{-23,16},{-23,17},{-23,18},{-22,15},{-21,16},{-20,17},{-19,14},{-19,15},{-19,16},{-19,17},{-19,18},
						{-17,18},{-16,17},{-15,16},{-14,15},{-14,16},{-13,14},{-13,16},{-12,15},{-12,16},{-11,16},{-10,17},{-9,18},
						{-7,14},{-7,15},{-7,16},{-7,17},{-7,18},{-6,16},{-5,15},{-5,17},{-4,14},{-4,18},
						{-2,14},{-2,15},{-2,16},{-2,17},{-2,18},{-1,14},{-1,16},{-1,18},{0,14},{0,16},{0,18} };
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 53; j++)
		{
			if (SNAKE[j][0] >= 0)
				Print_point(SNAKE[j][0], SNAKE[j][1]);
		}
		Sleep(35);
		for (int j = 0; j < 53; j++)
		{
			if (SNAKE[j][0] >= 0)
				Print_blank(SNAKE[j][0], SNAKE[j][1]);
			SNAKE[j][0]++;
		}
	}
	for (int j = 0; j < 53; j++)
	{
		if (SNAKE[j][0] >= 0)
			Print_point(SNAKE[j][0], SNAKE[j][1]);
	}
	gotoxy(13, 26);
	printf("Press any key to start...");
	gotoxy(13, 27);
	system("pause");
}