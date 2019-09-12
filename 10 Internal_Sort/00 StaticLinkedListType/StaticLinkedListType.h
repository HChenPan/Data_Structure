//
//文件夹: 10 Internal_Sort/00 StaticLinkedListType
//文件名: StaticLinkedListType
//内　容：静态链表存储结构，供本章算法调用
//Author Huangcp
//Date 2019/9/13 上午 04:12
//Version 1.0
//

#ifndef DATA_STRUCTURE_STATICLINKEDLISTTYPE_H
#define DATA_STRUCTURE_STATICLINKEDLISTTYPE_H

#include <stdio.h>
#include <limits.h>
#include "../../01 Introduction/Status.h"            //**01 Introduction**//
#include "../../01 Introduction/Scanf.h"            //**01 Introduction**//

/* 宏定义 */
#define MAXSIZE 100                            //静态链表容量
#define MAXINT INT_MAX
#define LT(a, b) ((a)<(b))

/* 类型定义 */
typedef int KeyType;                        //定义关键字类型为整数类型
typedef struct                                //静态链表
{
    KeyType key;                            //关键字项
    //使用结构体便于使用中扩展
} RcdType;                                    //记录类型
typedef struct {
    RcdType rc;                                //记录项
    int next;                                //指针项
} SLNode;                                    //表结点类型
typedef struct {
    SLNode r[MAXSIZE];                        //0号单元为表头结点
    int length;                                //链表当前长度
} SLinkList_sort;                            //静态链表类型

/* 静态链表存储结构函数列表 */
/*━━━━━━━━━━━━━━┓
┃(01)创建一个任意顺序的序列。┃
┗━━━━━━━━━━━━━━*/
Status CreateSortList(FILE *fp, SLinkList_sort *L);

/*━━━━━━━━┓
┃(02)输出序列L。 ┃
┗━━━━━━━━*/
void Traverse(SLinkList_sort L, void(Visit)(KeyType));

Status CreateSortList(FILE *fp, SLinkList_sort *L) {
    int i;

    Scanf(fp, "%d", &((*L).length));

    if ((*L).length > MAXSIZE)
        return ERROR;

    (*L).r[0].rc.key = MAXINT;
    (*L).r[0].next = 0;

    for (i = 1; i <= (*L).length; i++) {
        Scanf(fp, "%d", &((*L).r[i].rc.key));
        (*L).r[i].next = -1;
    }

    return OK;
}

void Traverse(SLinkList_sort L, void(Visit)(KeyType)) {
    int i;

    for (i = 1; i <= L.length; i++)
        Visit(L.r[i].rc.key);

    printf("\n");
}


#endif //DATA_STRUCTURE_STATICLINKEDLISTTYPE_H
