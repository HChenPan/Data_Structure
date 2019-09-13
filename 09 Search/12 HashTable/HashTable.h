//
//文件夹: 09 Search/12 HashTable
//文件名: HashTable
//内　容：哈希查找表相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 03:23
//Version 1.0
//

#ifndef DATA_STRUCTURE_HASHTABLE_H
#define DATA_STRUCTURE_HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "../00 Base/Base.h"                //**09 Search**//

/*全局变量*/
int hashsize[] = {7, 13, 17, 101, 211, 307, 401, 503, 601, 701, 809, 907, 997};    //哈希表容量递增表，一个合适的素数序列

/* 宏定义 */
#define DUPLICATE -1                        //表中已存在关键字
#define NULLKEY   -2                        //标记此处无关键字
#define FULL      -3                        //表已满（冲突次数达上限就认为表满）
#define EQ(a, b) ((a)==(b))

/* 类型定义 */
typedef struct                                //开放定址哈希表存储表示
{
    KeyType *elem;                            //数据元素存储基址，动态分配数组
    int count;                                //当前哈希表包含的关键字个数
    int sizeindex;                            //hashsize[sizeindex]为当前容量
} HashTable;



/* 哈希查找表函数列表 */
/**
(01)初始化一个空的哈希表。
**/
void InitHash(HashTable *H);

/**
(02)创建哈希表。
**/
Status CreateHash(HashTable *H, Table T);

/**
(03)算法9.17：哈希表关键字搜索，p指向查找成功后的元素位置，*c记录发生冲突的次数 
**/
Status SearchHash(HashTable H, KeyType K, int *p);

/**
(04)算法9.18：哈希表关键字插入。
**/
Status InsertHash(HashTable *H, KeyType K);

/**
(05)重建哈希表。
**/
Status RecreateHashTable(HashTable *H);

/**
(06)哈希函数。
**/
int fHash(HashTable H, KeyType K);

/**
(07)开放定址法寻找下一探查位置。
**/
void collision(HashTable H, int *p);

/**
(08)输出哈希表中关键字。
**/
void PrintHash(HashTable H);

void InitHash(HashTable *H) {
    (*H).count = 0;
    (*H).sizeindex = -1;
    (*H).elem = NULL;
}

Status CreateHash(HashTable *H, Table T) {
    int i, tag;

    InitHash(H);

    RecreateHashTable(H);

    i = 1;
    while (i <= T.length)                //将T中关键字依次插入到哈希表中
    {
        tag = InsertHash(H, T.elem[i].key);
        if (tag == SUCCESS)            //表中已有关键字或关键字顺利插入
            i++;
        else                        //重建哈希表后重新填充
            i = 1;
    }

    return OK;
}

/**
算法9.17
**/
//重写了课本算法
Status SearchHash(HashTable H, KeyType K, int *p) {
    int c, sup;

    c = 0;                            //记录冲突次数
    sup = hashsize[H.sizeindex] / 2;    //冲突上限
    *p = fHash(H, K);                //p指向K应该插入的地址

    while (1)                        //该位置有记录且与K不等
    {
        if (H.elem[*p] == NULLKEY)
            return NULLKEY;
        else if (EQ(H.elem[*p], K))
            return DUPLICATE;        //表中已有此关键字
        else if (++c == sup)            //已达冲突上限
            return FULL;
        else
            collision(H, p);        //重新定位p的地址
    }
}

/**
算法9.18
**/
//重写了课本算法
Status InsertHash(HashTable *H, KeyType K) {
    int flag, p;

    flag = SearchHash(*H, K, &p);

    if (flag == FULL)                //表已满
    {
        RecreateHashTable(H);    //重建哈希表
        return UNSUCCESS;
    } else {
        if (flag == NULLKEY) {
            H->elem[p] = K;        //插入K
            ++(*H).count;
        }
        return SUCCESS;
    }
}

Status RecreateHashTable(HashTable *H) {
    int i, newv;
    HashTable *p;

    (*H).count = 0;
    (*H).sizeindex++;
    newv = hashsize[(*H).sizeindex];

    if ((*H).elem != NULL)
        free((*H).elem);

    //扩充了哈希表容量
    (*H).elem = (KeyType *) malloc(newv * sizeof(KeyType));
    if ((*H).elem == NULL)
        return ERROR;

    for (i = 0; i < newv; i++)
        (*H).elem[i] = NULLKEY;

    return OK;
}

int fHash(HashTable H, KeyType K)    //只是简单的取余
{
    return K % hashsize[H.sizeindex];
}

void collision(HashTable H, int *p)    //简单的移位
{
    *p = (*p + 1) % hashsize[H.sizeindex];
}

void PrintHash(HashTable H) {
    int i, v;

    v = hashsize[H.sizeindex];

    printf("哈希表容量为：%d，现有元素：%d 个，表中元素为：\n", v, H.count);

    for (i = 0; i < v; i++) {
        if (H.elem[i] != NULLKEY)
            printf("%d ", H.elem[i]);
    }

    printf("\n");
}

#endif //DATA_STRUCTURE_HASHTABLE_H
