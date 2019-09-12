//
//文件夹: 11 External_Sort/02 ReSeSort
//文件名: ReSeSort
//内　容：置换选择排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:39
//Version 1.0
//

#ifndef DATA_STRUCTURE_RESESORT_H
#define DATA_STRUCTURE_RESESORT_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../../01 Introduction/Status.h"            //**01 Introduction**//
#include "../../01 Introduction/Scanf.h"            //**01 Introduction**//

#define RUNEND_SYMBOL INT_MAX                //初始归并段结束标志
#define MAXKEY INT_MAX                        //关键字可能的最大值
#define W 6                                    //工作区缓存

/* 类型定义 */
typedef int KeyType;                        //定义关键字类型为整数类型
typedef struct {
    KeyType key;                            //关键字项
} RcdType;                                    //记录类型
typedef int LoserTree[W];                    //败者树
typedef struct                                //败者树叶节点存储结构
{
    RcdType rec;                            //记录
    KeyType key;                            //从记录中抽取的关键字
    int rnum;                                //所属归并段的段号
} RcdNode;
typedef RcdNode WorkArea[W];                //内存工作区，容量为W

/* 全局变量 */
int part;                                    //统计初始归并段个数
int rmax;                                    //rmax指示wa中关键字所属初始归并段的最大段号
int rc;                                        //rc指示当前生成的初始归并段的段号

/* 置换选择排序函数列表 */
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法11.4：在败者树ls和内存工作区wa上用置换-选择排序求初始归并段,fi为指向文件(只读)，fo指向输出文件(只写)。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void Replace_Selectiom(FILE *fi, LoserTree ls, WorkArea wa);

/*━━━━━━━━━━━━━━━━━┓
┃(02)算法11.5：求得一个初始归并段。┃
┗━━━━━━━━━━━━━━━━━*/
void get_run(FILE *fi, FILE *fo, LoserTree ls, WorkArea wa);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(03)算法11.6：从wa[q]起到败者树的根比较选择minimax记录,并由q指示它所在的归并段。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void Select_MiniMax(LoserTree ls, WorkArea wa, int q);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(04)算法11.7：输入w个记录到内存工作区wa，建得败者树ls，选出关键字最小的记录并由s指示其在wa中的位置。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void Construct_Loser(FILE *fi, LoserTree ls, WorkArea wa);

/*════╗
║算法11.4║
╚════*/
void Replace_Selectiom(FILE *fi, LoserTree ls, WorkArea wa) {
    FILE *fo;
    char str1[100], str2[100], str3[100] = ".txt";

    Construct_Loser(fi, ls, wa);            //初建败者树

    rc = rmax = 1;                            //初始化当前段号和最大段号为1

    system("md tmpfile");                    //创建临时文件夹tmp

    while (rc <= rmax)                            //"rc=rmax+1"标志输入文件的置换-选择排序已完成
    {
        strcpy(str1, "tmpfile/");
        itoa(part, str2, 10);                //[0..k-1]
        strcat(str1, strcat(str2, str3));    //tmpfile/[0..k-1].txt

        fo = fopen(str1, "w+");                //存储各归并段，[0..n-1].txt

        get_run(fi, fo, ls, wa);            //求得一个初始归并段
        fprintf(fo, "%d", RUNEND_SYMBOL);    //将段结束标志写入输出文件
        fclose(fo);
        part++;
        rc = wa[ls[0]].rnum;                //设置下一段的段号
    }
}

void get_run(FILE *fi, FILE *fo, LoserTree ls, WorkArea wa) {
    int q, minimax;

    while (wa[ls[0]].rnum == rc)                        //选得的MINIMAX记录属当前段时
    {
        q = ls[0];                                    //q指示MINIMAX记录在wa中的位置
        minimax = wa[q].key;
        fprintf(fo, "%d，", wa[q].rec.key);            //将刚选好的MINIMAX记录写入输出文件

        //从输入文件读入下一记录
        if (Scanf(fi, "%d", &(wa[q].rec.key)) != 1)    //读取失败，则输入文件结束
        {
            wa[q].rnum = rmax + 1;                    //虚设记录(属“rmax+1”段)
            wa[q].key = MAXKEY;
        } else {
            wa[q].key = wa[q].rec.key;                //提取关键字

            if (wa[q].key < minimax)                    //新读入的记录属于下一段
            {
                rmax = rc + 1;
                wa[q].rnum = rmax;
            } else
                wa[q].rnum = rc;                    //新读入的记录属于当前段
        }

        Select_MiniMax(ls, wa, q);                    //选择新的MINIMAX记录
    }
}

void Select_MiniMax(LoserTree ls, WorkArea wa, int q) {
    int p, t, tmp;

    for (t = (W + q) / 2, p = ls[t]; t > 0; t = t / 2, p = ls[t]) {
        if (wa[p].rnum < wa[q].rnum || wa[p].rnum == wa[q].rnum && wa[p].key < wa[q].key) {
            tmp = q;                                //q指向新的胜利者
            q = ls[t];
            ls[t] = tmp;
        }
    }

    ls[0] = q;
}

void Construct_Loser(FILE *fi, LoserTree ls, WorkArea wa)    //工作区wa是一棵败者树
{
    int i;

    for (i = 0; i < W; i++)
        wa[i].rnum = wa[i].key = ls[i] = 0;            //工作区初始化

    for (i = W - 1; i >= 0; i--) {
        Scanf(fi, "%d", &(wa[i].rec.key));            //输入一个记录
        wa[i].key = wa[i].rec.key;                    //提取关键字
        wa[i].rnum = 1;                                //其段号为“1”
        Select_MiniMax(ls, wa, i);                    //调整败者
    }
}

#endif //DATA_STRUCTURE_RESESORT_H
