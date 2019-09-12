//
//文件夹: 10 Internal_Sort/11 RadixSort
//文件名: RadixSort
//内　容：基数排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:14
//Version 1.0
//

#ifndef DATA_STRUCTURE_RADIXSORT_H
#define DATA_STRUCTURE_RADIXSORT_H

#include <stdio.h>
#include "../../01 Introduction/Status.h"            //**01 Introduction**//
#include "../../01 Introduction/Scanf.h"            //**01 Introduction**//

#define MAX_NUM_OF_KEY 8                    //关键字项数的最大值
#define RADIX 10                            //关键字基数，此时是十进制整数的基数
#define MAX_SPACE 10000

#define ord(ch) ((ch)-'0')
#define succ(x) ((x)+1)

/* 静态链表的结点类型 */
typedef char KeysType;
typedef struct {
    KeysType keys[MAX_NUM_OF_KEY];            //关键字
    int next;
} SLCell;

/* 静态链表类型 */
typedef struct {
    SLCell r[MAX_SPACE];                    //静态链表的可利用空间，r[0]为头结点
    int keynum;                                //记录的当前关键字个数
    int recnum;                                //静态链表当前长度
} SLList;

/* 指针数组类型 */
typedef int ArrType[RADIX];                    //指针数组类型

/* 基数排序函数列表 */
/*━━━━━━━━━━┓
┃(01)创建静态链表L。 ┃
┗━━━━━━━━━━*/
void CreateSLList(FILE *fp, SLList *L);

/*━━━━━━━━━━━━━━━━━┓
┃(02)输出静态链表L中的关键字记录。 ┃
┗━━━━━━━━━━━━━━━━━*/
void Traverse(SLList L);

/*━━━━━━━━━━━━━━━━━━━┓
┃(03)算法10.17：对静态链表L作基数排序。┃
┗━━━━━━━━━━━━━━━━━━━*/
void RadixSort(SLList *L);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(04)算法10.15：分配算法，按第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void Distribute(SLCell *r, int i, ArrType f, ArrType e);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(05)算法10.16：收集算法，按keys[i]从小到大地将f[0..RADIX-1]所指各子表依次链接成一个链表。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void Collect(SLCell *r, int i, ArrType f, ArrType e);

void CreateSLList(FILE *fp, SLList *L) {
    int i;
    char s[1000];

    Scanf(fp, "%d", &((*L).keynum));            //关键字个数

    (*L).recnum = 0;                            //静态链表当前长度

    while (Scanf(fp, "%s", &s) == 1) {
        (*L).recnum++;

        for (i = 0; i < (*L).keynum; i++)            //按低位到高位的顺序将关键字存储到keys
            (*L).r[(*L).recnum].keys[(*L).keynum - 1 - i] = s[i];
    }

    for (i = 0; i < (*L).recnum; i++)                //将L改造为静态链表（循环）
        (*L).r[i].next = i + 1;
    (*L).r[(*L).recnum].next = 0;
}

void Traverse(SLList L) {
    int i, j;

    for (i = L.r[0].next; i; i = L.r[i].next) {
        for (j = L.keynum - 1; j >= 0; j--)
            printf("%c", L.r[i].keys[j]);

        printf(" ");
    }

    printf("\n");
}

/*═════╗
║ 算法10.17║
╚═════*/
void RadixSort(SLList *L) {
    int i;
    ArrType f, e;

    for (i = 0; i < (*L).keynum; i++)                //按最低位优先依次对各关键字进行分配和收集
    {
        Distribute((*L).r, i, f, e);            //第i趟分配
        Collect((*L).r, i, f, e);                //第i趟收集
    }
}

/*═════╗
║ 算法10.15║
╚═════*/
void Distribute(SLCell r[], int i, ArrType f, ArrType e) {
    int j, p;

    for (j = 0; j < RADIX; j++)                        //各子表初始化为空表
    {
        f[j] = 0;
        e[j] = 0;
    }

    for (p = r[0].next; p; p = r[p].next) {
        j = ord(r[p].keys[i]);                    //ord将记录中第i个关键字映射到[0..RADIX-1]

        if (!f[j])
            f[j] = p;
        else
            r[e[j]].next = p;

        e[j] = p;                                //将p所指的结点插入第j个子表中
    }
}

/*═════╗
║ 算法10.16║
╚═════*/
void Collect(SLCell r[], int i, ArrType f, ArrType e) {
    int j, t;

    for (j = 0; j < RADIX && !f[j]; j = succ(j))            //找第一个非空子表，succ为求后继函数
        ;

    if (j < RADIX) {
        r[0].next = f[j];                        //r[0].next指向第一个非空子表中第一个结点
        t = e[j];

        while (j < RADIX) {
            for (j = succ(j); j < RADIX - 1 && !f[j]; j = succ(j));                                //寻找下一个非空子表

            if (f[j] && j <= RADIX - 1)                //链接两个非空子表
            {
                r[t].next = f[j];
                t = e[j];
            }
        }

        r[t].next = 0;                            //t指向最后一个非空子表中的最后一个结点
    }
}

#endif //DATA_STRUCTURE_RADIXSORT_H
