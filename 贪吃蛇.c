#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "tools.h"
#include "startinterface.h"
//蛇的移动方向
enum Direction { UP, DOWN, LEFT, RIGHT };
//食物的相关参数
struct {
	int x;
	int y;
	int count;//计数产生的食物个数
}food;
//限时食物的相关参数
struct {
	int x;
	int y;
	int time;//剩余时间
	int count;
	bool bigflag;//食物是否存在标记
	bool flashflag;//闪烁标记
}big_food;
//蛇的相关属性
struct {
	enum Direction direction;//蛇的移动方向
	int sorce;//分数
	int speed;//蛇移动的速度
	int len;//蛇的长度
	int xy[28*28+1][2];//存储蛇身体坐标
}snake;
//排行榜数据
typedef struct
{
	char name[12];
	int score;
}chart;
chart cha[3];
void createFood();//生成随机食物
void createbig_food();//生成限时奖励食物
void FlashBigfood();//闪烁限时奖励食物
void selete();//绘制地图选择菜单
void snake_init();//贪吃蛇初始化
void snake_move();//贪吃蛇移动及增长
bool ChangeDirection();//改变贪吃蛇移动方向
int PauseMenu();//绘制暂停暂停菜单
bool OverEdge();//判断游戏是否结束 撞到墙或撞到自身
int GameOver();//绘制游戏结束菜单
void Print_chart();//输出排行榜
int updata_chart();//更新排行榜

int main()
{
	SetWindowSize(41, 32);//设置窗口大小
	startinterface();//开场动画
	while (1)//游戏一级循环
	{
		int tmp=0;
		selete();//开始选择菜单
		snake_init();
		createFood();
		while (OverEdge())//游戏二级循环
		{
			snake_move();
			if (food.count!=big_food.count &&food.count % 5 == 0&&big_food.bigflag==false)//生成限时奖励食物的条件
			{
				createbig_food();
			}
			FlashBigfood();
			Sleep(snake.speed);
			if (ChangeDirection());
			else
			{
				tmp = PauseMenu();
				if (tmp == 2)//选择重新开始游戏
				{
					system("cls");//清屏
					break;
				}
				if (tmp == 3)//选择退出游戏
					return 0;
			}
		}
		if (tmp != 2)
		{
			if (snake.sorce > cha[2].score)
			{
				tmp=updata_chart();
				if (tmp == 2)//选择退出游戏
					return 0;
				system("cls");//清屏
			}
			else
			{
				tmp = GameOver();
				if (tmp == 2)//选择退出游戏
					return 0;
				system("cls");//清屏
			}
		}
	}
}//主程序

void snake_init()//贪吃蛇初始化
{
	food.count = 0;
	big_food.count = 0;
	big_food.bigflag = false;
	snake.sorce = 0;
	gotoxy(37, 8);
	printf("%5d", snake.sorce);
	snake.direction = UP;
	snake.len = 3;
	SetColor(14);
	snake.xy[0][0] = 16;
	snake.xy[0][1] = 16;
	Print_food(16, 16);
	snake.xy[1][0] = 16;
	snake.xy[1][1] = 17;
	Print_point(16, 17);
	snake.xy[2][0] = 16;
	snake.xy[2][1] = 18;
	Print_point(16, 18);
	snake.xy[3][0] = 16;
	snake.xy[3][1] = 18;
}
void createFood()//生成随机食物
{
	bool flag = true;
	while (flag)
	{
		flag = false;
		srand((unsigned int)time(NULL));
		food.x = rand() % (28) + 2;
		food.y = rand() % (28) + 2;
		for (int i = 0; i < snake.len; i++)
		{
			if (food.x == snake.xy[i][0])
				if (food.y == snake.xy[i][1])
					flag = true;
		}
	}
	SetColor(13);
	Print_food(food.x, food.y);
}
bool OverEdge()//判断游戏是否结束 撞到墙或撞到自身
{
	if (snake.xy[0][0] <= 1 || snake.xy[0][0] >= 30)
		return false;
	if (snake.xy[0][1] <= 1 || snake.xy[0][1] >= 30)
		return false;
	for (int i = 1; i < snake.len; i++)
	{
		if (snake.xy[0][0] == snake.xy[i][0] && snake.xy[0][1] == snake.xy[i][1])
			return false;
	}
	return true;
}
int PauseMenu()//绘制暂停暂停菜单
{
	/*绘制菜单*/
	SetColor(11);
	gotoxy(32, 19);
	printf("菜单：");
	Sleep(100);
	gotoxy(34, 21);
	SetBackColor();
	printf("继续游戏");
	Sleep(100);
	gotoxy(34, 23);
	SetColor(11);
	printf("重新开始    ");
	gotoxy(38, 21);
	printf("    ");
	Sleep(100);
	gotoxy(34, 25);
	printf("退出游戏    ");
	gotoxy(0, 31);

	/*选择部分*/
	int ch;
	int tmp_key = 1;
	bool flag = false;
	while ((ch = _getch()))
	{
		switch (ch)
		{
		case 72://UP
			if (tmp_key > 1)
			{
				switch (tmp_key)
				{
				case 2:
					gotoxy(34, 21);
					SetBackColor();
					printf("继续游戏");
					gotoxy(34, 23);
					SetColor(11);
					printf("重新开始");

					--tmp_key;
					break;
				case 3:
					gotoxy(34, 23);
					SetBackColor();
					printf("重新开始");
					gotoxy(34, 25);
					SetColor(11);
					printf("退出游戏");

					--tmp_key;
					break;
				}
			}
			break;

		case 80://DOWN
			if (tmp_key < 3)
			{
				switch (tmp_key)
				{
				case 1:
					gotoxy(34, 23);
					SetBackColor();
					printf("重新开始");
					gotoxy(34, 21);
					SetColor(11);
					printf("继续游戏");

					++tmp_key;
					break;
				case 2:
					gotoxy(34, 25);
					SetBackColor();
					printf("退出游戏");
					gotoxy(34, 23);
					SetColor(11);
					printf("重新开始");

					++tmp_key;
					break;
				}
			}
			break;

		case 13://Enter
			flag = true;
			break;

		default:
			break;
		}

		if (flag)
		{
			break;
		}
		gotoxy(0, 31);
	}

	if (tmp_key == 1) //选择继续游戏，则将菜单擦除
	{
		Print_chart();
	}
	return tmp_key;
}
bool ChangeDirection()//改变贪吃蛇移动方向
{
	char ch;
	if (_kbhit())//kbhit函数返回值为两个，需注意
	{
		ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			switch (ch)
			{
			case 72:
				if (snake.direction != DOWN)//如果方向与当前运动方向相反，无效
					snake.direction = UP;
				break;
			case 80:
				if (snake.direction != UP)
					snake.direction = DOWN;
				break;
			case 75:
				if (snake.direction != RIGHT)
					snake.direction = LEFT;
				break;
			case 77:
				if (snake.direction != LEFT)
					snake.direction = RIGHT;
				break;
			default:
				break;
			}
			return true;

		case 27://ESC
			return false;

		default:
			return true;
		}
	}
	return true;
}
void snake_move()//贪吃蛇移动
{
	for (int i = 0; i < snake.len; i++)
		Print_blank(snake.xy[i][0], snake.xy[i][1]);
	for (int i = snake.len ; i > 0; i--)
	{
		snake.xy[i][0] = snake.xy[i - 1][0];
		snake.xy[i][1] = snake.xy[i - 1][1];
	}
	//Print_blank(snake.xy[snake.len - 1][0], snake.xy[snake.len - 1][1]);
	//Print_point(snake.xy[0][0], snake.xy[0][1]);
	switch (snake.direction)
	{
	case UP:
		snake.xy[0][1]--;
		break;
	case DOWN:
		snake.xy[0][1]++;
		break;
	case LEFT:
		snake.xy[0][0]--;
		break;
	case RIGHT:
		snake.xy[0][0]++;
		break;
	}
	if (snake.xy[0][0] == big_food.x && snake.xy[0][1] == big_food.y)
	{
		big_food.bigflag = false;
		gotoxy(5, 0);
		printf("                                          ");
		snake.sorce += big_food.time / 2;
		big_food.time = 0;
		gotoxy(37, 8);
		SetColor(11);
		printf("%5d", snake.sorce);
	}
	if (snake.xy[0][0] == food.x && snake.xy[0][1] == food.y)
	{
		createFood();
		food.count++;
		snake.len++;
		snake.sorce += 5;
		gotoxy(37, 8);
		SetColor(11);
		printf("%5d", snake.sorce);
	}
	SetColor(14);
	Print_food(snake.xy[0][0], snake.xy[0][1]);
	for (int i = 1; i < snake.len; i++)
		Print_point(snake.xy[i][0], snake.xy[i][1]);
}
void selete()//绘制地图选择菜单
{
	SetColor(5);
	int SNAKE[53][2] = { {7,14},{6,14},{5,15},{6,16},{7,17},{5,18},{6,18},
						{9,14},{9,15},{9,16},{9,17},{9,18},{10,15},{11,16},{12,17},{13,14},{13,15},{13,16},{13,17},{13,18},
						{15,18},{16,17},{17,16},{18,15},{18,16},{19,14},{19,16},{20,15},{20,16},{21,16},{22,17},{23,18},
						{25,14},{25,15},{25,16},{25,17},{25,18},{26,16},{27,15},{27,17},{28,14},{28,18},
						{30,14},{30,15},{30,16},{30,17},{30,18},{31,14},{31,16},{31,18},{32,14},{32,16},{32,18} };
	for (int j = 0; j < 53; j++)
	{
		if (SNAKE[j][0] >= 0)
			Print_point(SNAKE[j][0], SNAKE[j][1]);
	}
	SetColor(3);
	gotoxy(13, 26);
	printf("                          ");
	gotoxy(13, 27);
	printf("                          ");
	gotoxy(6, 21);
	printf("请选择游戏难度：");
	gotoxy(6, 22);
	printf("(上下键选择,回车确认)");
	gotoxy(27, 22);
	SetBackColor();//第一个选项设置背景色以表示当前选中
	printf("简单模式");
	gotoxy(27, 24);
	SetColor(3);
	printf("普通模式");
	gotoxy(27, 26);
	printf("困难模式");
	gotoxy(27, 28);
	printf("炼狱模式");
	gotoxy(0, 31);
	int score = 0;
	//上下方向键选择模块
	int ch;
	int key = 1;
	bool flag = false;//记录是否键入Enter键
	while ((ch = _getch()))
	{
		switch (ch)
		{
		case 72:
			if (key > 1)
			{
				switch (key)
				{
				case 2:
					gotoxy(27, 22);
					SetBackColor();
					printf("简单模式");

					gotoxy(27, 24);
					SetColor(3);
					printf("普通模式");

					--key;
					break;
				case 3:
					gotoxy(27, 24);
					SetBackColor();
					printf("普通模式");

					gotoxy(27, 26);
					SetColor(3);
					printf("困难模式");

					--key;
					break;
				case 4:
					gotoxy(27, 26);
					SetBackColor();
					printf("困难模式");

					gotoxy(27, 28);
					SetColor(3);
					printf("炼狱模式");

					--key;
					break;
				}
			}
			break;

		case 80://DOWN下方向键
			if (key < 4)
			{
				switch (key)
				{
				case 1:
					gotoxy(27, 24);
					SetBackColor();
					printf("普通模式");
					gotoxy(27, 22);
					SetColor(3);
					printf("简单模式");

					++key;
					break;
				case 2:
					gotoxy(27, 26);
					SetBackColor();
					printf("困难模式");
					gotoxy(27, 24);
					SetColor(3);
					printf("普通模式");

					++key;
					break;
				case 3:
					gotoxy(27, 28);
					SetBackColor();
					printf("炼狱模式");
					gotoxy(27, 26);
					SetColor(3);
					printf("困难模式");

					++key;
					break;
				}
			}
			break;
		case 13:
			flag = true;
			break;
		default:
			break;
		}
		if (flag) break;//输入Enter回车键确认，退出检查输入循环

		gotoxy(0, 31);//将光标置于左下角，避免关标闪烁影响游戏体验

	}
	switch (key)//根据所选选项设置蛇的移动速度，speed值越小，速度越快
	{
	case 1:
		snake.speed = 135;
		break;
	case 2:
		snake.speed = 100;
		break;
	case 3:
		snake.speed = 60;
		break;
	case 4:
		snake.speed = 30;
		break;
	default:
		break;
	}
	system("cls");//清屏
	for (int i = 1; i <= 30; i++)
	{
		Print_point(i, 1);
		Print_point(i, 30);
		Print_point(1, i);
		Print_point(30, i);
	}
	//绘制侧边栏
	gotoxy(33, 1);
	printf("Greedy Snake");
	gotoxy(34, 2);
	printf("贪吃蛇");
	gotoxy(31, 4);
	printf("难度:");
	gotoxy(36, 5);
	switch (key)
	{
	case 1:
		printf("简单模式");
		break;
	case 2:
		printf("普通模式");
		break;
	case 3:
		printf("困难模式");
		break;
	case 4:
		printf("炼狱模式");
		break;
	default:
		break;
	}
	gotoxy(31, 7);
	printf("得分:");
	gotoxy(37, 8);
	printf("%5d",snake.sorce);
	gotoxy(33, 13);
	printf(" 方向键移动");
	gotoxy(33, 15);
	printf(" ESC键暂停");
	FILE* fp = fopen("chart.txt","a+");
	fclose(fp);
	fp = fopen("chart.txt", "r+");
	for (int i = 0; (fscanf(fp, "%s %d", cha[i].name, &cha[i].score) != EOF); i++);
	fclose(fp);
	Print_chart();
}
void Print_chart()
{
	SetColor(11);
	gotoxy(32, 19);
	printf("排行榜：");
	Sleep(100);
	gotoxy(34, 21);
	printf("%-6s %5d", cha[0].name, cha[0].score);
	Sleep(100);
	gotoxy(34, 23);
	SetColor(11);
	printf("%-6s %5d", cha[1].name, cha[1].score);
	Sleep(100);
	gotoxy(34, 25);
	printf("%-6s %5d", cha[2].name, cha[2].score);
	gotoxy(0, 31);
}
int GameOver()//绘制游戏结束菜单
{
	Sleep(500);
	SetColor(11);
	gotoxy(10, 8);
	printf("━━━━━━━━━━━━━━━━━━━━━━");
	Sleep(30);
	gotoxy(9, 9);
	printf(" ┃               Game Over !!!              ┃");
	Sleep(30);
	gotoxy(9, 10);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 11);
	printf(" ┃           真遗憾，游戏结束               ┃");
	Sleep(30);
	gotoxy(9, 12);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 13);
	printf(" ┃             你的分数为：                 ┃");
	gotoxy(24, 13);
	printf("%d", snake.sorce);
	Sleep(30);
	gotoxy(9, 14);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 15);
	printf(" ┃   是否再来一局？                         ┃");
	Sleep(30);
	gotoxy(9, 16);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 17);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 18);
	printf(" ┃    重新开始            退出游戏          ┃");
	Sleep(30);
	gotoxy(9, 19);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 20);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(10, 21);
	printf("━━━━━━━━━━━━━━━━━━━━━━");

	Sleep(100);
	gotoxy(12, 18);
	SetBackColor();
	printf("重新开始");
	gotoxy(0, 31);

	/*选择部分*/
	int ch;
	int tmp_key = 1;
	bool flag = false;
	while ((ch = _getch()))
	{
		switch (ch)
		{
		case 75://LEFT
			if (tmp_key > 1)
			{
				gotoxy(12, 18);
				SetBackColor();
				printf("重新开始");
				gotoxy(22, 18);
				SetColor(11);
				printf("退出游戏");
				--tmp_key;
			}
			break;

		case 77://RIGHT
			if (tmp_key < 2)
			{
				gotoxy(22, 18);
				SetBackColor();
				printf("退出游戏");
				gotoxy(12, 18);
				SetColor(11);
				printf("重新开始");
				++tmp_key;
			}
			break;

		case 13://Enter
			flag = true;
			break;

		default:
			break;
		}

		gotoxy(0, 31);
		if (flag) {
			break;
		}
	}

	SetColor(11);
	switch (tmp_key)
	{
	case 1:
		return 1;//重新开始
	case 2:
		return 2;//退出游戏
	default:
		return 1;
	}
}
void createbig_food()//生成限时奖励食物
{
	bool flag = true;
	while (flag)
	{
		flag = false;
		srand((unsigned int)time(NULL) + 1);
		big_food.x = rand() % (28) + 2;
		big_food.y = rand() % (28) + 2;
		for (int i = 0; i < snake.len; i++)
		{
			if (big_food.x == snake.xy[i][0])
				if (big_food.y == snake.xy[i][1])
					flag = true;
		}
	}
	SetColor(3);
	Print_food(big_food.x, big_food.y);
	big_food.count = food.count;
	big_food.bigflag = true;
	big_food.flashflag = true;
	big_food.time = 42;
	gotoxy(5, 0);
	SetColor(11);
	printf("------------------------------------------");//进度条
}
void FlashBigfood()//闪烁限时奖励食物
{
	if (big_food.bigflag)
	{
		gotoxy(big_food.x, big_food.y);
		SetColor(18);
		if (big_food.flashflag)
		{
			printf("  ");
			big_food.flashflag = false;
		}
		else
		{
			Print_food(big_food.x, big_food.y);
			big_food.flashflag = true;
		}
		gotoxy(26, 0);
		SetColor(11);
		for (int i = 42; i >= big_food.time; --i)//进度条缩短
			printf("\b \b");
		big_food.time--;
		if (big_food.time == 0)
		{
			big_food.bigflag = false;
			Print_blank(big_food.x, big_food.y);
			Print_blank(5, 0);
		}
	}
}
int updata_chart()
{
	Sleep(500);
	SetColor(11);
	gotoxy(10, 8);
	printf("━━━━━━━━━━━━━━━━━━━━━━");
	Sleep(30);
	gotoxy(9, 9);
	printf(" ┃               Game Over !!!              ┃");
	Sleep(30);
	gotoxy(9, 10);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 11);
	printf(" ┃           恭喜您，进入排行榜！           ┃");
	Sleep(30);
	gotoxy(9, 12);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 13);
	printf(" ┃             你的分数为：                 ┃");
	gotoxy(24, 13);
	printf("%d", snake.sorce);
	Sleep(30);
	gotoxy(9, 14);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 15);
	printf(" ┃   请输入您的姓名：                       ┃");
	char name[12];
	Sleep(30);
	gotoxy(9, 16);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 17);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 18);
	printf(" ┃    重新开始            退出游戏          ┃");
	Sleep(30);
	gotoxy(9, 19);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(9, 20);
	printf(" ┃                                          ┃");
	Sleep(30);
	gotoxy(10, 21);
	printf("━━━━━━━━━━━━━━━━━━━━━━");
	gotoxy(20, 15);
	scanf("%s", name);
	int i;
	if (snake.sorce > cha[0].score)
	{
		for (i = 0; cha[1].name[i] != '\0'; i++)
			cha[2].name[i] = cha[1].name[i];
		cha[2].name[i] = '\0';
		cha[2].score = cha[1].score;
		for (i = 0; cha[0].name[i] != '\0'; i++)
			cha[1].name[i] = cha[0].name[i];
		cha[1].name[i] = '\0';
		cha[1].score = cha[0].score;
		for (i = 0; name[i] != '\0'; i++)
			cha[0].name[i] = name[i];
		cha[0].name[i] = '\0';
		cha[0].score = snake.sorce;
	}
	else if (snake.sorce > cha[1].score)
	{
		for (i = 0; cha[1].name[i] != '\0'; i++)
			cha[2].name[i] = cha[1].name[i];
		cha[2].name[i] = '\0';
		cha[2].score = cha[1].score;
		for (i = 0; name[i] != '\0'; i++)
			cha[1].name[i] = name[i];
		cha[1].name[i] = '\0';
		cha[1].score = snake.sorce;
	}
	else
	{
		for (i = 0; name[i] != '\0'; i++)
			cha[2].name[i] = name[i];
		cha[2].name[i] = '\0';
		cha[2].score = snake.sorce;
	}
	FILE* fp = fopen("chart.txt", "w+");
	for (int i = 0; i < 3; i++)
	{
		fprintf(fp, "%s %d\n", cha[i].name, cha[i].score);
	}
	fclose(fp);
	Sleep(100);
	gotoxy(12, 18);
	SetBackColor();
	printf("重新开始");
	gotoxy(0, 31);

	/*选择部分*/
	int ch;
	int tmp_key = 1;
	bool flag = false;
	while ((ch = _getch()))
	{
		switch (ch)
		{
		case 75://LEFT
			if (tmp_key > 1)
			{
				gotoxy(12, 18);
				SetBackColor();
				printf("重新开始");
				gotoxy(22, 18);
				SetColor(11);
				printf("退出游戏");
				--tmp_key;
			}
			break;

		case 77://RIGHT
			if (tmp_key < 2)
			{
				gotoxy(22, 18);
				SetBackColor();
				printf("退出游戏");
				gotoxy(12, 18);
				SetColor(11);
				printf("重新开始");
				++tmp_key;
			}
			break;

		case 13://Enter
			flag = true;
			break;

		default:
			break;
		}

		gotoxy(0, 31);
		if (flag) {
			break;
		}
	}
	SetColor(11);
	switch (tmp_key)
	{
	case 1:
		return 1;//重新开始
	case 2:
		return 2;//退出游戏
	default:
		return 1;
	}
}
