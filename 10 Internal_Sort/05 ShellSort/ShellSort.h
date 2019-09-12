//
//文件夹: 10 Internal_Sort/05 ShellSort
//文件名: ShellSort
//内　容：希尔插入排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:13
//Version 1.0
//

#ifndef DATA_STRUCTURE_SHELLSORT_H
#define DATA_STRUCTURE_SHELLSORT_H

#include "../00 SequenceListType/SequenceListType.h"    //**10 Internal_Sort**//

/* 全局变量 */
int t = 3;                                                //增量序列容量
int dlta[] = {5, 3, 1};                                    //增量序列

/* 希尔插入排序函数列表 */
/*━━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法10.4：对顺序表做一趟希尔插入排序。┃
┗━━━━━━━━━━━━━━━━━━━━━*/
void ShellInsert(SqList_sort *L, int dk);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(02)算法10.5：按增量序列dlta[0..t-1]对顺序表L作希尔插入排序。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void ShellSort(SqList_sort *L, int dlta[], int t);

/*════╗
║算法10.4║
╚════*/
void ShellInsert(SqList_sort *L, int dk) {
    int i, j;

    for (i = dk + 1; i <= (*L).length; i++)            //dk为前后记录的位置增量，r[0]作暂存单元
    {
        if (LT((*L).r[i].key, (*L).r[i - dk].key))    //将L.r[i]插入有序增量子表
        {
            (*L).r[0] = (*L).r[i];                //暂存在L.r[0]

            for (j = i - dk; j > 0 && LT((*L).r[0].key, (*L).r[j].key); j -= dk)
                (*L).r[j + dk] = (*L).r[j];        //记录后移，查找插入位置

            (*L).r[j + dk] = (*L).r[0];            //插入
        }
    }
}

/*════╗
║算法10.5║
╚════*/
void ShellSort(SqList_sort *L, int dlta[], int t) {
    int k;

    for (k = 0; k < t; k++)
        ShellInsert(L, dlta[k]);                //一趟增量为dlta[k]的插入排序
}

#endif //DATA_STRUCTURE_SHELLSORT_H
