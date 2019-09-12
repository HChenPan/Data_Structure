//
//文件夹: 02 Linear_List/06 StaticLinkedList
//文件名: StaticLinkedList
//内　容：静态链表相关操作列表
//Author Huangcp
//Date 2019/9/10 上午 12:36
//Version 1.0
//
/*━━━━━━━━━━━━━━━━━━━━━━━━┓
★备注：                                          ┃
★1.为操作方便，特为申请到的空间段设一“头结点”。┃
★2.模拟系统动态申请空间过程。                    ┃
★3.个别操作会与严蔚敏数据结构课本有所差异。      ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━*/

#ifndef DATA_STRUCTURE_STATICLINKEDLIST_H
#define DATA_STRUCTURE_STATICLINKEDLIST_H

#include <stdlib.h>                        ////提供malloc、realloc、free、exit原型
#include "../../01 Introduction/Status.h"        //**▲01 绪论**//

/* 宏定义 */
#define MAXSIZE 1000                    //静态链表的最大长度

/* 静态链表类型定义 */
typedef int SLinkList;                    //静态链表类型
typedef int LElemType_S;
typedef struct {
    LElemType_S data;
    int cur;                            //cur是游标，做指针用，区别于数组下标
} Component[MAXSIZE];                    //链表空间类型

/* 全局变量 */
Component SPACE;                        //静态链表空间

/*	静态链表函数列表 */
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法2.14：将一维数组SPACE中各分量链成一个大的备用空间。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
void InitSpace_SL();

/*━━━━━━━━━━━━━━━━━┓
┃(02)算法2.15：为插入数据申请空间。┃
┗━━━━━━━━━━━━━━━━━*/
int Malloc_SL();

/*━━━━━━━━━━━━━━━━━━━━┓
┃(03)算法2.16：将下标为k的空闲结点回收。 ┃
┗━━━━━━━━━━━━━━━━━━━━*/
void Free_SL(int k);

/*━━━━━━━━━━━━━━━━┓
┃(04)初始化静态链表，建立头结点。┃
┗━━━━━━━━━━━━━━━━*/
int InitList_SL(SLinkList *H);

/*━━━━━┓
┃(05)置空。┃
┗━━━━━*/
Status ClearList_SL(SLinkList H);

/*━━━━━┓
┃(06)销毁。┃
┗━━━━━*/
void DestroyList_SL(SLinkList *H);

/*━━━━━┓
┃(07)判空。┃
┗━━━━━*/
Status ListEmpty_SL(SLinkList H);

/*━━━━━┓
┃(08)求长。┃
┗━━━━━*/
int ListLength_SL(SLinkList H);

/*━━━━━┓
┃(09)取值。┃
┗━━━━━*/
Status GetElem_SL(SLinkList H, int i, LElemType_S *e);

/*━━━━━━━━━━━━━━━━┓
┃(10)算法2.13：返回元素e的位序。 ┃
┗━━━━━━━━━━━━━━━━*/
int LocateElem_SL(SLinkList H, LElemType_S e);

/*━━━━━┓
┃(11)前驱。┃
┗━━━━━*/
Status PriorElem_SL(SLinkList H, LElemType_S cur_e, LElemType_S *pre_e);

/*━━━━━┓
┃(12)后继。┃
┗━━━━━*/
Status NextElem_SL(SLinkList H, LElemType_S cur_e, LElemType_S *next_e);

/*━━━━━┓
┃(13)插入。┃
┗━━━━━*/
Status ListInsert_SL(SLinkList H, int i, LElemType_S e);

/*━━━━━┓
┃(14)删除。┃
┗━━━━━*/
Status ListDelete_SL(SLinkList H, int i, LElemType_S *e);

/*━━━━━┓
┃(15)访问。┃
┗━━━━━*/
Status ListTraverse_SL(SLinkList H, void(Visit)(LElemType_S));


/*═════╗
║ 算法2.14 ║ 
╚═════*/
void InitSpace_SL() {
    //首先初始化备用空间 
    int i;                                //0号单元做备用空间的起始结点 

    for (i = 0; i < MAXSIZE - 1; i++)            //各空间结点首尾相接 
        SPACE[i].cur = i + 1;

    SPACE[MAXSIZE - 1].cur = 0;
}

/*═════╗
║ 算法2.15 ║ 
╚═════*/
int Malloc_SL()                            //从备用空间申请结点空间
{
    int i;

    i = SPACE[0].cur;

    if (SPACE[0].cur) {
        SPACE[0].cur = SPACE[i].cur;    //将申请到的空间从备用空间中删去 
        return i;                        //返回新申请结点下标
    } else
        return 0;                        //申请失败返回0 
}

/*═════╗
║ 算法2.16 ║ 
╚═════*/
void Free_SL(int k)                    //回收k结点空间 
{
    SPACE[k].cur = SPACE[0].cur;
    SPACE[0].cur = k;
}

Status InitList_SL(SLinkList *H)        //H为头结点指针 
{
    *H = Malloc_SL();                    //创建头结点 	
    if (!(*H))
        exit(OVERFLOW);                    //“内存”已满 

    SPACE[*H].cur = 0;                    //头结点游标置为0 

    return OK;
}

Status ClearList_SL(SLinkList H) {
    int p, q;

    if (!H)
        return ERROR;

    p = SPACE[H].cur;                    //p指向第一个结点 

    while (p)                            //从链表首结点开始删除 
    {
        SPACE[H].cur = SPACE[p].cur;
        Free_SL(p);
        p = SPACE[H].cur;
    }

    return OK;
}

void DestroyList_SL(SLinkList *H) {
    ClearList_SL(*H);                    //清空静态链表 

    Free_SL(*H);                            //释放头结点	
    *H = 0;
}

Status ListEmpty_SL(SLinkList H) {
    if (H && !SPACE[H].cur)                //只有头结点 
        return TRUE;
    else
        return FALSE;
}

int ListLength_SL(SLinkList H) {
    int count;                            //计数器
    int p;

    if (!H)
        exit(OVERFLOW);

    count = 0;
    p = SPACE[H].cur;

    while (p) {
        count++;
        p = SPACE[p].cur;
    }

    return count;
}

Status GetElem_SL(SLinkList H, int i, LElemType_S *e) {
    int count, p;

    if (!H || i < 1 || i > MAXSIZE - 2)
        return ERROR;

    count = 0;
    p = SPACE[H].cur;

    while (p) {
        count++;

        if (count == i) {
            *e = SPACE[p].data;
            return OK;
        }

        p = SPACE[p].cur;
    }
}

/*═════╗
║ 算法2.13 ║ 
╚═════*/
int LocateElem_SL(SLinkList H, LElemType_S e) {
    int k, count;

    count = 1;
    if (H && SPACE[H].cur) {
        k = SPACE[H].cur;

        while (k && SPACE[k].data != e) {
            count++;
            k = SPACE[k].cur;
        }

        if (k)
            return count;
    }

    return 0;
}

Status PriorElem_SL(SLinkList H, LElemType_S cur_e, LElemType_S *pre_e) {
    int p, q;

    if (H) {
        p = SPACE[H].cur;

        if (p && SPACE[p].data != cur_e) {
            q = SPACE[p].cur;

            while (q && SPACE[q].data != cur_e) {
                p = q;
                q = SPACE[q].cur;
            }

            if (q)                                //找到了cur_e
            {
                *pre_e = SPACE[p].data;
                return OK;
            }
        }
    }

    return ERROR;
}

Status NextElem_SL(SLinkList H, LElemType_S cur_e, LElemType_S *next_e) {
    int p;

    if (H) {
        p = SPACE[H].cur;

        while (p && SPACE[p].data != cur_e)
            p = SPACE[p].cur;

        if (p && SPACE[p].cur)                    //找到了cur_e且不是最后一个结点 
        {
            p = SPACE[p].cur;
            *next_e = SPACE[p].data;
            return OK;
        }
    }

    return ERROR;
}

Status ListInsert_SL(SLinkList H, int i, LElemType_S e) {
    int count, k, p;

    if (!H)                                //链表不存在 
        return ERROR;

    if (i > 0) {
        count = 0;
        k = H;                            //k指向头结点 

        while (k && count < i - 1)            //寻找插入位置的前一个位置 
        {
            count++;
            k = SPACE[k].cur;
        }

        if (k)                            //找到了第i-1个元素的位置 
        {
            p = Malloc_SL();
            if (!p)                        //申请空间失败 
                return ERROR;

            SPACE[p].data = e;            //插入元素e 
            SPACE[p].cur = SPACE[k].cur;
            SPACE[k].cur = p;

            return OK;
        }
    }

    return ERROR;
}

Status ListDelete_SL(SLinkList H, int i, LElemType_S *e) {
    int count, k, p;

    if (!H)                                //链表不存在 
        return ERROR;

    if (i > 0) {
        count = 0;
        k = H;                            //k指向头结点 

        while (k && count < i - 1)            //寻找插入位置的前一个位置 
        {
            count++;
            k = SPACE[k].cur;
        }

        if (k && SPACE[k].cur)            //找到了第i-1个元素的位置且不是最后一个元素 
        {
            p = SPACE[k].cur;            //p指向要被删除的结点 
            *e = SPACE[p].data;
            SPACE[k].cur = SPACE[p].cur;
            Free_SL(p);

            return OK;
        }
    }

    return ERROR;
}

Status ListTraverse_SL(SLinkList H, void(Visit)(LElemType_S)) {
    int p;

    if (!H)
        return ERROR;                    //静态链表不存在或为空

    p = SPACE[H].cur;

    while (p) {
        Visit(SPACE[p].data);
        p = SPACE[p].cur;
    }

    return OK;
}

#endif //DATA_STRUCTURE_STATICLINKEDLIST_H
