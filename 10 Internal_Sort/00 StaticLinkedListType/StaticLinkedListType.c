//
//文件夹: 10 Internal_Sort/00 StaticLinkedListType
//文件名: StaticLinkedListType
//内　容：静态链表相关函数测试
//Author Huangcp
//Date 2019/9/13 上午 04:12
//Version 1.0
//

#include "StaticLinkedListType.h"

void PrintKey(KeyType e);

int main(int argc, char *argv[]) {
    SLinkList_sort L;

    printf("▼1、2\n▲函数 CreateSortList等 测试...\n");    //1、2.函数CreateSortList等测试
    {
        FILE *fp;

        printf("创建并输出一个任意序列...\n");
        fp = fopen("TestData.txt", "r");
        CreateSortList(fp, &L);
        Traverse(L, PrintKey);
        printf("\n");
    }
    PressEnter;

    return 0;
}

void PrintKey(KeyType e) {
    printf("%d ", e);
}
