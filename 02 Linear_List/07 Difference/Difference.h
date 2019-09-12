//
//文件夹: 02 Linear_List/07 Difference
//文件名: Difference
//内　容：算法2.17相关操作列表
//Author Huangcp
//Date 2019/9/10 上午 12:51
//Version 1.0
//

#ifndef DATA_STRUCTURE_DIFFERENCE_H
#define DATA_STRUCTURE_DIFFERENCE_H

#include <stdio.h>
#include "../../01 Introduction/Scanf.h"                            //**▲01 绪论**//
#include "../06 StaticLinkedList/StaticLinkedList.h"        //**▲02 线性表**//
/* 算法2.17函数列表 */

/*━━━━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法2.17：在一维数组中建立集合(A-B)∪(B-A)┃
┗━━━━━━━━━━━━━━━━━━━━━━━*/
void difference(SLinkList *S, LElemType_S A[], int len_A, LElemType_S B[], int len_B);

/*═════╗
║ 算法2.17 ║ 
╚═════*/
void difference(SLinkList *S, LElemType_S A[], int len_A, LElemType_S B[], int len_B) {
    int i, j;
    int r, p, k;
    LElemType_S b;

    InitSpace_SL();
    *S = Malloc_SL();                        //头结点 
    r = *S;                                    //r指向S的当前最后结点（尾指针） 
    SPACE[r].cur = 0;

    for (j = 0; j < len_A; j++)                    //建立集合A的链表 
    {
        i = Malloc_SL();                    //申请结点 
        SPACE[i].data = A[j];                //录入A的元素值	 
        SPACE[r].cur = i;                    //插入到表尾 
        r = i;
    }
    SPACE[r].cur = 0;                        //尾结点指针为空

    for (j = 0; j < len_B; j++)                    //录入B的元素值
    {
        b = B[j];
        p = *S;                                //p指向集合A的头结点
        k = SPACE[*S].cur;                    //k指向集合A的第一个结点
        while (k && SPACE[k].data != b) {                                    //在集合A中查找b 
            p = k;
            k = SPACE[k].cur;
        }

        if (!k)                                //A中找不到b，则将b插入A
        {                                    //新增元素将插入r结点的尾部
            i = Malloc_SL();
            SPACE[i].data = b;
            SPACE[i].cur = SPACE[r].cur;
            SPACE[r].cur = i;                //r始终指向最后从A中插入的元素	
        } else                                //A中存在b，则将b从A中删除 
        {
            SPACE[p].cur = SPACE[k].cur;
            Free_SL(k);
            if (k == r)
                r = p;
        }
    }
}

#endif //DATA_STRUCTURE_DIFFERENCE_H
