//
//文件夹: 10 Internal_Sort/00 SequenceListType
//文件名: SequenceListType
//内　容：顺序表存储结构，供本章算法调用
//Author Huangcp
//Date 2019/9/13 上午 04:12
//Version 1.0
//

#ifndef DATA_STRUCTURE_SEQUENCELISTTYPE_H
#define DATA_STRUCTURE_SEQUENCELISTTYPE_H

#include <stdio.h>
#include "../../01 Introduction/Status.h"        //**01 Introduction**//
#include "../../01 Introduction/Scanf.h"        //**01 Introduction**//

/* 宏定义 */
#ifndef MAXSIZE
#define MAXSIZE 20                        //一个用作示例的小顺序表的最大长度
#endif
#define LT(a, b) ((a)<(b))
#define LQ(a, b) ((a)<=(b))

/* 类型定义 */
typedef int KeyType;                    //定义关键字类型为整数类型
typedef struct                            //顺序表结构
{
    KeyType key;                        //关键字项
    //使用结构体便于使用中扩展
} RcdType;                                //记录类型
typedef struct {
    RcdType r[MAXSIZE + 1];                //r[0]闲置或用作哨兵单元
    int length;                            //顺序表长度
} SqList_sort;                            //顺序表类型

/* 顺序表存储结构函数列表 */
/*━━━━━━━━━━━━━━┓
┃(01)创建一个任意顺序的序列。┃
┗━━━━━━━━━━━━━━*/
Status CreateSortList(FILE *fp, SqList_sort *L);

/*━━━━━━━━┓
┃(02)输出序列L。 ┃
┗━━━━━━━━*/
void Traverse(SqList_sort L, void(Visit)(KeyType));

Status CreateSortList(FILE *fp, SqList_sort *L) {
    int i;

    Scanf(fp, "%d", &((*L).length));

    if ((*L).length > MAXSIZE)
        return ERROR;

    for (i = 1; i <= (*L).length; i++)
        Scanf(fp, "%d", &((*L).r[i].key));

    return OK;
}

void Traverse(SqList_sort L, void(Visit)(KeyType)) {
    int i;

    for (i = 1; i <= L.length; i++)
        Visit(L.r[i].key);

    printf("\n");
}


#endif //DATA_STRUCTURE_SEQUENCELISTTYPE_H
