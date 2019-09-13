//
//文件夹: 10 Internal_Sort/01 InsertSort
//文件名: InsertSort
//内　容：直接插入排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:12
//Version 1.0
//

#ifndef DATA_STRUCTURE_INSERTSORT_H
#define DATA_STRUCTURE_INSERTSORT_H

#include "../00 SequenceListType/SequenceListType.h"    //**10 Internal_Sort**//

/* 直接插入排序函数列表 */
/**
(01)算法10.1：对顺序表L作直接插入排序。 
**/
void InsertSort(SqList_sort *L);

/**
算法10.1
**/
void InsertSort(SqList_sort *L) {
    int i, j;

    for (i = 2; i <= (*L).length; i++) {
        if (LT((*L).r[i].key, (*L).r[i - 1].key))        //"<"，需将L.r[i]插入有序子表
        {
            (*L).r[0] = (*L).r[i];                    //复制为哨兵
            (*L).r[i] = (*L).r[i - 1];
            for (j = i - 1; LT((*L).r[0].key, (*L).r[j].key); --j)
                (*L).r[j + 1] = (*L).r[j];            //记录后移
            (*L).r[j + 1] = (*L).r[0];                //插入到正确位置
        }
    }
}

#endif //DATA_STRUCTURE_INSERTSORT_H
