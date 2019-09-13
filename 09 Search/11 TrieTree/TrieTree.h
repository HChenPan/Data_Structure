//
//文件夹: 09 Search/11 TrieTree
//文件名: TrieTree
//内　容：Trie树相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 03:22
//Version 1.0
//

#ifndef DATA_STRUCTURE_TRIETREE_H
#define DATA_STRUCTURE_TRIETREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>                        //提供isalpha原型
#include "../../01 Introduction/Status.h"        //**01 Introduction**//
#include "../../01 Introduction/Scanf.h"        //**01 Introduction**//

/* 宏定义 */
#define MAXKEYLEN 26                            //关键字的最大长度

/* 类型定义 */
typedef enum {
    LEAF, BRANCH
} NodeKind;            //结点种类：0-叶子，1-分支
typedef struct {
    char ch[MAXKEYLEN + 1];                        //关键字
    int num;                                    //关键字长度
} KeysType;                                        //关键字类型
typedef struct                                    //叶子结点的记录类型
{
    char key[MAXKEYLEN + 1];
} Record;                                        //记录类型
typedef struct TrieNode                            //Trie树存储表示
{
    NodeKind kind;                                //结点种类
    union {
        struct {
            struct TrieNode *ptr[MAXKEYLEN + 1];    //存储26个英文字母和1个"空"字母
            int count;                            //当前分支结点已占用的字母数
        } bh;                                    //分支结点

        struct {
            KeysType K;
            Record *infoptr;
        } lf;                                    //叶子结点
    } Ptr;
} TrieNode;                                        //Trie树结点
typedef TrieNode *TrieTree;                        //指向Trie树结点的指针

/* Trie树函数列表 */
/**
(01)创建Trie树
**/
Status CreateTrie(FILE *fp, TrieTree *TT);

/**
(02)算法9.16：查找
**/
Record *SearchTrie(TrieTree TT, KeysType K);

/**
(03)插入记录
**/
Status InsertTrie(TrieTree *TT, Record R);

/**
(04)删除含有关键字K的记录 
**/
Status DeleteTrie(TrieTree *TT, KeysType K);

/**
(05)返回字符ch在Trie树结点中的位序
**/
int ord(char ch);

/**
(06)判断结构A与B是否相等
**/
Status cmp(KeysType A, KeysType B);

/**
(07)遍历Trie树
**/
void TraverseTrie(TrieTree TT, void(Visit)(Record *));

Status CreateTrie(FILE *fp, TrieTree *TT) {
    Record tmp;
    int i;

    *TT = NULL;
    i = 0;

    while (Scanf(fp, "%s", &(tmp.key)) == 1)
        InsertTrie(TT, tmp);

    return OK;
}

/**
算法9.16
**/
Record *SearchTrie(TrieTree TT, KeysType K) {
    TrieTree p;
    int i;

    for (p = TT, i = 0; p && p->kind == BRANCH && i <= K.num; p = p->Ptr.bh.ptr[ord(K.ch[i])], i++);

    if (p && p->kind == LEAF && cmp(p->Ptr.lf.K, K))
        return p->Ptr.lf.infoptr;                    //查找成功
    else
        return NULL;                                //查找不成功
}

Status InsertTrie(TrieTree *TT, Record R) {
    TrieTree p, pre, np;
    int i, j;
    Record *r;
    KeysType Ko, K;

    r = (Record *) malloc(sizeof(Record));
    *r = R;
    strcpy(K.ch, R.key);
    K.num = strlen(R.key);

    if (!*TT)                                        //空树
    {
        *TT = (TrieTree) malloc(sizeof(TrieNode));
        (*TT)->kind = BRANCH;
        for (i = 0; i <= MAXKEYLEN; i++)
            (*TT)->Ptr.bh.ptr[i] = NULL;
        (*TT)->Ptr.bh.count = 0;

        p = (TrieTree) malloc(sizeof(TrieNode));
        p->kind = LEAF;
        p->Ptr.lf.K = K;
        p->Ptr.lf.infoptr = r;
        (*TT)->Ptr.bh.ptr[ord(R.key[0])] = p;
        (*TT)->Ptr.bh.count++;
    } else                                            //非空树
    {
        for (pre = NULL, p = *TT, i = 0;
             p && p->kind == BRANCH && i <= K.num; pre = p, p = p->Ptr.bh.ptr[ord(R.key[i])], ++i);

        i--;                                        //退回失配的位置

        if (p && p->kind == LEAF && cmp(p->Ptr.lf.K, K))
            return ERROR;                            //记录已存在
        else {
            if (!p) {
                p = (TrieTree) malloc(sizeof(TrieNode));
                p->kind = LEAF;
                p->Ptr.lf.K = K;
                p->Ptr.lf.infoptr = r;
                pre->Ptr.bh.ptr[ord(R.key[i])] = p;
                pre->Ptr.bh.count++;
            } else {
                if (p->kind == LEAF) {
                    Ko = p->Ptr.lf.K;
                    pre->Ptr.bh.count--;

                    do {
                        np = (TrieTree) malloc(sizeof(TrieNode));
                        np->kind = BRANCH;
                        for (j = 0; j <= MAXKEYLEN; j++)
                            np->Ptr.bh.ptr[j] = NULL;
                        np->Ptr.bh.count = 0;

                        pre->Ptr.bh.ptr[ord(K.ch[i])] = np;
                        pre->Ptr.bh.count++;
                        pre = np;
                        i++;
                    } while (ord(K.ch[i]) == ord(Ko.ch[i]));

                    pre->Ptr.bh.ptr[ord(Ko.ch[i])] = p;
                    pre->Ptr.bh.count++;

                    p = (TrieTree) malloc(sizeof(TrieNode));
                    p->kind = LEAF;
                    p->Ptr.lf.K = K;
                    p->Ptr.lf.infoptr = r;
                    pre->Ptr.bh.ptr[ord(K.ch[i])] = p;
                    pre->Ptr.bh.count++;
                }
            }
        }
    }
}

Status DeleteTrie(TrieTree *TT, KeysType K) {
    TrieTree p, pre, prepre, r;
    KeysType K0;
    int i, j;

    p = *TT, prepre = pre = NULL, i = 0;

    while (p && p->kind == BRANCH && i <= K.num) {
        prepre = pre;
        pre = p;
        p = p->Ptr.bh.ptr[ord(K.ch[i])];
        i++;
    }

    if (p && p->kind == LEAF && cmp(p->Ptr.lf.K, K))            //查找成功，进行删除
    {
        free(p->Ptr.lf.infoptr);                            //释放叶子结点指向的记录
        free(pre->Ptr.bh.ptr[ord(K.ch[i - 1])]);                //释放记录
        pre->Ptr.bh.ptr[ord(K.ch[i - 1])] = NULL;
        pre->Ptr.bh.count--;

        if (pre->Ptr.bh.count == 0)                            //只可能发生在根结点上
        {
            free(*TT);
            *TT = NULL;
        } else {
            if (pre->Ptr.bh.count == 1 && pre != *TT)            //收缩剩余结点到上一个分支结点
            {
                if (pre->Ptr.bh.ptr[0])                        //只剩0号单元位置的结点
                {
                    r = pre->Ptr.bh.ptr[0];
                    free(prepre->Ptr.bh.ptr[ord(K.ch[i - 2])]);
                    prepre->Ptr.bh.ptr[ord(K.ch[i - 2])] = r;
                } else                                        //查找另一个结点
                {
                    for (j = 0, r = pre->Ptr.bh.ptr[j]; !r; r = pre->Ptr.bh.ptr[++j]);

                    if (r->kind == LEAF)                        //剩余结点为叶子结点时收缩
                    {
                        K0 = r->Ptr.lf.K;
                        r = pre->Ptr.bh.ptr[ord(K0.ch[i - 1])];
                        free(prepre->Ptr.bh.ptr[ord(K0.ch[i - 2])]);
                        prepre->Ptr.bh.ptr[ord(K0.ch[i - 2])] = r;
                    }
                }
            }
        }

        return OK;
    } else
        return ERROR;
}

int ord(char ch) {
    if (isalpha(ch))
        return ch - 'A' + 1;
    else
        return 0;
}

Status cmp(KeysType A, KeysType B) {
    int i;

    if (A.num != B.num)
        return ERROR;
    else {
        for (i = 0; i < A.num; i++) {
            if (A.ch[i] != B.ch[i])
                return ERROR;
        }
    }

    return OK;
}

void TraverseTrie(TrieTree TT, void(Visit)(Record *)) {
    TrieTree p;
    int i;

    if (TT) {
//		printf("%d\n", TT->Ptr.bh.count);
        for (i = 0; i <= MAXKEYLEN; i++) {
            p = TT->Ptr.bh.ptr[i];

            if (p && p->kind == LEAF)
                Visit(p->Ptr.lf.infoptr);
            else {
                if (p && p->kind == BRANCH)
                    TraverseTrie(p, Visit);
            }
        }
    }
}

#endif //DATA_STRUCTURE_TRIETREE_H
