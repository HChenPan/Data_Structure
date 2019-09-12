//
//文件夹: 11 External_Sort/02 ReSeSort
//文件名: ReSeSort
//内　容：置换选择排序相关函数测试
//Author Huangcp
//Date 2019/9/13 上午 04:39
//Version 1.0
//

#include "ReSeSort.h"

int main(int argc, char *argv[]) {
    FILE *fi;
    LoserTree ls;
    WorkArea wa;

    printf("▼1、2、3、4\n▲函数 Replace_Selectiom等 测试...\n");//1、2、3、4.函数Replace_Selectiom等测试
    {
        printf("将输入文件通过败者树归并到输出文件[0..k-1].txt中...\n");
        printf("可在当前文件夹下查看生成的文件...\n");
        fi = fopen("TestData.txt", "r");                        //读取输入文件
        Replace_Selectiom(fi, ls, wa);                            //分割fi
        printf("\n");
    }
    PressEnter;

    return 0;
}
