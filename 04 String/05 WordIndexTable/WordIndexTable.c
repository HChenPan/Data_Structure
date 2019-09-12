//
//文件夹: 04 String/05 WordIndexTable
//文件名: WordIndexTable
//内　容：创建索引表相关函数测试
//Author Huangcp
//Date 2019/9/12 上午 01:02
//Version 1.0
//

#include "WordIndexTable.h"

int main(int argc, char **argv) {
    FILE *fp;
    char line[MaxLineLen];

    char *bookinfo = "BookInfo.txt";    //书目文件名
    char *bookidx = "BookIdx.txt";        //关键词索引文件名

    Main(bookinfo, bookidx);            //创建索引表

    if (fp = fopen(bookidx, "r"))        //显示索引表到屏幕
        printf("---------索引表生成功！---------\n\n");
    while (!feof(fp)) {
        fgets(line, MaxLineLen, fp);
        printf("%s", line);
    }
    printf("\n\n-------------------------------\n\n");

    Wait(50);
    system("start BookInfo.txt");        //打开书目文件
    Wait(50);
    system("start BookIdx.txt");        //打开上面生成的索引表

    return 0;
}
