//
//文件夹: 07 Graph/06 StronglyConnectedComponents
//文件名: StronglyConnectedComponents
//内　容：强连通分量相关函数测试
//Author Huangcp
//Date 2019/9/13 上午 02:41
//Version 1.0
//

#include "StronglyConnectedComponents.h"

int main(int argc, char *argv[]) {
    OLGraph G;

    printf("初始化并输出有向图...\n");
    {
        FILE *fp;

        fp = fopen("TestData_DG_OL.txt", "r");                    //文档中弧的录入为逆序
        CreateDG_OL(fp, &G);
        fclose(fp);
        OutputOLGraph(G);
        printf("\n");
    }
    PressEnter;

    printf("▼1、2、3、4、5\n▲函数 Kosaraju等 测试...\n");        //1、2、3、4、5.函数Kosaraju等测试
    {
        printf("计算此有向图的强连通分量...\n");
        Kosaraju(G);
        printf("\n");
    }
    PressEnter;
}
