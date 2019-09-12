//
//文件夹: 02 Linear_List/05 MergeList
//文件名: MergeList
//内　容：单链表归并相关操作列表
//Author Huangcp
//Date 2019/9/10 上午 12:26
//Version 1.0
//

#ifndef DATA_STRUCTURE_MERGELIST_H
#define DATA_STRUCTURE_MERGELIST_H

#include <stdlib.h>                                        //提供malloc、realloc、free、exit原型
#include "../04 SinglyLinkedList/SinglyLinkedList.h"    //**▲02 线性表**//
/* 单链表归并函数列表 */
/*━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法2.12：C=A+B，且保持元素相对位置不变。   ┃
┃    Lc利用La的头结点，Lb中结点均插入新链表Lc中。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━*/
void MergeList_L(LinkList La, LinkList *Lb, LinkList *Lc);

/*═════╗
║ 算法2.12 ║ 
╚═════*/
void
MergeList_L(LinkList La, LinkList *Lb, LinkList *Lc) {                                        //指针Lb,Lc要改变，故形参是指向指针的指针 
    LinkList pa, pb, pc;

    pa = La->next;
    pb = (*Lb)->next;
    pc = *Lc = La;                        //用La的头结点作为Lc的头结点 						

    while (pa && pb) {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }

    pc->next = pa ? pa : pb;            //插入剩余段 

    free(*Lb);                            //释放Lb的头结点
    *Lb = NULL;
}

#endif //DATA_STRUCTURE_MERGELIST_H
