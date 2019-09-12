//
//文件夹: 10 Internal_Sort/08 SelectSort
//文件名: SelectSort
//内　容：简单选择排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:14
//Version 1.0
//

#ifndef DATA_STRUCTURE_SELECTSORT_H
#define DATA_STRUCTURE_SELECTSORT_H

#include "../00 SequenceListType/SequenceListType.h"//**10 Internal_Sort**//

/* 简单选择排序函数列表 */
/*━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法10.9：对顺序表L作简单选择排序。 ┃
┗━━━━━━━━━━━━━━━━━━━━*/
void SelectSort(SqList_sort *L);

/*━━━━━━━━━━━━━━━━━━━━━━┓
┃(02)在L.r[i..L.length]中选择key最小的记录。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━*/
int SelectMinKey(SqList_sort L, int i);

/*════╗
║算法10.9║
╚════*/
void SelectSort(SqList_sort *L) {
    int i, j;
    RcdType tmp;

    for (i = 1; i < (*L).length; i++) {
        j = SelectMinKey(*L, i);

        if (i != j) {
            tmp = (*L).r[i];
            (*L).r[i] = (*L).r[j];
            (*L).r[j] = tmp;
        }
    }
}

int SelectMinKey(SqList_sort L, int i) {
    int min, k;

    min = i;
    L.r[0] = L.r[i];

    for (k = i; k <= L.length; k++) {
        if (L.r[k].key < L.r[0].key) {
            min = k;
            L.r[0] = L.r[k];
        }
    }

    return min;
}


#endif //DATA_STRUCTURE_SELECTSORT_H
