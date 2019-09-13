//
//文件夹: 10 Internal_Sort/06 BubbleSort
//文件名: BubbleSort
//内　容：起泡排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:13
//Version 1.0
//

#ifndef DATA_STRUCTURE_BUBBLESORT_H
#define DATA_STRUCTURE_BUBBLESORT_H

#include "../00 SequenceListType/SequenceListType.h"    //**10 Internal_Sort**//

/* 起泡排序函数列表 */
/**
(01)对顺序表L作起泡排序。 
**/
void BubbleSort(SqList_sort *L);

void BubbleSort(SqList_sort *L) {
    int i, j;
    RcdType tmp;
    Status tag;

    for (i = (*L).length; i >= 2; i--) {
        tag = FALSE;                    //tag标记遍历过程是否发生的交换

        for (j = 1; j <= i - 1; j++) {
            if (LT((*L).r[j + 1].key, (*L).r[j].key)) {
                tmp = (*L).r[j + 1];
                (*L).r[j + 1] = (*L).r[j];
                (*L).r[j] = tmp;

                tag = TRUE;                //若遍历不发生交换，说明序列已经有序
            }
        }

        if (!tag)
            break;
    }
}

#endif //DATA_STRUCTURE_BUBBLESORT_H
