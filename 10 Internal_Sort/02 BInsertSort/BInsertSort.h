//
//文件夹: 10 Internal_Sort/02 BInsertSort
//文件名: BInsertSort
//内　容：折半插入排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:13
//Version 1.0
//

#ifndef DATA_STRUCTURE_BINSERTSORT_H
#define DATA_STRUCTURE_BINSERTSORT_H

#include "../00 SequenceListType/SequenceListType.h"    //**10 Internal_Sort**//

/* 折半插入排序函数列表 */
/*━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法10.2：对顺序表L作折半插入排序。 ┃
┗━━━━━━━━━━━━━━━━━━━━*/
void BInsertSort(SqList_sort *L);

/*════╗
║算法10.2║
╚════*/
void BInsertSort(SqList_sort *L) {
    int i, j, low, high, m;

    for (i = 2; i <= (*L).length; ++i) {
        (*L).r[0] = (*L).r[i];                        //将(*L).r[i]暂存到(*L).r[0]
        low = 1;
        high = i - 1;

        while (low <= high)                            //在r[low..high]中折半查找有序插入的位置
        {
            m = (low + high) / 2;                        //折半

            if (LT((*L).r[0].key, (*L).r[m].key))    //插入点在低半区
                high = m - 1;
            else                                    //插入点在高半区
                low = m + 1;

        }

        for (j = i - 1; j >= high + 1; --j)                    //记录后移
            (*L).r[j + 1] = (*L).r[j];

        (*L).r[high + 1] = (*L).r[0];                    //插入
    }
}

#endif //DATA_STRUCTURE_BINSERTSORT_H
