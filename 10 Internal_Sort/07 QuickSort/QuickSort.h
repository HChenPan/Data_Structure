//
//文件夹: 10 Internal_Sort/07 QuickSort
//文件名: QuickSort
//内　容：快速排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:14
//Version 1.0
//

#ifndef DATA_STRUCTURE_QUICKSORT_H
#define DATA_STRUCTURE_QUICKSORT_H

#include "../00 SequenceListType/SequenceListType.h"    //**10 Internal_Sort**//

/* 快速排序函数列表 */
/*━━━━━━━━━━━━━━━━━━┓
┃(01)算法10.6(a)：完成一趟快速排序。 ┃
┗━━━━━━━━━━━━━━━━━━*/
int Partition_1(SqList_sort *L, int low, int high);

/*━━━━━━━━━━━━━━━━━━┓
┃(02)算法10.6(b)：完成一趟快速排序。 ┃
┗━━━━━━━━━━━━━━━━━━*/
int Partition_2(SqList_sort *L, int low, int high);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(03)算法10.8：对顺序表L中的子序列L.r[low..high]作快速排序。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void QSort(SqList_sort *L, int low, int high);

/*━━━━━━━━━━━━━━━━━━┓
┃(04)算法10.7：对顺序表L作快速排序。 ┃
┗━━━━━━━━━━━━━━━━━━*/
void QuickSort(SqList_sort *L);

/*══════╗
║ 算法10.6(a)║
╚══════*/
int Partition_1(SqList_sort *L, int low, int high) {
    int pivotkey;
    RcdType tmp;

    pivotkey = (*L).r[low].key;                    //用子表第一个记录作枢轴记录

    while (low < high)                                //从表的两端交替地向中间扫描
    {
        while (low < high && (*L).r[high].key >= pivotkey)
            high--;

        tmp = (*L).r[high];                        //将比枢轴记录小的记录交换到低端
        (*L).r[high] = (*L).r[low];
        (*L).r[low] = tmp;

        while (low < high && (*L).r[low].key <= pivotkey)
            low++;

        tmp = (*L).r[high];                        //将比枢轴记录大的记录交换到高端
        (*L).r[high] = (*L).r[low];
        (*L).r[low] = tmp;
    }

    return low;                                    //返回枢轴所在位置
}

/*══════╗
║ 算法10.6(b)║
╚══════*/
int Partition_2(SqList_sort *L, int low, int high) {
    int pivotkey;

    (*L).r[0] = (*L).r[low];                    //用子表第一个记录作枢轴记录
    pivotkey = (*L).r[low].key;                    //枢轴记录关键字

    while (low < high)                                //从表的两端交替地向中间扫描
    {
        while (low < high && (*L).r[high].key > pivotkey)
            high--;

        (*L).r[low] = (*L).r[high];                //将比枢轴记录小的记录交换到低端

        while (low < high && (*L).r[low].key <= pivotkey)
            low++;

        (*L).r[high] = (*L).r[low];                //将比枢轴记录大的记录交换到高端
    }

    (*L).r[low] = (*L).r[0];                    //枢轴记录到位

    return low;                                    //返回枢轴所在位置
}

/*════╗
║算法10.7║
╚════*/
void QSort(SqList_sort *L, int low, int high) {
    int pivotloc;

    if (low < high)                                //长度大于1
    {
        //	pivotloc = Partition_1(L, low, high);	//将(*L).r[row..high]一分为二

        pivotloc = Partition_2(L, low, high);    //将(*L).r[row..high]一分为二

        QSort(L, 1, pivotloc - 1);                //对低子表递归排序，pivotloc是枢轴位置
        QSort(L, pivotloc + 1, high);                //对高子表递归排序
    }
}

/*════╗
║算法10.8║
╚════*/
void QuickSort(SqList_sort *L) {
    QSort(L, 1, (*L).length);
}


#endif //DATA_STRUCTURE_QUICKSORT_H
