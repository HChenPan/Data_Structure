//
//文件夹: 09 Search/09 B+Tree
//文件名: B
//内　容：B+树相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 03:22
//Version 1.0
//

#ifndef DATA_STRUCTURE_B_TREE_H
#define DATA_STRUCTURE_B_TREE_H

#include <stdlib.h>
#include <math.h>                            //提供ceil原型
#include "../00 Base/Base.h"                //**09 Search**//

/* 宏定义 */
#define M 3                                    //B+树的阶，暂设为3
#define EQ(a, b) ((a)==(b))
#define LT(a, b) ((a) < (b))

/* 类型定义 */
typedef ElemType_Search B_TElemType;        //B+树元素类型
typedef struct B_TNode                        //B+树存储表示
{
    int keynum;                                //结点中关键字个数
    struct B_TNode *parent;                    //指向双亲结点
    //（与B树区别）
    KeyType key[M + 1];                        //关键字向量，占用0号单元
    struct B_TNode *ptr[M + 1];                //子树指针向量，占用0号单元

    int leaf;                                //leaf=0,非叶结点，leaf=1，叶结点
    union {
        struct B_TNode *next;
    } lf;
} B_TNode;                                    //B+树结点
typedef struct {
    B_TNode *data;                            //叶子结点头指针
    B_TNode *root;                            //指向B+树根结点
} B_Tree;                                    //B+树

/* B+树查找结果类型 */
typedef struct {
    B_TNode *pt;                            //指向找到的结点
    int i;                                    //1...n，关键字在结点中的序号（插入位置）
    int tag;                                //1:查找成功，0:查找失败
} Result;

/* B+树函数列表 */
/**
(01)创建B+树。
**/
Status CreateB_Tree(B_Tree *B_T, Table T);

/**
(02)查找，返回查找信息。
**/
Result SearchB_Tree(B_Tree B_T, KeyType K);

/**
(03)返回K在结点p中的次序。
**/
int Search(B_TNode *p, KeyType K);

/**
(04)将关键字K插入B+树。 
**/
Status InsertKey(B_Tree *B_T, KeyType K);

/**
(05)插入，将K插入为结点*q的第i个关键字。
**/
Status InsertB_Tree(B_Tree *B_T, KeyType K, B_TNode *q, int i);

/**
(06)将x和ap分别插入到q->key[i]和q->ptr[i]。 
**/
void Insert(B_TNode *q, int i, KeyType x, B_TNode *ap);

/**
(07)以s为界，将q指向的结点分裂成q和ap指向的两部分。 
**/
void split(B_TNode *q, int s, B_TNode **ap);

/**
(08)生成含信息(BT,x,ap)的新的根结点*BT，原BT和ap为子树指针，q初值为NULL。 
**/
void NewRoot(B_Tree *B_T, B_TNode *q, int x, B_TNode *ap);

/**
(09)输出B+树关键字。
**/
void PrintB_Tree(B_Tree B_T);

Status CreateB_Tree(B_Tree *B_T, Table T) {
    int i;

    (*B_T).root = (*B_T).data = NULL;

    if (T.length) {
        for (i = 1; i <= T.length; i++) {
            if (!InsertKey(B_T, T.elem[i].key))    //插入失败则跳出循环
                break;
        }
    }

    if (i > T.length)
        return OK;
    else
        return ERROR;
}

Result SearchB_Tree(B_Tree B_T, KeyType K) {
    Result R = {NULL, 0, 0};
    B_TNode *p;
    int found, i;

    p = B_T.root;
    found = FALSE;
    i = 0;                        //p->key[i]<=K<p->key[i+1]

    while (p && !found) {
        i = Search(p, K);        //在p->key[1...keynum]中查找

        if (p->leaf == 1) {
            if (i > 0 && p->key[i - 1] == K) {
                found = TRUE;
                i--;
            } else
                break;
        } else {
            if (i > 0)
                i--;

            p = p->ptr[i];
        }
    }

    R.i = i;
    R.pt = p;

    if (found)
        R.tag = 1;
    else
        R.tag = 0;

    return R;
}

int Search(B_TNode *p, KeyType K) {
    int i;

    for (i = 0; i < p->keynum && p->key[i] <= K; i++);

    return i;
}

Status InsertKey(B_Tree *B_T, KeyType K) {
    Result R;

    R = SearchB_Tree(*B_T, K);

    if (R.tag == 0)                            //B+树中不存在此关键字
    {
        InsertB_Tree(B_T, K, R.pt, R.i);
        return OK;
    } else
        return ERROR;
}

Status InsertB_Tree(B_Tree *B_T, KeyType K, B_TNode *q, int i) {
    KeyType x;
    B_TNode *ap;
    int finished;
    int s;

    x = K;
    ap = NULL;
    finished = FALSE;

    while (q && !finished) {
        Insert(q, i, x, ap);        //将x和ap分别插入到q->key[i]和q->ptr[i]
        q->ptr[i] = ap;

        if (q->keynum <= M)            //（与B树区别）
            finished = TRUE;        //插入完成
        else                        //关键字数目超出限制
        {
            s = (double) M / 2;        //B+树结点中关键字个数必须>=ceil(M/2)
            split(q, s, &ap);        //分裂结点*q
            x = q->key[s + 1];        //将q->key[s+1...M],q->ptr[s...M]移入新结点*ap;
            q = q->parent;

            if (q)                    //在双亲结点*q中查找x的插入位置
                i = Search(q, x);
        }
    }

    if (!finished)                    //B_T是空树（参数q初值为NULL）或者根结点已分裂为结点*q和*ap
        NewRoot(B_T, q, x, ap);    //生成含信息(B_T,x,ap)的新的根结点*B_T，原B_T和ap为子树指针

    return OK;
}

void Insert(B_TNode *q, int i, KeyType x, B_TNode *ap) {
    int j;
    B_TNode *p;

    for (j = q->keynum; j > i; j--) {
        q->key[j] = q->key[j - 1];
        q->ptr[j] = q->ptr[j - 1];
    }

    q->key[i] = x;
    q->ptr[i] = ap;
    q->keynum++;

    p = q->parent;                            //最小值发生了变动
    while (!i && p) {
        i = Search(p, q->key[1]);
        --i;
        p->key[i] = x;
        p = p->parent;
    }
}

void split(B_TNode *q, int s, B_TNode **ap)        //s初值为┌M/2┐
{
    int i;

    *ap = (B_TNode *) malloc(sizeof(B_TNode));

    if (q->leaf == 1)                                //分裂的是叶子结点
    {
        (*ap)->leaf = 1;
        (*ap)->lf.next = q->lf.next;
        q->lf.next = *ap;
    } else
        (*ap)->leaf = 0;

    for (i = s + 1; i <= M; i++) {
        (*ap)->key[i - s - 1] = q->key[i];
        (*ap)->ptr[i - s - 1] = q->ptr[i];
    }

    (*ap)->keynum = M - s;
    q->keynum = s + 1;

    (*ap)->parent = q->parent;

    for (i = 0; i < (*ap)->keynum; i++) {
        if ((*ap)->ptr[i])
            (*ap)->ptr[i]->parent = *ap;
    }
}

void NewRoot(B_Tree *B_T, B_TNode *q, int x, B_TNode *ap)    //q初始值为空
{
    B_TNode *p;

    p = (B_TNode *) malloc(sizeof(B_TNode));
    p->keynum = 1;
    p->parent = NULL;
    p->key[0] = x;
    p->ptr[0] = ap;
    if (p->ptr[0])
        p->ptr[0]->parent = p;

    if (!q && B_T->root) {
        Insert(p, 0, B_T->root->key[0], B_T->root);
        if (p->ptr[0])
            p->ptr[0]->parent = p;
    }

    B_T->root = p;

    if (B_T->data == NULL) {
        p->leaf = 1;
        p->lf.next = NULL;
        B_T->data = p;
    } else
        p->leaf = 0;
}

void PrintB_Tree(B_Tree B_T) {
    B_TNode *p;
    int i;

    for (p = B_T.data; p; p = p->lf.next) {
        printf("(");
        for (i = 0; i < p->keynum; i++)
            printf("%d ", p->key[i]);
        printf(") ");
    }

    printf("\n");
}

#endif //DATA_STRUCTURE_B_TREE_H
