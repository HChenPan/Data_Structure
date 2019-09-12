//
//文件夹: 12 File/01 SequentialFile
//文件名: MergeFile
//内　容：文件归并相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:42
//Version 1.0
//

#ifndef DATA_STRUCTURE_MERGEFILE_H
#define DATA_STRUCTURE_MERGEFILE_H

#include <stdio.h>
#include "../../01 Introduction/Status.h"            //**01 Introduction**//

/* 文件类型定义 */
typedef struct                //主文件
{
    int key;                //账号
    int balance;            //余额
} MainFile;
typedef struct                //事务文件
{
    char code;                //操作：I-插入，D删去，U更改
    int key;                //账号
    int money;                //金额变动，存"+"，取"-"
} AffairFile;

/* 文件归并函数列表 */
/*━━━━━━━━━━━━━━━━━┓
┃(01)初始化一个主文件f和事务文件g。┃
┗━━━━━━━━━━━━━━━━━*/
void InitFile(FILE *f, FILE *g);

/*━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(02)根据读到的主文件记录与事务记录，判断当前情形。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━*/
int Situation(MainFile fr, AffairFile gr);

/*━━━━━━━━━━━━━━━━━━━━┓
┃(03)将事务记录类型转换为主文件记录类型。┃
┗━━━━━━━━━━━━━━━━━━━━*/
MainFile P(AffairFile gr);

/*━━━━━━━━━━━━━━━━┓
┃(04)根据事务记录修改主文件记录。┃
┗━━━━━━━━━━━━━━━━*/
MainFile Q(MainFile fr, AffairFile gr);

/*━━━━━━━━━━━━━━━━━━━┓
┃(05)将发生错误的事务记录写入日志文件。┃
┗━━━━━━━━━━━━━━━━━━━*/
void Error(AffairFile gr, FILE *log);

/*━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(06)算法12.1：归并主文件f和事务记录g到新的文件h。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━*/
void MergeFile(FILE *f, FILE *g, FILE *h, FILE *log);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(07)输出记录，mark=0表示输出文件记录，mark=1表示输出事务记录。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void Print(FILE *fp, int mark);

void InitFile(FILE *f, FILE *g) {
    MainFile fr[7] = {1, 50, 5, 78, 12, 100, 14, 95, 15, 360, 18, 200, 20, 510};                    //主文件
    AffairFile gr[5] = {'I', 8, +100, 'U', 12, -25, 'U', 14, +38, 'D', 18, -200, 'I', 21, +60};    //事务文件

    fwrite(&fr[0], sizeof(fr[0]), 7, f);
    fwrite(&gr[0], sizeof(AffairFile), 5, g);

    fclose(f);
    fclose(g);
}

int Situation(MainFile fr, AffairFile gr) {
    if (fr.key < gr.key)        //情形1：复制"旧"主文件中的记录
        return 1;

    if (fr.key == gr.key) {
        if (gr.code == 'D')    //情形2：删除"旧"主文件记录，即不复制
            return 2;

        if (gr.code == 'U')    //情形3：更改"旧"主文件中记录
            return 3;
    }

    if (fr.key > gr.key) {
        if (gr.code == 'I')    //情形4：插入事务到主文件
            return 4;
    }

    return 0;                //其他情形，返回错误
}

MainFile P(AffairFile gr) {
    MainFile tmp;

    tmp.key = gr.key;
    tmp.balance = gr.money;

    return tmp;
}

MainFile Q(MainFile fr, AffairFile gr) {
    MainFile tmp;

    tmp.key = fr.key;
    tmp.balance = fr.balance + gr.money;

    return tmp;
}

void Error(AffairFile gr, FILE *log)            //事务文件发生错误
{
    log = fopen("ErrorLog.file", "a+");
    fwrite(&gr, sizeof(AffairFile), 1, log);    //将错误事务写入日志
    fclose(log);
}

/*════╗
║算法12.1║
╚════*/
void MergeFile(FILE *f, FILE *g, FILE *h, FILE *log) {
    int tag, ftag, gtag;
    MainFile fr, tmp;                                            //主文件
    AffairFile gr;                                                //事务文件

    ftag = gtag = 0;

    ftag = fread(&fr, sizeof(MainFile), 1, f);
    gtag = fread(&gr, sizeof(AffairFile), 1, g);

    while (ftag == 1 && gtag == 1)                                        //读取成功
    {
        tag = Situation(fr, gr);

        switch (tag) {
            case 1:                                                //复制"旧"主文件中记录
                fwrite(&fr, sizeof(MainFile), 1, h);
                ftag = fread(&fr, sizeof(MainFile), 1, f);
                break;

            case 2:                                                //删除"旧"主文件记录，即不复制
                ftag = fread(&fr, sizeof(MainFile), 1, f);
                gtag = fread(&gr, sizeof(AffairFile), 1, g);
                break;

            case 3:                                                //更改"旧"主文件中记录
                tmp = Q(fr, gr);
                fwrite(&tmp, sizeof(MainFile), 1, h);            //函数Q将fr和gr归并成一个h结构的记录
                ftag = fread(&fr, sizeof(MainFile), 1, f);
                gtag = fread(&gr, sizeof(AffairFile), 1, g);
                break;

            case 4:                                                //插入，函数P把gr加工为h的结构
                tmp = P(gr);
                fwrite(&tmp, sizeof(MainFile), 1, h);
                gtag = fread(&gr, sizeof(AffairFile), 1, g);
                break;

            default:
                Error(gr, log);
                gtag = fread(&gr, sizeof(AffairFile), 1, g);    //读取下一条事务
        }
    }

    while (ftag == 0 && gtag == 1)                                        //主文件读完
    {
        if (gr.code == 'I')                                        //只能是"插入"这种情形
        {
            tmp = P(gr);
            fwrite(&tmp, sizeof(MainFile), 1, h);
        } else
            Error(gr, log);

        gtag = fread(&gr, sizeof(AffairFile), 1, g);            //读取下一条事务
    }

    while (ftag == 1 && gtag == 0)                                        //事务文件读完
    {
        fwrite(&fr, sizeof(MainFile), 1, h);
        ftag = fread(&fr, sizeof(MainFile), 1, f);
    }

    fclose(f);
    fclose(g);
    fclose(h);
}

void Print(FILE *fp, int mark) {
    MainFile fr;
    AffairFile gr;

    if (mark == 0)            //输出文件记录
    {
        while (fread(&fr, sizeof(MainFile), 1, fp) == 1)
            printf("(%d，%d) ", fr.key, fr.balance);
    } else                //输出事务记录
    {
        while (fread(&gr, sizeof(AffairFile), 1, fp) == 1)
            printf("(%d，%d，%c) ", gr.key, gr.money, gr.code);
    }

    fclose(fp);

    printf("\n");
}

#endif //DATA_STRUCTURE_MERGEFILE_H
