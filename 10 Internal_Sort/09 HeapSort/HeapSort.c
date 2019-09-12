//
//文件夹: 10 Internal_Sort/09 HeapSort
//文件名: HeapSort
//内　容：堆排序相关函数测试
//Author Huangcp
//Date 2019/9/13 上午 04:14
//Version 1.0
//

#include "HeapSort.h"

void PrintKey(KeyType e);

int main(int argc, char *argv[]) {
    HeapType H;

    printf("创建并输出一个任意序列...\n");
    {
        FILE *fp;

        fp = fopen("TestData.txt", "r");
        CreateSortList(fp, &H);
        Traverse(H, PrintKey);
        printf("\n");
    }
    PressEnter;

    printf("▼1、2\n▲函数 HeapSort等 测试...\n");            //1、2.函数HeapSort等测试
    {
        printf("将关键字按递增顺序排列...\n");
        HeapSort(&H);
        Traverse(H, PrintKey);
        printf("\n");
    }
    PressEnter;

    return 0;
}

void PrintKey(KeyType e) {
    printf("%d ", e);
}
