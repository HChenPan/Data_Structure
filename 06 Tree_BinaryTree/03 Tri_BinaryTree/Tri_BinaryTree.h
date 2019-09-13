//
//文件夹: 06 Tree_BinaryTree/03 Tri_BinaryTree
//文件名: Tri_BinaryTree
//内　容：二叉树三叉链表存储结构相关操作列表
//Author Huangcp
//Date 2019/9/12 下午 10:30
//Version 1.0
//

#ifndef DATA_STRUCTURE_TRI_BINARYTREE_H
#define DATA_STRUCTURE_TRI_BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>                                //提供malloc、realloc、free、exit原型
#include <math.h>                                //提供pow、log原型
#include "../../01 Introduction/Status.h"                //**▲01 绪论**//
#include "../../01 Introduction/Scanf.h"                //**▲01 绪论**//

/* 二叉树（三叉链表存储）相关类型定义 */
typedef char TElemType_Tri;                        //假设二叉树元素均为字符
typedef struct TBiTNode {
    TElemType_Tri data;                            //结点元素
    struct TBiTNode *parent;                    //双亲结点指针
    struct TBiTNode *lchild;                    //左孩子指针
    struct TBiTNode *rchild;                    //右孩子指针
} TBiTNode;                                        //二叉树结点
typedef TBiTNode *TBiTree;                        //指向二叉树结点的指针

/* 队列元素类型 */
typedef TBiTree QElemType_L;

#include "../../03 Stack_Queue/07 LinkQueue/LinkQueue.h" //**▲03 栈和队列**//

/* 二叉树三叉链表存储结构函数列表 */

/**
(01)构造空二叉树T (初始化二叉树)。
**/
void InitBiTree_Tri(TBiTree *T);

/**
(02)清空二叉树T。 
**/
void ClearBiTree_Tri(TBiTree *T);

/**
(03)销毁二叉树T。 
**/
void DestroyBiTree_Tri(TBiTree *T);

/**
(04)判断二叉树T是否为空。 
**/
Status BiTreeEmpty_Tri(TBiTree T);

/**
(05)二叉树构造函数调用。
**/
void Create_Tri(TBiTree *T, FILE *fp);

/**
(06)按先序序列构造二叉树。
**/
Status CreateBiTree_Tri(FILE *fp, TBiTree *T);

/**
(07)返回二叉树长度（按完全二叉树计算）。
**/
int BiTreeLength_Tri(TBiTree T);

/**
(08)返回二叉树深度（层数）。
**/
int BiTreeDepth_Tri(TBiTree T);

/**
(09)用e返回二叉树的根结点值。 
**/
Status Root_Tri(TBiTree T, TElemType_Tri *e);

/**
(10)返回某结点的值，p为结点指针。 
**/
TElemType_Tri Value_Tri(TBiTree p);

/**
(11)为某结点赋值，p为结点指针。 
**/
void Assign_Tri(TBiTree p, TElemType_Tri value);

/**
(12)返回指向某结点的指针。
**/
TBiTree Point(TBiTree T, TElemType_Tri e);

/**
(13)返回某结点的双亲结点值。
**/
TElemType_Tri Parent_Tri(TBiTree T, TElemType_Tri e);

/**
(14)返回某结点的左孩子结点值。
**/
TElemType_Tri LeftChild_Tri(TBiTree T, TElemType_Tri e);

/**
(15)返回某结点的右孩子结点值。
**/
TElemType_Tri RightChild_Tri(TBiTree T, TElemType_Tri e);

/**
(16)返回某结点的左兄弟结点值。
**/
TElemType_Tri LeftSibling_Tri(TBiTree T, TElemType_Tri e);

/**
(17)返回某结点的右兄弟结点值。
**/
TElemType_Tri RightSibling_Tri(TBiTree T, TElemType_Tri e);

/**
(18)将树T0插入到树T中成为结点e的子树，LR为插入标记。
**/
Status InsertBiTree_Tri(TBiTree T, TElemType_Tri e, TBiTree *T0, int LR);

/**
(19)删除e结点的左子树或右子树，LR为删除标记。 
**/
Status DeleteBiTree_Tri(TBiTree T, TElemType_Tri e, int LR);

/**
(20)层序遍历二叉树。
**/
void LevelOrderTraverse_Tri(TBiTree T, void(Visit)(TElemType_Tri));

/**
(21)前序遍历二叉树。
**/
void PreOrderTraverse_Tri(TBiTree T, void(Visit)(TElemType_Tri));

/**
(22)中序遍历二叉树。
**/
void InOrderTraverse_Tri(TBiTree T, void(Visit)(TElemType_Tri));

/**
(23)后序遍历二叉树。
**/
void PostOrderTraverse_Tri(TBiTree T, void(Visit)(TElemType_Tri));

/**
(24)按二叉树的结构打印树。
**/
void Print_Tri(TBiTree T);


void InitBiTree_Tri(TBiTree *T) {
    *T = NULL;
}

void ClearBiTree_Tri(TBiTree *T) {
    if (*T) {
        if ((*T)->lchild)                                        //清空左树
            ClearBiTree_Tri(&((*T)->lchild));
        if ((*T)->rchild)                                        //清空右树
            ClearBiTree_Tri(&((*T)->rchild));

        free(*T);

        *T = NULL;
    }
}

void DestroyBiTree_Tri(TBiTree *T) {
    //二叉树无法销毁
}

Status BiTreeEmpty_Tri(TBiTree T) {
    return T == NULL ? TRUE : ERROR;
}

void Create_Tri(TBiTree *T, FILE *fp) {
    TElemType_Tri ch;

    Scanf(fp, "%c", &ch);

    if (ch == '^')
        *T = NULL;
    else {
        *T = (TBiTree) malloc(sizeof(TBiTNode));
        if (!(*T))
            exit(OVERFLOW);
        (*T)->data = ch;
        Create_Tri(&(*T)->lchild, fp);
        Create_Tri(&(*T)->rchild, fp);
    }
}

Status CreateBiTree_Tri(FILE *fp, TBiTree *T)                    //先建树，后设置双亲结点信息
{
    LinkQueue Q;
    QElemType_L e;

    Create_Tri(T, fp);

    if (*T) {
        (*T)->parent = NULL;
        InitQueue_L(&Q);
        EnQueue_L(&Q, *T);

        while (!QueueEmpty_L(Q)) {
            DeQueue_L(&Q, &e);

            if (e->lchild) {
                e->lchild->parent = e;
                EnQueue_L(&Q, e->lchild);
            }

            if (e->rchild) {
                e->rchild->parent = e;
                EnQueue_L(&Q, e->rchild);
            }
        }
    }

    return OK;
}

int BiTreeLength_Tri(TBiTree T) {
    LinkQueue Q;
    QElemType_L e;
    int a[100] = {};
    int i, j;

    i = -1;
    j = 0;

    if (T) {
        InitQueue_L(&Q);
        EnQueue_L(&Q, T);
        a[j++] = 1;

        while (!QueueEmpty_L(Q)) {
            DeQueue_L(&Q, &e);
            i++;

            if (e->lchild) {
                EnQueue_L(&Q, e->lchild);
                a[j++] = 2 * a[i];
            }

            if (e->rchild) {
                EnQueue_L(&Q, e->rchild);
                a[j++] = 2 * a[i] + 1;
            }
        }
    }

    if (j)
        return a[j - 1];
    else
        return 0;
}

int BiTreeDepth_Tri(TBiTree T) {
    int i = 0;
    double j;

    if (BiTreeLength_Tri(T)) {
        j = log(BiTreeLength_Tri(T)) / log(2);

        i = j + 1;
    }

    return i;
}

Status Root_Tri(TBiTree T, TElemType_Tri *e) {
    if (!T)
        return ERROR;
    else {
        *e = T->data;
        return OK;
    }
}

TElemType_Tri Value_Tri(TBiTree p) {
    return p->data;
}

void Assign_Tri(TBiTree p, TElemType_Tri value) {
    p->data = value;
}

TBiTree Point(TBiTree T, TElemType_Tri e) {
    LinkQueue Q;
    QElemType_L x;

    if (T) {
        InitQueue_L(&Q);
        EnQueue_L(&Q, T);

        while (!QueueEmpty_L(Q)) {
            DeQueue_L(&Q, &x);

            if (x->data == e)
                return x;

            if (x->lchild)
                EnQueue_L(&Q, x->lchild);

            if (x->rchild)
                EnQueue_L(&Q, x->rchild);
        }
    }

    return NULL;
}

TElemType_Tri Parent_Tri(TBiTree T, TElemType_Tri e) {
    TBiTree p;

    p = Point(T, e);

    if (p && p != T)
        return p->parent->data;
    else
        return '\0';
}

TElemType_Tri LeftChild_Tri(TBiTree T, TElemType_Tri e) {
    TBiTree p;

    p = Point(T, e);

    if (p && p->lchild)
        return p->lchild->data;
    else
        return '\0';
}

TElemType_Tri RightChild_Tri(TBiTree T, TElemType_Tri e) {
    TBiTree p;

    p = Point(T, e);

    if (p && p->rchild)
        return p->rchild->data;
    else
        return '\0';
}

TElemType_Tri LeftSibling_Tri(TBiTree T, TElemType_Tri e) {
    TBiTree p;

    p = Point(T, e);

    if (p && p->parent->lchild && p->parent->lchild->data != e)
        return p->parent->lchild->data;
    else
        return '\0';
}

TElemType_Tri RightSibling_Tri(TBiTree T, TElemType_Tri e) {
    TBiTree p;

    p = Point(T, e);

    if (p && p->parent->rchild && p->parent->rchild->data != e)
        return p->parent->rchild->data;
    else
        return '\0';
}

Status InsertBiTree_Tri(TBiTree T, TElemType_Tri e, TBiTree *T0, int LR) {
    TBiTree p = Point(T, e);

    if (p) {
        if (LR == 0)                                            //插入为左子树
        {
            (*T0)->rchild = p->lchild;
            p->lchild->parent = *T0;
            (*T0)->parent = p;
            p->lchild = *T0;
        } else                                                //插入为右子树
        {
            (*T0)->rchild = p->rchild;
            p->rchild->parent = *T0;
            (*T0)->parent = p;
            p->rchild = *T0;
        }

        return OK;
    }

    return ERROR;
}

Status DeleteBiTree_Tri(TBiTree T, TElemType_Tri e, int LR) {
    TBiTree p = Point(T, e);

    if (p) {
        LR ? ClearBiTree_Tri(&(p->rchild)) : ClearBiTree_Tri(&(p->lchild));

        return OK;
    }

    return ERROR;
}

void LevelOrderTraverse_Tri(TBiTree T, void(Visit)(TElemType_Tri)) {
    LinkQueue Q;
    QElemType_L e;

    if (T) {
        InitQueue_L(&Q);
        EnQueue_L(&Q, T);

        while (!QueueEmpty_L(Q)) {
            DeQueue_L(&Q, &e);
            Visit(e->data);

            if (e->lchild)
                EnQueue_L(&Q, e->lchild);

            if (e->rchild)
                EnQueue_L(&Q, e->rchild);
        }
    }
}

void PreOrderTraverse_Tri(TBiTree T, void(Visit)(TElemType_Tri)) {
    if (T) {
        Visit(T->data);
        PreOrderTraverse_Tri(T->lchild, Visit);
        PreOrderTraverse_Tri(T->rchild, Visit);
    }
}

void InOrderTraverse_Tri(TBiTree T, void(Visit)(TElemType_Tri)) {
    if (T) {
        InOrderTraverse_Tri(T->lchild, Visit);
        Visit(T->data);
        InOrderTraverse_Tri(T->rchild, Visit);
    }
}

void PostOrderTraverse_Tri(TBiTree T, void(Visit)(TElemType_Tri)) {
    if (T) {
        PostOrderTraverse_Tri(T->lchild, Visit);
        PostOrderTraverse_Tri(T->rchild, Visit);
        Visit(T->data);
    }
}


void Print_Tri(TBiTree T) {
    struct {
        TElemType_Tri c;
        int t;
    } node[100] = {};
    LinkQueue Q;
    QElemType_L e;
    int i, j, m, n, row, col, max, x, y;
    double tmp;
    TElemType_Tri a[100][100] = {};

    i = -1;
    j = 0;

    if (T) {
        InitQueue_L(&Q);
        EnQueue_L(&Q, T);
        node[j].c = T->data;
        node[j].t = 1;
        j++;

        while (!QueueEmpty_L(Q)) {
            DeQueue_L(&Q, &e);
            i++;

            if (e->lchild) {
                EnQueue_L(&Q, e->lchild);
                node[j].c = e->lchild->data;
                node[j].t = 2 * node[i].t;
                j++;
            }

            if (e->rchild) {
                EnQueue_L(&Q, e->rchild);
                node[j].c = e->rchild->data;
                node[j].t = 2 * node[i].t + 1;
                j++;
            }
        }
    }

    if (j) {
        tmp = log(node[j - 1].t) / log(2) + 1;
        row = (int) tmp;                            //二叉树层数（放入二维数组后占的行数）
        max = (int) pow(2, row - 1);                //二叉树最后一层最大元素个数
        col = 2 * max - 1;                            //放入二维数组后占的列数

        for (i = 0; i < j; i++)                        //遍历结构node
        {
            tmp = log(node[i].t) / log(2) + 1;
            x = (int) tmp;                            //当前结点所在层
            y = node[i].t - (int) pow(2, x - 1) + 1;        //当前结点所在列（按完全二叉树计算）

            if (x == 1)
                a[x - 1][max / (int) pow(2, x - 1) - 1] = node[i].c;
            else
                a[x - 1][max / (int) pow(2, x - 1) + (y - 1) * (max / (int) pow(2, x - 2)) - 1] = node[i].c;
        }

        for (m = 0; m < row; m++) {
            for (n = 0; n < col; n++) {
                if (a[m][n] != '\0')
                    printf("%c", a[m][n]);
                else
                    printf(" ");
            }

            printf("\n");
        }
    }

}

#endif //DATA_STRUCTURE_TRI_BINARYTREE_H
