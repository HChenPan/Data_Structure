//
//文件夹: 08 Dynamic_Storage_Management/02 BuddySystem
//文件名: BuddySystem
//内　容：伙伴系统
//Author Huangcp
//Date 2019/9/13 上午 02:59
//Version 1.0
//

#ifndef DATA_STRUCTURE_BUDDYSYSTEM_H
#define DATA_STRUCTURE_BUDDYSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../01 Introduction/Status.h"                            //**01 Introduction**//

/* 宏定义 */
#define M 3                        //可利用空间总容量64k字的2的幂次，子表的个数为M+1

/* 类型定义 */
typedef struct WORD_b {
    struct WORD_b *llink;        //指向前驱结点
    int tag;                    //块标志，0空闲，1占用
    int kval;                    //块大小，值为2的幂次k
    struct WORD_b *rlink;        //头部域，指向后继结点
} WORD_b;                        //WORD_b：内存字类型，结点的第一个字也称为head
typedef struct HeadNode {
    int nodesize;                //该链表的空闲块的大小
    WORD_b *first;                //该链表的表头指针
} FreeList[M + 1];                    //表头向量类型

/* 全局变量 */
WORD_b *start, *end;            //内存起点和终点

/* 伙伴系统函数列表 */
/**
(01)初始化一块空闲内存块。
**/
void InitSpace_b(FreeList avail);

/**
(02)算法8.2：分配算法。 
**/
WORD_b *AllocBuddy(FreeList avail, int n);

/**
(03)返回p处内存块的伙伴内存块地址。 
**/
WORD_b *Buddy(WORD_b *p);

/**
(04)回收算法。
**/
void Reclaim_b(FreeList avail, WORD_b **p);

/**
(05)输出当前空闲内存块起止地址。
**/
void PrintLayout_b(FreeList avail);


void InitSpace_b(FreeList avail) {
    int k;
    WORD_b *r;

    for (k = 0; k <= M; k++) {
        avail[k].nodesize = (int) pow(2, k);
        avail[k].first = NULL;
    }

    r = (WORD_b *) malloc((int) pow(2, M) * sizeof(WORD_b));
    if (!r)
        exit(OVERFLOW);
    r->llink = r->rlink = r;
    r->tag = 0;
    r->kval = M;

    avail[M].first = r;

    start = r;
    end = r + avail[M].nodesize - 1;
}

/**
 算法8.2
**/
WORD_b *AllocBuddy(FreeList avail, int n)    //avail[0..m]为可利用空间表，n为申请分配量
{                                            //包括标志在内分配n个内存
    int k, i;
    WORD_b *pa, *pre, *suc, *pi;

    for (k = 0;
         k <= M && (avail[k].nodesize < n || !avail[k].first); k++);                                    //查找满足分配要求的子表

    if (k > M)
        return NULL;                        //分配失败，返回NULL
    else                                    //进行分配
    {
        pa = avail[k].first;                //指向可分配子表的第一个结点
        pre = pa->llink;                    //分别指向前驱和后继
        suc = pa->rlink;

        if (pa == suc)
            avail[k].first = NULL;
        else {
            pre->rlink = suc;
            suc->llink = pre;
            avail[k].first = suc;
        }

        for (i = 1; k - i >= 0 && avail[k - i].nodesize >= n; i++) {
            pi = pa + (int) pow(2, k - i);
            pi->rlink = pi;
            pi->llink = pi;
            pi->tag = 0;
            pi->kval = k - i;
            avail[k - i].first = pi;
        }

        pa->tag = 1;
        pa->kval = k - (--i);
    }

    return pa;
}

WORD_b *Buddy(WORD_b *p)    //start原始空闲块起点
{
    int s, m, n;

    s = p - start;
    m = (int) pow(2, p->kval);
    n = (int) pow(2, p->kval + 1);

    if (s % n == 0)
        return p + m;

    if (s % n == m)
        return p - m;
}

void Reclaim_b(FreeList avail, WORD_b **p) {
    WORD_b *s;

    s = Buddy(*p);            //s指向p的伙伴的地址

    while (s >= start && s <= end && s->tag == 0 && s->kval == (*p)->kval) {
        if (s->llink == s && s->rlink == s)        //链表上仅此一个结点
            avail[s->kval].first = NULL;
        else {
            s->llink->rlink = s->rlink;
            s->rlink->llink = s->llink;

            if (avail[s->kval].first == s)                    //s是链表的首结点
                avail[s->kval].first = s->rlink;
        }

        if ((int) (*p - start) % (int) pow(2, (*p)->kval + 1) == 0)    //p为前块
            (*p)->kval++;
        else {
            s->kval = (*p)->kval + 1;
            *p = s;
        }

        s = Buddy(*p);
    }

    (*p)->tag = 0;
    if (avail[(*p)->kval].first == NULL)
        avail[(*p)->kval].first = (*p)->llink = (*p)->rlink = *p;
    else {
        (*p)->rlink = avail[(*p)->kval].first;
        (*p)->llink = (*p)->rlink->llink;
        (*p)->rlink->llink = *p;
        (*p)->llink->rlink = *p;
        avail[(*p)->kval].first = *p;
    }

    *p = NULL;
}

void PrintLayout_b(FreeList avail) {
    int k;
    WORD_b *r;
    int mark;

    for (k = 0, mark = 0; k <= M; k++)        //判断内存是否被占满
    {
        if (avail[k].first) {
            mark = 1;
            break;
        }
    }

    if (!mark)
        printf("内存已被占满！");
    else {
        printf("空闲块起止范围：");
        for (k = 0; k <= M; k++) {
            r = avail[k].first;
            if (r) {
                printf("┃%d←→%d", r - start + 1, r + (int) pow(2, r->kval) - start);
                while (r->rlink != avail[k].first) {
                    r = r->rlink;
                    printf("┃%d←→%d", r - start + 1, r + (int) pow(2, r->kval) - start);
                }
            }
        }
    }
    printf("\n");
}


#endif //DATA_STRUCTURE_BUDDYSYSTEM_H
