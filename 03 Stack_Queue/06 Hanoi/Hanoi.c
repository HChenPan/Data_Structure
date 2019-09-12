//
//文件夹: 03 Stack_Queue/06 Hanoi
//文件名: Hanoi
//内　容：汉诺塔相关函数测试
//Author Huangcp
//Date 2019/9/10 下午 11:17
//Version 1.0
//

#include "Hanoi.h"
int main(int argc, char **argv)
{
    int n;
    char x = 'x';
    char y = 'y';
    char z = 'z';

    n = 3;								//为控制时间，n不要超过10

    printf("作为示例，假设圆盘个数为 %d ，操作步骤如下...\n", n);

    hanoi(n,x,y,z);

    printf("\n");

    return 0;
}