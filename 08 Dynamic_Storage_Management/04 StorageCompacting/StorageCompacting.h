//
//文件夹: 08 Dynamic_Storage_Management/04 StorageCompacting
//文件名: StorageCompacting
//内　容：存储紧缩
//Author Huangcp
//Date 2019/9/13 上午 03:01
//Version 1.0
//

#ifndef DATA_STRUCTURE_STORAGECOMPACTING_H
#define DATA_STRUCTURE_STORAGECOMPACTING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../01 Introduction/Status.h"                            //**01 Introduction**//

/* 宏定义 */
#define MAX 1000

/* 全局变量 */
struct {
    int stadr;                    //当前内存块起始地址
    int length;                    //当前内存块大小
} Record[MAX + 1];                    //内存地址表

int start, end;                    //空闲内存块下阕和上阕（固定）
int cur;                        //当前空闲内存块起点（浮动）

/* 存储紧缩函数列表 */
/**
(01)初始化一块大小为 n 的空闲内存块。 
**/
void InitMemory(int n);

/**
(02)分配一块大小为 n 的空闲内存块，若分配成功，返回其地址。 
**/
void *MallocMemory(int n);

/**
(03)释放地址 ptr 处的空闲内存块。 
**/
void FreeMemory(void *ptr);

/**
(04)存储紧缩算法，返回压缩后空闲内存块当前起始地址。
**/
int CompressMemory();

/**
(05)输出当前空闲、非空闲内存块的数量。
**/
void PrintLayout();


void InitMemory(int n) {
    void *p = malloc(n);

    start = (int) p;
    end = start + n - 1;
    cur = start;
}

void *MallocMemory(int n) {
    void *p;

    if (cur + n - 1 > end)                                    //空间不够，进行压缩
        cur = CompressMemory();

    if (cur + n - 1 > end)                                    //压缩后空间依然不够用
    {
        printf("内存已满，无法继续分配空间！\n");
        return NULL;
    } else {
        p = (void *) cur;

        Record[0].length++;                            //内存地址表中添加此记录
        Record[Record[0].length].stadr = cur;
        Record[Record[0].length].length = n;

        cur += n;
    }

    return p;
}

void FreeMemory(void *ptr) {
    int i, j;

    for (i = 1; i <= Record[0].length; i++) {
        if (Record[i].stadr == (int) ptr)            //内存地址表压缩
        {
            for (j = i; j < Record[0].length; j++)
                Record[j] = Record[j + 1];

            Record[0].length--;

            return;
        }
    }
}

int CompressMemory() {
    int p, q, k;

    for (k = 1, p = start; k <= Record[0].length && Record[k].length; k++) {
        q = Record[k].stadr;
        memmove((void *) p, (void *) q, Record[k].length);        //移动数据
        Record[k].stadr = p;                                //更新起点

        p += Record[k].length;
    }

    return p;
}

void PrintLayout() {
    int k, count;

    printf("已占用的内存块范围：┃");
    for (k = 1, count = 0; k <= Record[0].length; k++) {
        printf("%3d←→%3d┃", Record[k].stadr - start, Record[k].stadr + Record[k].length - start - 1);
        count += Record[k].length;
    }
    printf("\n");

    printf("内存已占用块数：%4d，空闲块数：%4d。\n", count, MAX - count);
}

#endif //DATA_STRUCTURE_STORAGECOMPACTING_H
