//
//文件夹: 10 Internal_Sort/10 MergingSort
//文件名: MergingSort
//内　容：归并排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 04:14
//Version 1.0
//

#ifndef DATA_STRUCTURE_MERGINGSORT_H
#define DATA_STRUCTURE_MERGINGSORT_H

#include "../00 SequenceListType/SequenceListType.h"    //**10 Internal_Sort**//

/* 归并排序函数列表 */
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法10.12：将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void Merge(RcdType SR[], RcdType TR[], int i, int m, int n);

/*━━━━━━━━━━━━━━━━━━━━━━━┓
┃(02)算法10.13：将SR[s..t]归并排序为TR[s..t]。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━*/
void MSort(RcdType SR[], RcdType TR[], int s, int t);

/*━━━━━━━━━━━━━━━━━━┓
┃(03)算法10.14：对顺序表L作归并排序。┃
┗━━━━━━━━━━━━━━━━━━*/
void MergeSort(SqList_sort *L);

/*═════╗
║ 算法10.12║
╚═════*/
void Merge(RcdType SR[], RcdType TR[], int i, int m, int n) {
    int j, k;

    for (j = m + 1, k = i; i <= m && j <= n; ++k)            //将SR中记录由小到大地并入TR
    {
        if (LQ(SR[i].key, SR[j].key))
            TR[k] = SR[i++];
        else
            TR[k] = SR[j++];
    }

    while (i <= m)                                //将剩余的SR[i..m]复制到TR
        TR[k++] = SR[i++];

    while (j <= n)                                //将剩余的SR[j..n]复制到TR
        TR[k++] = SR[j++];
}

/*═════╗
║ 算法10.13║
╚═════*/
void MSort(RcdType SR[], RcdType TR[], int s, int t) {
    int m;
    RcdType R[MAXSIZE + 1];

    if (s == t)
        TR[s] = SR[s];
    else {
        m = (s + t) / 2;                        //将SR[s..t]平分为SR[s..m]和SR[m+1..t]
        MSort(SR, R, s, m);                    //递归地将SR[s..m]归并为有序的R[s..m]
        MSort(SR, R, m + 1, t);                //递归地将SR[m+1..t]归并为有序的R[m+1..t]
        Merge(R, TR, s, m, t);                //将R[s..m]和R[m+1..t]归并到TR[s..t]
    }
}

/*═════╗
║ 算法10.14║
╚═════*/
void MergeSort(SqList_sort *L) {
    MSort((*L).r, (*L).r, 1, (*L).length);
}

#endif //DATA_STRUCTURE_MERGINGSORT_H
