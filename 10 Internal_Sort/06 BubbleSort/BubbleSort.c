//
//文件夹: 10 Internal_Sort/06 BubbleSort
//文件名: BubbleSort
//内　容：起泡排序相关函数测试
//Author Huangcp
//Date 2019/9/13 上午 04:13
//Version 1.0
//

#include "BubbleSort.h"

void PrintKey(KeyType e);

int main(int argc, char *argv[]) {
    SqList_sort L;

    printf("创建并输出一个任意序列...\n");
    {
        FILE *fp;

        fp = fopen("TestData.txt", "r");
        CreateSortList(fp, &L);
        Traverse(L, PrintKey);
        printf("\n");
    }
    PressEnter;

    printf("▼1\n▲函数 BubbleSort 测试...\n");                    //1.函数BubbleSort测试
    {
        printf("将关键字按递增顺序排列...\n");
        BubbleSort(&L);
        Traverse(L, PrintKey);
        printf("\n");
    }
    PressEnter;

    return 0;
}

void PrintKey(KeyType e) {
    printf("%d ", e);
}
