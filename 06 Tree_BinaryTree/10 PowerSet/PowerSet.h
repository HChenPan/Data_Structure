//
//文件夹: 06 Tree_BinaryTree/10 PowerSet
//文件名: PowerSet
//内　容：幂集相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 02:15
//Version 1.0
//

#ifndef DATA_STRUCTURE_POWERSET_H
#define DATA_STRUCTURE_POWERSET_H

#include <stdio.h>
#include "../../01 Introduction/Status.h"                    //**01 Introduction**//
#include "../../01 Introduction/Scanf.h"                    //**01 Introduction**//
#include "../../02 Linear_List/04 SinglyLinkedList/SinglyLinkedList.h"    //**02 Linear_List**//

/* 幂集类型定义 */
typedef LElemType_L PElemType;

/* 幂集函数列表 */
/**
(01)创建集合A，集合元素为int。
**/
Status CreatePowerSet_PS(FILE *fp, LinkList *A);

/**
(02)算法6.14 && 6.15：求取集合A的幂集，集合B暂存每一次求出的幂集子集。
**/
void GetPowerSet_PS(int i, LinkList A, LinkList B);

/**
(03)构造空树HT(初始化树)。
**/
void Output_PS(LinkList A);


Status CreatePowerSet_PS(FILE *fp, LinkList *A) {
    int i, j;
    PElemType e;                                //集合元素类型为int

    InitList_L(A);
    Scanf(fp, "%d", &j);
    printf("录入集合 A 的元素个数 %d...\n", j);

    for (i = 1; i <= j; i++) {
        Scanf(fp, "%d", &e);
        printf("录入第 %d 个元素：%d\n", i, e);
        ListInsert_L(*A, i, e);
    }

    return OK;
}

/**
 算法6.14 && 6.15 
**/
void GetPowerSet_PS(int i, LinkList A, LinkList B) {
    int k;
    LElemType_L x;

    if (i > ListLength_L(A))
        Output_PS(B);
    else {
        GetElem_L(A, i, &x);
        k = ListLength_L(B);

        ListInsert_L(B, k + 1, x);                //+第i个元素
        GetPowerSet_PS(i + 1, A, B);

        ListDelete_L(B, k + 1, &x);                //-第i个元素
        GetPowerSet_PS(i + 1, A, B);
    }
}

void Output_PS(LinkList A) {
    LinkList p;
    int len = ListLength_L(A);

    if (len) {
        for (p = A->next; p; p = p->next)
            printf("%d ", p->data);
    } else
        printf("⊙");

    printf("\n");
}

#endif //DATA_STRUCTURE_POWERSET_H
