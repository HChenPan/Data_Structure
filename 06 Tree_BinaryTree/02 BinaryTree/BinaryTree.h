//
//文件夹: 06 Tree_BinaryTree/02 BinaryTree
//文件名: BinaryTree
//内　容：二叉树（二叉链表存储）相关操作列表
//Author Huangcp
//Date 2019/9/12 下午 10:25
//Version 1.0
//

#ifndef DATA_STRUCTURE_BINARYTREE_H
#define DATA_STRUCTURE_BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>                                //提供malloc、realloc、free、exit原型
#include <math.h>                                //提供pow、log原型
#include "../../01 Introduction/Status.h"                //**▲01 绪论**//
#include "../../01 Introduction/Scanf.h"                //**▲01 绪论**//

/* 二叉树（二叉链表存储）相关类型定义 */
typedef char TElemType;                            //假设二叉树元素均为字符
typedef struct BiTNode {
    TElemType data;                                //结点元素
    struct BiTNode *lchild;                        //左孩子指针
    struct BiTNode *rchild;                        //右孩子指针
} BiTNode;                                        //二叉树结点
typedef BiTNode *BiTree;                        //指向二叉树结点的指针

/* 栈元素类型 */
typedef BiTree SElemType_Sq;                    //重定义栈元素类型
#include "../../03 Stack_Queue/01 SequenceStack/SequenceStack.h"    //**▲03 栈和队列**//

/* 存储当前结点信息 */
/* 在按树结构打印树的时候使用 */
typedef struct {
    BiTree left;                                //当前结点的左指针
    BiTree right;                                //当前结点的右指针
    int n;                                        //当前结点的次序
} Node;

/* 二叉树（二叉链表存储）函数列 表 */
/*━━━━━━━━━━━━━━━━━┓
┃(01)构造空二叉树T (初始化二叉树)。┃
┗━━━━━━━━━━━━━━━━━*/
void InitBiTree(BiTree *T);

/*━━━━━━━━━┓
┃(02)清空二叉树T。 ┃
┗━━━━━━━━━*/
void ClearBiTree(BiTree *T);

/*━━━━━━━━━┓
┃(03)销毁二叉树T。 ┃
┗━━━━━━━━━*/
void DestroyBiTree(BiTree *T);

/*━━━━━━━━━━━━━┓
┃(04)判断二叉树T是否为空。 ┃
┗━━━━━━━━━━━━━*/
Status BiTreeEmpty(BiTree T);

/*━━━━━━━━━━━━━━━━━━┓
┃(05)算法6.4：按先序序列构造二叉树。 ┃
┗━━━━━━━━━━━━━━━━━━*/
Status CreateBiTree(FILE *fp, BiTree *T);

/*━━━━━━━━━━━━━━━━━━━━┓
┃(06)返回二叉树长度（按完全二叉树计算）。┃
┗━━━━━━━━━━━━━━━━━━━━*/
int BiTreeLength(BiTree T);

/*━━━━━━━━━━━━━━┓
┃(07)返回二叉树深度（层数）。┃
┗━━━━━━━━━━━━━━*/
int BiTreeDepth(BiTree T);

/*━━━━━━━━━━━━━━━┓
┃(08)用e返回二叉树的根结点值。 ┃
┗━━━━━━━━━━━━━━━*/
Status Root(BiTree T, TElemType *e);

/*━━━━━━━━━━━━━━━━━┓
┃(09)返回某结点的值，p为结点指针。 ┃
┗━━━━━━━━━━━━━━━━━*/
TElemType Value(BiTree p);

/*━━━━━━━━━━━━━━━━┓
┃(10)为某结点赋值，p为结点指针。 ┃
┗━━━━━━━━━━━━━━━━*/
void Assign(BiTree p, TElemType value);

/*━━━━━━━━━━━━━━┓
┃(11)返回某结点的双亲结点值。┃
┗━━━━━━━━━━━━━━*/
TElemType Parent(BiTree T, TElemType e);

/*━━━━━━━━━━━━━━━┓
┃(12)返回某结点的左孩子结点值。┃
┗━━━━━━━━━━━━━━━*/
TElemType LeftChild(BiTree T, TElemType e);

/*━━━━━━━━━━━━━━━┓
┃(13)返回某结点的右孩子结点值。┃
┗━━━━━━━━━━━━━━━*/
TElemType RightChild(BiTree T, TElemType e);

/*━━━━━━━━━━━━━━━┓
┃(14)返回某结点的左兄弟结点值。┃
┗━━━━━━━━━━━━━━━*/
TElemType LeftSibling(BiTree T, TElemType e);

/*━━━━━━━━━━━━━━━┓
┃(15)返回某结点的右兄弟结点值。┃
┗━━━━━━━━━━━━━━━*/
TElemType RightSibling(BiTree T, TElemType e);

/*━━━━━━━━━━━━━━┓
┃(16-1)获取指向结点e的指针。 ┃
┗━━━━━━━━━━━━━━*/
BiTree LocationBiTree_1(BiTree T, TElemType e);

/*━━━━━━━━━━━━━━┓
┃(16-2)获取指向结点e的指针。 ┃
┗━━━━━━━━━━━━━━*/
BiTree LocationBiTree_2(BiTree T, TElemType e);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(17)将树T0插入到树T中成为结点e的子树，LR为插入标记，T0只有左子树。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
Status InsertBiTree(BiTree T, TElemType e, BiTree T0, int LR);

/*━━━━━━━━━━━━━━━━━━━━━━━┓
┃(18)删除e结点的左子树或右子树，LR为删除标记。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━*/
Status DeleteBiTree(BiTree T, TElemType e, int LR);

/*━━━━━━━━━━┓
┃(19)层序遍历二叉树。┃
┗━━━━━━━━━━*/
void LevelOrderTraverse(BiTree T, void(Visit)(TElemType));

/*━━━━━━━━━━━┓
┃(20-1)先序遍历二叉树。┃
┗━━━━━━━━━━━*/
void PreOrderTraverse_1(BiTree T, void(Visit)(TElemType));

/*━━━━━━━━━━━━━━━━┓
┃(20-2)算法6.1：先序遍历二叉树。 ┃
┗━━━━━━━━━━━━━━━━*/
Status PreOrderTraverse_2(BiTree T, Status(Visit)(TElemType));

/*━━━━━━━━━━━┓
┃(21-1)中序遍历二叉树。┃
┗━━━━━━━━━━━*/
void InOrderTraverse_1(BiTree T, void(Visit)(TElemType));

/*━━━━━━━━━━━━━━━━┓
┃(21-2)算法6.2：中序遍历二叉树。 ┃
┗━━━━━━━━━━━━━━━━*/
Status InOrderTraverse_2(BiTree T, Status(Visit)(TElemType));

/*━━━━━━━━━━━━━━━━┓
┃(21-3)算法6.3：中序遍历二叉树。 ┃
┗━━━━━━━━━━━━━━━━*/
Status InOrderTraverse_3(BiTree T, Status(Visit)(TElemType));

/*━━━━━━━━━━┓
┃(22)后序遍历二叉树。┃
┗━━━━━━━━━━*/
void PostOrderTraverse(BiTree T, void(Visit)(TElemType));

/*━━━━━━━━━━━━━┓
┃(23)按二叉树的结构打印树。┃
┗━━━━━━━━━━━━━*/
void PrintTree(BiTree T);

void InitBiTree(BiTree *T) {
    *T = NULL;
}

void ClearBiTree(BiTree *T) {
    if (*T)                                                        //二叉树不为空
    {
        if ((*T)->lchild)                                        //清空左树
            ClearBiTree(&((*T)->lchild));
        if ((*T)->rchild)                                        //清空右树
            ClearBiTree(&((*T)->rchild));

        free(*T);                                                //释放根结点

        *T = NULL;                                                //置空树指针
    }
}

void DestroyBiTree(BiTree *T) {
    //二叉树无法销毁
}

Status BiTreeEmpty(BiTree T) {
    return T == NULL ? TRUE : ERROR;
}

/*════╗
║ 算法6.4║
╚════*/
Status CreateBiTree(FILE *fp, BiTree *T) {
    char ch;

    Scanf(fp, "%c", &ch);

    if (ch == '^')
        *T = NULL;
    else {
        *T = (BiTree) malloc(sizeof(BiTNode));
        if (!(*T))
            exit(OVERFLOW);
        (*T)->data = ch;
        CreateBiTree(fp, &(*T)->lchild);
        CreateBiTree(fp, &(*T)->rchild);
    }

    return OK;
}

BiTree f(FILE *fp, BiTree *T) {
    char ch;

    Scanf(fp, "%c", &ch);

    if (ch == '^')
        *T = NULL;
    else {
        *T = (BiTree) malloc(sizeof(BiTNode));
        if (!(*T))
            exit(OVERFLOW);
        (*T)->data = ch;
        CreateBiTree(fp, &(*T)->lchild);
        CreateBiTree(fp, &(*T)->rchild);
    }
}

int BiTreeLength(BiTree T) {
    Node node[100];                                                //存储结点信息
    int i, len;

    i = len = 0;

    if (T) {
        node[i].left = T->lchild;
        node[i].right = T->rchild;
        node[i].n = 1;
        if (node[i].n > len)
            len = node[i].n;

        while (i >= 0) {
            while (node[i].left)                                    //访问左子树
            {
                node[i + 1].left = node[i].left->lchild;
                node[i + 1].right = node[i].left->rchild;
                node[i + 1].n = 2 * node[i].n;
                node[i].left = NULL;
                i++;
                if (node[i].n > len)
                    len = node[i].n;
            }

            if (node[i].right)                                    //左子树为空时访问右子树
            {
                node[i + 1].left = node[i].right->lchild;
                node[i + 1].right = node[i].right->rchild;
                node[i + 1].n = 2 * node[i].n + 1;
                node[i].right = NULL;
                i++;
                if (node[i].n > len)
                    len = node[i].n;
            }

            if (node[i].left == NULL && node[i].right == NULL)
                i--;
        }
    }

    return len;
}

int BiTreeDepth(BiTree T) {
    int LD, RD;

    if (T == NULL)
        return 0;                                //空树深度为0
    else {
        LD = BiTreeDepth(T->lchild);            //求左子树深度
        RD = BiTreeDepth(T->rchild);            //求右子树深度

        return (LD >= RD ? LD : RD) + 1;
    }
}

Status Root(BiTree T, TElemType *e) {
    if (!T)
        return ERROR;
    else {
        *e = T->data;
        return OK;
    }
}

TElemType Value(BiTree p) {
    return p->data;
}

void Assign(BiTree p, TElemType value) {
    p->data = value;
}

TElemType Parent(BiTree T, TElemType e) {
    BiTNode node[100];
    int i = 0;

    if (T == NULL || (T != NULL && e == T->data))
        return '\0';

    node[i] = *T;

    while (i >= 0) {
        while (node[i].lchild) {
            if (node[i].lchild->data == e)
                return node[i].data;
            node[i + 1] = *(node[i].lchild);
            node[i].lchild = NULL;
            i++;
        }

        if (node[i].rchild) {
            if (node[i].rchild->data == e)
                return node[i].data;
            node[i + 1] = *(node[i].rchild);
            node[i].rchild = NULL;
            i++;
        }

        if (node[i].lchild == NULL && node[i].rchild == NULL)
            i--;
    }

    if (i < 0)
        return '\0';
}

TElemType LeftChild(BiTree T, TElemType e) {
    BiTNode node[100];
    int i = 0;

    if (!T)
        return '\0';

    node[i] = *T;

    while (i >= 0) {
        while (node[i].data != e && node[i].lchild) {
            node[i + 1] = *(node[i].lchild);
            node[i].lchild = NULL;
            i++;
        }

        if (node[i].data == e) {
            if (node[i].lchild)
                return node[i].lchild->data;
            else
                return '\0';
        }

        if (node[i].rchild) {
            node[i + 1] = *(node[i].rchild);
            node[i].rchild = NULL;
            i++;
        }

        if (node[i].lchild == NULL && node[i].rchild == NULL && node[i].data != e)
            i--;
    }

    if (i < 0)
        return '\0';
}

TElemType RightChild(BiTree T, TElemType e) {
    BiTNode node[100];
    int i = 0;

    if (!T)
        return '\0';

    node[i] = *T;

    while (i >= 0) {
        while (node[i].data != e && node[i].lchild) {
            node[i + 1] = *(node[i].lchild);
            node[i].lchild = NULL;
            i++;
        }

        if (node[i].data == e) {
            if (node[i].rchild)
                return node[i].rchild->data;
            else
                return '\0';
        }

        if (node[i].rchild) {
            node[i + 1] = *(node[i].rchild);
            node[i].rchild = NULL;
            i++;
        }
        if (node[i].lchild == NULL && node[i].rchild == NULL)
            i--;
    }

    if (i < 0)
        return '\0';
}

TElemType LeftSibling(BiTree T, TElemType e) {
    BiTNode node[100];
    int i = 0;

    if (T == NULL || (T != NULL && e == T->data))
        return '\0';

    node[i] = *T;

    while (i >= 0) {
        while (node[i].rchild) {
            if (node[i].rchild->data == e) {
                if (node[i].lchild)
                    return node[i].lchild->data;
                else
                    return '\0';
            }

            node[i + 1] = *(node[i].rchild);
            node[i].rchild = NULL;
            i++;
        }

        if (node[i].lchild) {
            if (node[i].lchild->data == e)
                return '\0';
            node[i + 1] = *(node[i].lchild);
            node[i].lchild = NULL;
            i++;
        }

        if (node[i].lchild == NULL && node[i].rchild == NULL)
            i--;
    }

    if (i < 0)
        return '\0';
}

TElemType RightSibling(BiTree T, TElemType e) {
    BiTNode node[100];
    int i = 0;

    if (T == NULL || (T != NULL && e == T->data))
        return '\0';

    node[i] = *T;

    while (i >= 0) {
        while (node[i].lchild) {
            if (node[i].lchild->data == e) {
                if (node[i].rchild)
                    return node[i].rchild->data;
                else
                    return '\0';
            }
            node[i + 1] = *(node[i].lchild);
            node[i].lchild = NULL;
            i++;
        }

        if (node[i].rchild) {
            if (node[i].rchild->data == e)
                return '\0';
            node[i + 1] = *(node[i].rchild);
            node[i].rchild = NULL;
            i++;
        }

        if (node[i].lchild == NULL && node[i].rchild == NULL)
            i--;
    }

    if (i < 0)
        return '\0';
}

BiTree LocationBiTree_1(BiTree T, TElemType e) {
    BiTNode node[100];
    int i = 0;

    if (T == NULL)
        return NULL;

    if (T->data == e)
        return T;

    node[i] = *T;

    while (i >= 0) {
        while (node[i].lchild) {
            if (node[i].lchild->data == e)
                return node[i].lchild;
            node[i + 1] = *(node[i].lchild);
            node[i].lchild = NULL;
            i++;
        }

        if (node[i].rchild) {
            if (node[i].rchild->data == e)
                return node[i].rchild;
            node[i + 1] = *(node[i].rchild);
            node[i].rchild = NULL;
            i++;
        }

        if (node[i].lchild == NULL && node[i].rchild == NULL)
            i--;
    }

    if (i < 0)
        return NULL;
}

BiTree LocationBiTree_2(BiTree T, TElemType e) {
    BiTree p = NULL;

    if (T) {
        if (T->data == e)
            p = T;
        else {
            if (p = LocationBiTree_2(T->lchild, e))
                return p;

            if (p = LocationBiTree_2(T->rchild, e))
                return p;
        }
    }

    return p;
}

Status InsertBiTree(BiTree T, TElemType e, BiTree T0, int LR) {
    BiTree p = LocationBiTree_1(T, e);

    if (p) {
        T0->rchild = LR ? p->rchild : p->lchild;
        LR ? (p->rchild = T0) : (p->lchild = T0);

        return OK;
    }

    return ERROR;
}

Status DeleteBiTree(BiTree T, TElemType e, int LR) {
    BiTree p = LocationBiTree_2(T, e);

    if (p) {
        LR ? ClearBiTree(&(p->rchild)) : ClearBiTree(&(p->lchild));

        return OK;
    }

    return ERROR;
}

void LevelOrderTraverse(BiTree T, void(Visit)(TElemType)) {
    int i, j;
    BiTree p[100];                    //树指针数组

    i = j = 0;

    if (T)
        p[j++] = T;

    while (i < j) {
        Visit(p[i]->data);
        if (p[i]->lchild)
            p[j++] = p[i]->lchild;
        if (p[i]->rchild)
            p[j++] = p[i]->rchild;
        i++;
    }
}

void PreOrderTraverse_1(BiTree T, void(Visit)(TElemType)) {
    if (T) {
        Visit(T->data);
        PreOrderTraverse_1(T->lchild, Visit);
        PreOrderTraverse_1(T->rchild, Visit);
    }
}

/*════╗
║ 算法6.1║
╚════*/
Status PreOrderTraverse_2(BiTree T, Status(Visit)(TElemType)) {
    if (T) {
        if (Visit(T->data)) {
            PreOrderTraverse_2(T->lchild, Visit);
            PreOrderTraverse_2(T->rchild, Visit);
        }
        return OK;
    } else
        return ERROR;
}

void InOrderTraverse_1(BiTree T, void(Visit)(TElemType)) {
    if (T) {
        InOrderTraverse_1(T->lchild, Visit);
        Visit(T->data);
        InOrderTraverse_1(T->rchild, Visit);
    }
}

/*════╗
║ 算法6.2║
╚════*/
Status InOrderTraverse_2(BiTree T, Status(Visit)(TElemType)) {
    SqStack S;
    SElemType_Sq p;

    InitStack_Sq(&S);
    Push_Sq(&S, T);

    while (!StackEmpty_Sq(S)) {
        while (GetTop_Sq(S, &p) && p)                //栈顶元素不为空
            Push_Sq(&S, p->lchild);                    //向左走到尽头

        Pop_Sq(&S, &p);                                //空指针退栈

        if (!StackEmpty_Sq(S))                        //访问结点，向右一步
        {
            Pop_Sq(&S, &p);
            if (!Visit(p->data))
                return ERROR;
            Push_Sq(&S, p->rchild);
        }
    }
    return OK;
}

/*════╗
║ 算法6.3║
╚════*/
Status InOrderTraverse_3(BiTree T, Status(Visit)(TElemType)) {
    SqStack S;
    SElemType_Sq p;

    InitStack_Sq(&S);
    p = T;

    while (p || !StackEmpty_Sq(S)) {
        if (p) {
            Push_Sq(&S, p);
            p = p->lchild;
        } else {
            Pop_Sq(&S, &p);
            if (!Visit(p->data))
                return ERROR;
            p = p->rchild;
        }
    }
    return OK;
}

void PostOrderTraverse(BiTree T, void(Visit)(TElemType)) {
    if (T) {
        PostOrderTraverse(T->lchild, Visit);
        PostOrderTraverse(T->rchild, Visit);
        Visit(T->data);
    }
}

void PrintTree(BiTree T) {
    int row, col;
    int i, j, m, l, r;
    BiTNode a[100][100] = {};                    //用一个足够大的矩阵按原样存储树

    if (T) {
        row = BiTreeDepth(T);                    //总行数
        col = pow(2, row) - 1;                    //总列数

        for (i = 1; i <= row - 1; i++) {
            for (j = 1; j <= pow(2, i - 1); j++) {
                m = (2 * j - 1) * pow(2, row - i);        //当前行结点相对位序
                l = (4 * j - 3) * pow(2, row - i - 1);    //下一行结点相对位序
                r = (4 * j - 1) * pow(2, row - i - 1);

                if (i == 1)                        //初始化
                    a[i][m] = *T;

                if (a[i][m].lchild)                //下一行
                    a[i + 1][l] = *(a[i][m].lchild);

                if (a[i][m].rchild)                //下一行
                    a[i + 1][r] = *(a[i][m].rchild);
            }
        }

        for (i = 1; i <= row; i++) {
            for (j = 1; j <= col; j++) {
                if (a[i][j].data)
                    printf("%c", a[i][j].data);
                else
                    printf(" ");
            }
            printf("\n");
        }
    }
}


#endif //DATA_STRUCTURE_BINARYTREE_H
