//
//文件夹: 10 Internal_Sort/09 HeapSort
//文件名: HeapSort
//内　容：堆排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:14
//Version 1.0
//

#ifndef DATA_STRUCTURE_HEAPSORT_H
#define DATA_STRUCTURE_HEAPSORT_H

#include "../00 SequenceListType/SequenceListType.h"    //**10 Internal_Sort**//

/* 类型定义 */
typedef SqList_sort HeapType;

/* 堆排序函数列表 */
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法10.10：调整H.r[s]的关键字（其他关键字已满足堆的条件），使H.r[s..m]成为一个大顶堆。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void HeapAdjust(HeapType *H, int s, int m);

/*━━━━━━━━━━━━━━━━━┓
┃(02)算法10.11：对顺序表H作堆排序。┃
┗━━━━━━━━━━━━━━━━━*/
void HeapSort(HeapType *H);

/*═════╗
║ 算法10.10║
╚═════*/
void HeapAdjust(HeapType *H, int s, int m) {
    int j;
    RcdType rc;

    rc = (*H).r[s];

    for (j = 2 * s; j <= m; j *= 2)                        //沿key较大的孩子结点向下筛选
    {
        if (j < m && LT((*H).r[j].key, (*H).r[j + 1].key))
            j++;                                //j为key较大的记录的下标

        if (!LT(rc.key, (*H).r[j].key))
            break;                                //rc应插入在位置s上

        (*H).r[s] = (*H).r[j];

        s = j;
    }

    (*H).r[s] = rc;                            //插入
}

/*═════╗
║ 算法10.11║
╚═════*/
void HeapSort(HeapType *H) {
    int i;
    RcdType tmp;

    for (i = (*H).length / 2; i > 0; i--)            //把H.r[1..H.length]建成大顶堆
        HeapAdjust(H, i, (*H).length);

    for (i = (*H).length; i > 1; i--) {
        tmp = (*H).r[1];                    //将堆顶记录和当前未经排序子序列Hr[1..i]中最后一个记录交换
        (*H).r[1] = (*H).r[i];
        (*H).r[i] = tmp;

        HeapAdjust(H, 1, i - 1);                //将H.r[1..i-1]重新调整为大顶堆
    }
}

#endif //DATA_STRUCTURE_HEAPSORT_H
