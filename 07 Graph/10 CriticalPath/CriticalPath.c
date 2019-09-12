//
//文件夹: 07 Graph\10 CriticalPath
//文件名: CriticalPath
//内　容：AOE-网关键路径相关函数测试
//Author Huangcp
//Date 2019/9/13 上午 02:42
//Version 1.0
//

#include "CriticalPath.h"

int main(int argc, char *argv[]) {
    ALGraph G;

    printf("创建并输出有向图(带权)...\n");
    {
        FILE *fp;

        fp = fopen("TestData_DG_AL.txt", "r");
        CreateGraph_AL(fp, &G);
        fclose(fp);
        OutputALGraph(G);
        printf("\n");
    }
    PressEnter;

    printf("▼1、2、3\n▲函数 CriticalPath等 测试...\n");            //1、2、3.函数CriticalPath等测试
    {
        printf("输出并标记AOV-网中的关键路径...\n");
        CriticalPath(G);
        printf("\n");
    }
    PressEnter;

    return 0;
}
