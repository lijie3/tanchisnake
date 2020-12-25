#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include "tools.h"
#include "startinterface.h"
//�ߵ��ƶ�����
enum Direction { UP, DOWN, LEFT, RIGHT };
//ʳ�����ز���
struct {
	int x;
	int y;
	int count;//����������ʳ�����
}food;
//��ʱʳ�����ز���
struct {
	int x;
	int y;
	int time;//ʣ��ʱ��
	int count;
	bool bigflag;//ʳ���Ƿ���ڱ��
	bool flashflag;//��˸���
}big_food;
//�ߵ��������
struct {
	enum Direction direction;//�ߵ��ƶ�����
	int sorce;//����
	int speed;//���ƶ����ٶ�
	int len;//�ߵĳ���
	int xy[28*28+1][2];//�洢����������
}snake;
//���а�����
typedef struct
{
	char name[12];
	int score;
}chart;
chart cha[3];
void createFood();//�������ʳ��
void createbig_food();//������ʱ����ʳ��
void FlashBigfood();//��˸��ʱ����ʳ��
void selete();//���Ƶ�ͼѡ��˵�
void snake_init();//̰���߳�ʼ��
void snake_move();//̰�����ƶ�������
bool ChangeDirection();//�ı�̰�����ƶ�����
int PauseMenu();//������ͣ��ͣ�˵�
bool OverEdge();//�ж���Ϸ�Ƿ���� ײ��ǽ��ײ������
int GameOver();//������Ϸ�����˵�
void Print_chart();//������а�
int updata_chart();//�������а�

int main()
{
	SetWindowSize(41, 32);//���ô��ڴ�С
	startinterface();//��������
	while (1)//��Ϸһ��ѭ��
	{
		int tmp=0;
		selete();//��ʼѡ��˵�
		snake_init();
		createFood();
		while (OverEdge())//��Ϸ����ѭ��
		{
			snake_move();
			if (food.count!=big_food.count &&food.count % 5 == 0&&big_food.bigflag==false)//������ʱ����ʳ�������
			{
				createbig_food();
			}
			FlashBigfood();
			Sleep(snake.speed);
			if (ChangeDirection());
			else
			{
				tmp = PauseMenu();
				if (tmp == 2)//ѡ�����¿�ʼ��Ϸ
				{
					system("cls");//����
					break;
				}
				if (tmp == 3)//ѡ���˳���Ϸ
					return 0;
			}
		}
		if (tmp != 2)
		{
			if (snake.sorce > cha[2].score)
			{
				tmp=updata_chart();
				if (tmp == 2)//ѡ���˳���Ϸ
					return 0;
				system("cls");//����
			}
			else
			{
				tmp = GameOver();
				if (tmp == 2)//ѡ���˳���Ϸ
					return 0;
				system("cls");//����
			}
		}
	}
}//������

void snake_init()//̰���߳�ʼ��
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
void createFood()//�������ʳ��
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
bool OverEdge()//�ж���Ϸ�Ƿ���� ײ��ǽ��ײ������
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
int PauseMenu()//������ͣ��ͣ�˵�
{
	/*���Ʋ˵�*/
	SetColor(11);
	gotoxy(32, 19);
	printf("�˵���");
	Sleep(100);
	gotoxy(34, 21);
	SetBackColor();
	printf("������Ϸ");
	Sleep(100);
	gotoxy(34, 23);
	SetColor(11);
	printf("���¿�ʼ    ");
	gotoxy(38, 21);
	printf("    ");
	Sleep(100);
	gotoxy(34, 25);
	printf("�˳���Ϸ    ");
	gotoxy(0, 31);

	/*ѡ�񲿷�*/
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
					printf("������Ϸ");
					gotoxy(34, 23);
					SetColor(11);
					printf("���¿�ʼ");

					--tmp_key;
					break;
				case 3:
					gotoxy(34, 23);
					SetBackColor();
					printf("���¿�ʼ");
					gotoxy(34, 25);
					SetColor(11);
					printf("�˳���Ϸ");

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
					printf("���¿�ʼ");
					gotoxy(34, 21);
					SetColor(11);
					printf("������Ϸ");

					++tmp_key;
					break;
				case 2:
					gotoxy(34, 25);
					SetBackColor();
					printf("�˳���Ϸ");
					gotoxy(34, 23);
					SetColor(11);
					printf("���¿�ʼ");

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

	if (tmp_key == 1) //ѡ�������Ϸ���򽫲˵�����
	{
		Print_chart();
	}
	return tmp_key;
}
bool ChangeDirection()//�ı�̰�����ƶ�����
{
	char ch;
	if (_kbhit())//kbhit��������ֵΪ��������ע��
	{
		ch = _getch();
		switch (ch)
		{
		case -32:
			ch = _getch();
			switch (ch)
			{
			case 72:
				if (snake.direction != DOWN)//��������뵱ǰ�˶������෴����Ч
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
void snake_move()//̰�����ƶ�
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
void selete()//���Ƶ�ͼѡ��˵�
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
	printf("��ѡ����Ϸ�Ѷȣ�");
	gotoxy(6, 22);
	printf("(���¼�ѡ��,�س�ȷ��)");
	gotoxy(27, 22);
	SetBackColor();//��һ��ѡ�����ñ���ɫ�Ա�ʾ��ǰѡ��
	printf("��ģʽ");
	gotoxy(27, 24);
	SetColor(3);
	printf("��ͨģʽ");
	gotoxy(27, 26);
	printf("����ģʽ");
	gotoxy(27, 28);
	printf("����ģʽ");
	gotoxy(0, 31);
	int score = 0;
	//���·����ѡ��ģ��
	int ch;
	int key = 1;
	bool flag = false;//��¼�Ƿ����Enter��
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
					printf("��ģʽ");

					gotoxy(27, 24);
					SetColor(3);
					printf("��ͨģʽ");

					--key;
					break;
				case 3:
					gotoxy(27, 24);
					SetBackColor();
					printf("��ͨģʽ");

					gotoxy(27, 26);
					SetColor(3);
					printf("����ģʽ");

					--key;
					break;
				case 4:
					gotoxy(27, 26);
					SetBackColor();
					printf("����ģʽ");

					gotoxy(27, 28);
					SetColor(3);
					printf("����ģʽ");

					--key;
					break;
				}
			}
			break;

		case 80://DOWN�·����
			if (key < 4)
			{
				switch (key)
				{
				case 1:
					gotoxy(27, 24);
					SetBackColor();
					printf("��ͨģʽ");
					gotoxy(27, 22);
					SetColor(3);
					printf("��ģʽ");

					++key;
					break;
				case 2:
					gotoxy(27, 26);
					SetBackColor();
					printf("����ģʽ");
					gotoxy(27, 24);
					SetColor(3);
					printf("��ͨģʽ");

					++key;
					break;
				case 3:
					gotoxy(27, 28);
					SetBackColor();
					printf("����ģʽ");
					gotoxy(27, 26);
					SetColor(3);
					printf("����ģʽ");

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
		if (flag) break;//����Enter�س���ȷ�ϣ��˳��������ѭ��

		gotoxy(0, 31);//������������½ǣ�����ر���˸Ӱ����Ϸ����

	}
	switch (key)//������ѡѡ�������ߵ��ƶ��ٶȣ�speedֵԽС���ٶ�Խ��
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
	system("cls");//����
	for (int i = 1; i <= 30; i++)
	{
		Print_point(i, 1);
		Print_point(i, 30);
		Print_point(1, i);
		Print_point(30, i);
	}
	//���Ʋ����
	gotoxy(33, 1);
	printf("Greedy Snake");
	gotoxy(34, 2);
	printf("̰����");
	gotoxy(31, 4);
	printf("�Ѷ�:");
	gotoxy(36, 5);
	switch (key)
	{
	case 1:
		printf("��ģʽ");
		break;
	case 2:
		printf("��ͨģʽ");
		break;
	case 3:
		printf("����ģʽ");
		break;
	case 4:
		printf("����ģʽ");
		break;
	default:
		break;
	}
	gotoxy(31, 7);
	printf("�÷�:");
	gotoxy(37, 8);
	printf("%5d",snake.sorce);
	gotoxy(33, 13);
	printf(" ������ƶ�");
	gotoxy(33, 15);
	printf(" ESC����ͣ");
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
	printf("���а�");
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
int GameOver()//������Ϸ�����˵�
{
	Sleep(500);
	SetColor(11);
	gotoxy(10, 8);
	printf("��������������������������������������������");
	Sleep(30);
	gotoxy(9, 9);
	printf(" ��               Game Over !!!              ��");
	Sleep(30);
	gotoxy(9, 10);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 11);
	printf(" ��           ���ź�����Ϸ����               ��");
	Sleep(30);
	gotoxy(9, 12);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 13);
	printf(" ��             ��ķ���Ϊ��                 ��");
	gotoxy(24, 13);
	printf("%d", snake.sorce);
	Sleep(30);
	gotoxy(9, 14);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 15);
	printf(" ��   �Ƿ�����һ�֣�                         ��");
	Sleep(30);
	gotoxy(9, 16);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 17);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 18);
	printf(" ��    ���¿�ʼ            �˳���Ϸ          ��");
	Sleep(30);
	gotoxy(9, 19);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 20);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(10, 21);
	printf("��������������������������������������������");

	Sleep(100);
	gotoxy(12, 18);
	SetBackColor();
	printf("���¿�ʼ");
	gotoxy(0, 31);

	/*ѡ�񲿷�*/
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
				printf("���¿�ʼ");
				gotoxy(22, 18);
				SetColor(11);
				printf("�˳���Ϸ");
				--tmp_key;
			}
			break;

		case 77://RIGHT
			if (tmp_key < 2)
			{
				gotoxy(22, 18);
				SetBackColor();
				printf("�˳���Ϸ");
				gotoxy(12, 18);
				SetColor(11);
				printf("���¿�ʼ");
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
		return 1;//���¿�ʼ
	case 2:
		return 2;//�˳���Ϸ
	default:
		return 1;
	}
}
void createbig_food()//������ʱ����ʳ��
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
	printf("------------------------------------------");//������
}
void FlashBigfood()//��˸��ʱ����ʳ��
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
		for (int i = 42; i >= big_food.time; --i)//����������
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
	printf("��������������������������������������������");
	Sleep(30);
	gotoxy(9, 9);
	printf(" ��               Game Over !!!              ��");
	Sleep(30);
	gotoxy(9, 10);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 11);
	printf(" ��           ��ϲ�����������а�           ��");
	Sleep(30);
	gotoxy(9, 12);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 13);
	printf(" ��             ��ķ���Ϊ��                 ��");
	gotoxy(24, 13);
	printf("%d", snake.sorce);
	Sleep(30);
	gotoxy(9, 14);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 15);
	printf(" ��   ����������������                       ��");
	char name[12];
	Sleep(30);
	gotoxy(9, 16);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 17);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 18);
	printf(" ��    ���¿�ʼ            �˳���Ϸ          ��");
	Sleep(30);
	gotoxy(9, 19);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(9, 20);
	printf(" ��                                          ��");
	Sleep(30);
	gotoxy(10, 21);
	printf("��������������������������������������������");
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
	printf("���¿�ʼ");
	gotoxy(0, 31);

	/*ѡ�񲿷�*/
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
				printf("���¿�ʼ");
				gotoxy(22, 18);
				SetColor(11);
				printf("�˳���Ϸ");
				--tmp_key;
			}
			break;

		case 77://RIGHT
			if (tmp_key < 2)
			{
				gotoxy(22, 18);
				SetBackColor();
				printf("�˳���Ϸ");
				gotoxy(12, 18);
				SetColor(11);
				printf("���¿�ʼ");
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
		return 1;//���¿�ʼ
	case 2:
		return 2;//�˳���Ϸ
	default:
		return 1;
	}
}
