//
//文件夹: 09 Search/03 FibonacciSearch
//文件名: FibonacciSearch
//内　容：斐波那契查找相关函数测试
//Author Huangcp
//Date 2019/9/13 上午 03:21
//Version 1.0
//

#include "FibonacciSearch.h"

#define Max 100                            //查找表中元素个数

int main(int argc, char *argv[]) {
    Table T;

    printf("创建并输出一个查找表...\n");
    {
        FILE *fp;

        fp = fopen("TestData_Table.txt", "r");
        Create(fp, &T, Max);
        Traverse(T, PrintKey);
        printf("\n");
    }
    PressEnter;

    printf("▼1\n▲函数 Search_Fib 测试...\n");        //1.函数Search_Fib测试
    {
        printf("关键字 39 在有序查找表中的位序为：");
        printf("%d\n", Search_Fib(T, 39));
        printf("\n");
    }
    PressEnter;

    return 0;
}
