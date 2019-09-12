//
//文件夹: 03 Stack_Queue/06 Hanoi
//文件名: Hanoi
//内　容：汉诺塔相关操作列表
//Author Huangcp
//Date 2019/9/10 下午 11:17
//Version 1.0
//

#ifndef DATA_STRUCTURE_HANOI_H
#define DATA_STRUCTURE_HANOI_H
#include <stdio.h>

/* 全局变量 */
int gStep;								//统计移动步数

/* 汉诺塔函数列表 */
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(1)算法3.5：汉诺塔求解。以y为辅助，将x上前n个圆盘移动到z。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void hanoi(int n, char x, char y, char z);

/*━━━━━━━━━━━━┓
┃(2)将第n个圆盘从x移到z。┃
┗━━━━━━━━━━━━*/
void move(char x, int n, char z);

/*════╗
║ 算法3.5║
╚════*/
void hanoi(int n, char x, char y, char z)
{
    if(n==1)							//欲移动n个圆盘，需先移动其上的n-1个圆盘
        move(x, 1, z);					//将编号为1的圆盘从x移到z
    else
    {
        hanoi(n-1, x, z, y);			//将x上编号为1至n-1的圆盘移到y，z作辅助塔
        move(x, n, z);					//将编号为n的圆盘从x移到z
        hanoi(n-1, y, x, z);			//将y上编号为1至n-1的圆盘移动到z，x作辅助塔
    }
}

void move(char x, int n, char z)
{
    gStep++;							//step为全局变量，在main函数之外定义
    printf("第%2d步：将第 %d 个圆盘从 %c 移到 %c \n", gStep, n, x, z);
}

#endif //DATA_STRUCTURE_HANOI_H
