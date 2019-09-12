//
//文件夹: 10 Internal_Sort/03 2-InsertSort
//文件名: 2-InsertSort
//内　容：2-路插入排序相关函数测试
//Author Huangcp
//Date 2019/9/13 上午 04:13
//Version 1.0
//

#include "2-InsertSort.h"

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

    printf("▼1\n▲函数 TwoTayInsertSort 测试...\n");    //1.函数TwoTayInsertSort测试
    {
        printf("将关键字按递增顺序排列...\n");
        TwoTayInsertSort(&L);
        Traverse(L, PrintKey);
        printf("\n");
    }
    PressEnter;

    return 0;
}

void PrintKey(KeyType e) {
    printf("%d ", e);
}
