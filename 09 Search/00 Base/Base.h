//
//文件夹: 09 Search/00 Base
//文件名: Base
//内　容：查找表结构，供本章程序调用
//Author Huangcp
//Date 2019/9/13 上午 03:19
//Version 1.0
//

#ifndef DATA_STRUCTURE_BASE_H
#define DATA_STRUCTURE_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include "../../01 Introduction/Status.h"                //**01 Introduction**//
#include "../../01 Introduction/Scanf.h"                //**01 Introduction**//

/* 查找表类型定义 */
typedef int KeyType;            //关键字类型
typedef struct {
    int key;                    //关键字域
    float weight;                //其他域（此处可设为权重）
} ElemType_Search;                //有序表元素类型

//0号单元弃用
typedef struct {
    ElemType_Search *elem;        //数据元素存储空间基址，0号单元为空
    int length;                    //表长度
} Table;                            //查找表

/* 函数列表 */
/**
(01)创建查找表
**/
Status Create(FILE *fp, Table *T, int n);

/**
(02)销毁查找表
**/
void Destory(Table *T);

/**
(03)遍历查找表
**/
void Traverse(Table T, void(Visit)(ElemType_Search));

/**
(04)输出查找表中的关键字（只输出key域） 
**/
void PrintKey(ElemType_Search e);


Status Create(FILE *fp, Table *T, int n) {
    int i;
    int a;
    float b;

    T->elem = (ElemType_Search *) malloc((n + 1) * sizeof(ElemType_Search));
    if (!(T->elem))
        exit(OVERFLOW);

    //此表0号单元是弃用的
    for ((*T).length = 0, i = 1; i <= n; i++) {
        if (Scanf(fp, "%d%f", &a, &b) == 2) {
            (*T).elem[i].key = a;
            (*T).elem[i].weight = b;
            (*T).length++;
        }
    }

    return OK;
}

void Destory(Table *T) {
    if (T->elem)
        free(T->elem);

    T->elem = NULL;
    T->length = 0;
}

void Traverse(Table T, void(Visit)(ElemType_Search)) {
    int i;

    for (i = 0; i < T.length; i++) {
        if (i && !(i % 10))
            printf("\n");

        Visit(T.elem[i + 1]);
    }

    printf("\n");
}

/* 输出查找表中的关键字 */
void PrintKey(ElemType_Search e) {
    printf("%3d ", e.key);
}


#endif //DATA_STRUCTURE_BASE_H
