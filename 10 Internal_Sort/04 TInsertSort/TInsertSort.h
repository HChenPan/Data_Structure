//
//文件夹: 10 Internal_Sort/04 TInsertSort
//文件名: TInsertSort
//内　容：表插入排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:13
//Version 1.0
//

#ifndef DATA_STRUCTURE_TINSERTSORT_H
#define DATA_STRUCTURE_TINSERTSORT_H

#include "../00 StaticLinkedListType/StaticLinkedListType.h"    //**10 Internal_Sort**//

/* 表插入排序函数列表 */
/**
(01)对静态链表L作表插入排序。 
**/
void TInsertSort(SLinkList_sort *L);

/**
(02)算法10.3：根据各记录指针，对L中的记录重新排序。 
**/
void Arrange(SLinkList_sort *L);

void TInsertSort(SLinkList_sort *L) {
    int i, j, k;

    for (i = 1; i <= (*L).length; i++)        //对指针进行排序
    {
        for (k = 0, j = (*L).r[k].next; j && LT((*L).r[j].rc.key, (*L).r[i].rc.key); k = j, j = (*L).r[k].next);

        (*L).r[i].next = j;
        (*L).r[k].next = i;
    }

    Arrange(L);                            //对记录进行排序
}

/**
算法10.3
**/
void Arrange(SLinkList_sort *L) {
    int p, q, i;
    SLNode tmp;

    p = (*L).r[0].next;                    //p只是第一个记录的当前位置

    for (i = 1; i <= (*L).length; i++)        //L.r[1..i-1]中记录已按关键字有序排列
    {                                    //第i个记录在L中的当前位置应不小于i
        while (p < i)                        //找到第i个记录，并用p指示其在L中当前位置
            p = (*L).r[p].next;

        q = (*L).r[p].next;                //q指示尚未调整的表尾

        if (p != i) {
            tmp = (*L).r[p];            //交换记录，使第i个记录到位
            (*L).r[p] = (*L).r[i];
            (*L).r[i] = tmp;

            (*L).r[i].next = p;            //指向被移走的记录，使得以后可由while循环找回
        }

        p = q;                            //p指示尚未调整的表尾，为找第i+1个记录作准备
    }
}

#endif //DATA_STRUCTURE_TINSERTSORT_H
