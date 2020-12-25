#ifndef __TOOLS_H__
#define __TOOLS_H__

void SetWindowSize(int cols, int lines);//设置窗口大小(列，行)
void gotoxy(int x, int y);//设置光标位置
void SetColor(int colorID);//设置文本颜色
void SetBackColor();//设置文本背景色
void Print_point(int x, int y);//输出方块
void Print_blank(int x, int y);//输出空白
void Print_food(int x, int y);//输出食物

#endif // __TOOLS_H__
