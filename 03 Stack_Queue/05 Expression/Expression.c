//
//文件夹: 
//文件名: Expression
//内　容：
//Author Huangcp
//Date 2019/9/10 下午 11:13
//Version 1.0
//

#include "Expression.h"
int main(int argc, char **argv)
{
    char opnd;
    char *exp = "(2+3)*4*6#";

    opnd = EvaluateExpression(exp);

    printf("作为示例，%s 的计算结果为：%d\n", exp, opnd-'0');

    printf("\n");

    return 0;
}