//
//文件夹: 06 Tree_BinaryTree/05 ParentTree
//文件名: ParentTree
//内　容：树的双亲表示结构相关操作列表
//Author Huangcp
//Date 2019/9/12 下午 10:40
//Version 1.0
//

#ifndef DATA_STRUCTURE_PARENTTREE_H
#define DATA_STRUCTURE_PARENTTREE_H

#include <stdio.h>
#include "../../01 Introduction/Status.h"                //**▲01 绪论**//
#include "../../01 Introduction/Scanf.h"                //**▲01 绪论**//
#include "../../03 Stack_Queue/01 SequenceStack/SequenceStack.h"    //**▲03 栈和队列**//

/* 宏定义 */
#define MAX_TREE_SIZE 100                        //树的最大结点数

/* 双亲树类型定义 */
#ifndef DATA_STRUCTURE_MFSET_H                                    /* 在并查集结构中此类型将重新定义 */
typedef char TElemType_P;                        //假设树中元素均为字符
#endif
typedef struct PTNode                            //结点结构
{
    TElemType_P data;
    int parent;                                    //双亲位置域
} PTNode;
typedef struct                                    //树结构
{
    PTNode nodes[MAX_TREE_SIZE];                //根结点位置默认到0，为了操作方便
    int n;                                        //树的结点数
} PTree;

/* 树的双亲存储结构函数列表 */
/*━━━━━━━━━━━━━┓
┃(01)构造空树T (初始化树)。┃
┗━━━━━━━━━━━━━*/
void InitTree_P(PTree *T);

/*━━━━━━━┓
┃(02)清空树T。 ┃
┗━━━━━━━*/
void ClearTree_P(PTree *T);

/*━━━━━━━┓
┃(03)销毁树T。 ┃
┗━━━━━━━*/
void DestroyTree_P(PTree *T);

/*━━━━━━━━━━━┓
┃(04)判断树T是否为空。 ┃
┗━━━━━━━━━━━*/
Status TreeEmpty_P(PTree T);

/*━━━━━━━━━━━┓
┃(05)按层序序列构造树。┃
┗━━━━━━━━━━━*/
Status CreateTree_P(FILE *fp, PTree *T);

/*━━━━━━━━┓
┃(06)返回树的度。┃
┗━━━━━━━━*/
int TreeDegree_P(PTree T);

/*━━━━━━━━━┓
┃(07)返回树的深度。┃
┗━━━━━━━━━*/
int TreeDepth_P(PTree T);

/*━━━━━━━━━━━┓
┃(08)返回树的根结点值。┃
┗━━━━━━━━━━━*/
TElemType_P Root_P(PTree T);

/*━━━━━━━━━━━━━━━━━━━━━┓
┃(09)返回树中第i个结点的值（按层序计数）。 ┃
┗━━━━━━━━━━━━━━━━━━━━━*/
TElemType_P Value_P(PTree T, int i);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(10)返回结点e的值位置(在数组中位置)，-1代表无此结点。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
int Order_P(PTree T, TElemType_P e);

/*━━━━━━━━━━━━━┓
┃(11)替换结点e的值为value。┃
┗━━━━━━━━━━━━━*/
Status Assign_P(PTree *T, TElemType_P e, TElemType_P value);

/*━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(12)返回结点e的第order个孩子的值（从左至右计数）。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━*/
TElemType_P ChildValue_P(PTree T, TElemType_P e, int order);

/*━━━━━━━━━━━━━━━━━━━━━━┓
┃(13)返回元素e的左（右）兄弟，mark标记左右。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━*/
TElemType_P Sibling_P(PTree T, TElemType_P e, int mark);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(14)返回结点p的孩子结点（子树）个数，返回负数代表结点p不存在。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
int ChildCount_P(PTree T, TElemType_P p);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(15)返回树T中p结点的第i个孩子（层序计数）的位置，i=0定义为最后一个孩子。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
int ChildSeat_P(PTree T, TElemType_P p, int i);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(16)将结点e插入为树T中p结点的第i个孩子（层序计数），i=0定义为最后一个孩子。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
Status InsertChild_P(PTree *T, TElemType_P p, int i, TElemType_P e);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(17)将树t插入为树T中p结点的第i棵子树（层序计数），i=0定义为最后一棵子树。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
Status InsertTree_P(PTree *T, TElemType_P p, int i, PTree t);

/*━━━━━━━━━━━━━━━━┓
┃(18)删除树T中p结点的第i棵子树。 ┃
┗━━━━━━━━━━━━━━━━*/
Status DeleteTree_P(PTree *T, TElemType_P p, int i);

/*━━━━━━━━┓
┃(19)层序遍历树。┃
┗━━━━━━━━*/
void LevelOrderTraverse_P(PTree T, void(Visit)(TElemType_P));

/*━━━━━━┓
┃(20)打印树。┃
┗━━━━━━*/
void Print_P(PTree T);


void InitTree_P(PTree *T) {
    (*T).n = 0;                                        //结点数量
}

void ClearTree_P(PTree *T) {
    (*T).n = 0;
}

void DestroyTree_P(PTree *T) {
    //此存储结构下的树无法销毁
}

Status TreeEmpty_P(PTree T) {
    return (T.n ? FALSE : TRUE);
}

Status CreateTree_P(FILE *fp, PTree *T) {
    TElemType_P ch, p, tmp;
    int i, j;

    Scanf(fp, "%c", &ch);
    printf("录入树的根结点 %c \n", ch);
    Scanf(fp, "%c", &tmp);                            //跳过换行符

    if (ch != '^') {
        i = 0;                                        //根结点起点设为0
        (*T).nodes[i].data = ch;
        (*T).nodes[i].parent = -1;

        j = -1;
        while (!feof(fp)) {
            Scanf(fp, "%c", &p);
            printf("依次录入 %c 的孩子结点：", p);
            j++;
            while (1) {
                Scanf(fp, "%c", &ch);
                if (ch == '^' || ch == '\n') {
                    if (ch == '^') {
                        printf("%c", ch);
                        Scanf(fp, "%c", &tmp);        //跳过换行符
                    }

                    break;
                } else {
                    printf("%c", ch);
                    i++;
                    (*T).nodes[i].data = ch;
                    (*T).nodes[i].parent = j;
                }
            }

            printf("\n");
        }

        (*T).n = i + 1;
    }

    return OK;
}

int TreeDegree_P(PTree T) {
    int i, tmp, count;
    int max;

    max = count = 0;

    if (T.n) {
        tmp = T.nodes[0].parent;

        for (i = 0; i < T.n; i++) {
            if (T.nodes[i].parent != tmp) {
                tmp = T.nodes[i].parent;
                count = 1;
            } else
                count++;

            if (count > max)
                max = count;
        }
    }

    return max;
}

int TreeDepth_P(PTree T)                                        //由于按层序序列存储，故最后存储的结点必在最大层
{
    int k, level;

    k = T.n - 1;
    level = 0;

    if (T.n != 0) {
        level++;
        k = T.nodes[k].parent;

        while (k != -1) {
            level++;
            k = T.nodes[k].parent;
        }

    }

    return level;
}

TElemType_P Root_P(PTree T) {
    if (T.n)
        return T.nodes[0].data;

    return '\0';
}

TElemType_P Value_P(PTree T, int i) {
    if (T.n && i > 0 && i <= T.n)
        return T.nodes[i - 1].data;
    else
        return '\0';
}

int Order_P(PTree T, TElemType_P e) {
    int i;
    int k = -1;

    for (i = 0; i < T.n; i++) {
        if (T.nodes[i].data == e) {
            k = i;
            break;
        }
    }

    return k;
}

Status Assign_P(PTree *T, TElemType_P e, TElemType_P value) {
    int i;

    for (i = 0; i < (*T).n; i++) {
        if ((*T).nodes[i].data == e) {
            (*T).nodes[i].data = value;
            return OK;
        }
    }

    return ERROR;
}

TElemType_P ChildValue_P(PTree T, TElemType_P e, int order) {
    int i, p, count;

    count = 0;
    for (i = 1; i < T.n; i++) {
        p = T.nodes[i].parent;
        if (T.nodes[p].data == e) {
            count++;
            if (count == order)
                return T.nodes[i].data;
        }
    }

    return '\0';
}

TElemType_P Sibling_P(PTree T, TElemType_P e, int mark) {
    int i;

    if (!TreeEmpty_P(T) && e != T.nodes[0].data) {
        for (i = 1; i < T.n; i++) {
            if (mark == 0)                                        //左兄弟
            {
                if (T.nodes[i].data == e)
                    break;

                if (T.nodes[i].data != e && i + 1 < T.n && T.nodes[i + 1].parent == T.nodes[i].parent &&
                    T.nodes[i + 1].data == e)
                    return T.nodes[i].data;
            }

            if (mark == 1)                                        //右兄弟
            {
                if (T.nodes[i].data == e && i + 1 < T.n && T.nodes[i].parent == T.nodes[i + 1].parent)
                    return T.nodes[i + 1].data;
            }
        }
    }


    return '\0';
}

int ChildCount_P(PTree T, TElemType_P p) {
    int k1, k2, count;

    if (TreeEmpty_P(T))                        //空树
        return -1;

    k1 = Order_P(T, p);

    if (k1 < 0)                                //p结点不存在
        return -2;

    k2 = k1 + 1;
    count = 0;
    while (k2 < T.n)                            //统计孩子个数
    {
        if (T.nodes[k2].parent == k1)
            count++;
        if (T.nodes[k2].parent > k1)
            break;
        k2++;
    }

    return count;
}

int ChildSeat_P(PTree T, TElemType_P p, int i) {
    int k0, k1, k2, count;

    if (TreeEmpty_P(T))                            //空树
        return -1;

    k0 = ChildCount_P(T, p);        //k0标记孩子个数

    if (i < 0 || k0 < 0 || i > k0 + 1)        //插入位置不正确
        return -2;

    k1 = Order_P(T, p);

    k2 = k1 + 1;
    if (i == 0)                        //此时i为p最后一个结点的下一个位置
    {
        while (k2 < T.n) {
            if (T.nodes[k2].parent > k1)
                break;
            k2++;
        }
    } else {
        count = 0;

        while (k2 < T.n) {
            if (T.nodes[k2].parent >= k1) {
                count++;
                if (count == i)
                    break;
            }

            k2++;
        }
    }

    return k2;
}

Status InsertChild_P(PTree *T, TElemType_P p, int i, TElemType_P e) {
    int k0, start, end;

    if (TreeEmpty_P((*T)) || !e)                //空树或e为空字符
        return ERROR;

    k0 = 0;                                    //k0标记p的位置
    while (k0 < (*T).n) {
        if ((*T).nodes[k0].data == p)
            break;
        k0++;
    }

    if (k0 == (*T).n)                            //p不存在
        return ERROR;

    start = ChildSeat_P(*T, p, i);            //e结点的插入位置
    if (start <= 0)                            //插入位置不正确
        return ERROR;

    end = (*T).n;
    while (end > start) {
        (*T).nodes[end].data = (*T).nodes[end - 1].data;
        if ((*T).nodes[end - 1].parent < start)
            (*T).nodes[end].parent = (*T).nodes[end - 1].parent;
        else
            (*T).nodes[end].parent = (*T).nodes[end - 1].parent + 1;
        end--;
    }

    (*T).nodes[start].data = e;
    (*T).nodes[start].parent = k0;
    (*T).n++;

    return OK;
}

Status InsertTree_P(PTree *T, TElemType_P p, int i, PTree t) {
    int k;

    if (TreeEmpty_P((*T)) || TreeEmpty_P(t))                //空树
        return ERROR;

    for (k = 0; k < t.n; k++) {
        if (k == 0)
            InsertChild_P(T, p, i, t.nodes[k].data);
        else
            InsertChild_P(T, t.nodes[t.nodes[k].parent].data, 0, t.nodes[k].data);
    }

    return OK;
}

Status DeleteTree_P(PTree *T, TElemType_P p, int i) {
    int k1;                                            //k1标记p的位置
    int k2, count;                                    //k2标记第i棵子树起点
    int k3;
    int stack[MAX_TREE_SIZE], m, n;
    int k4, k5, order[MAX_TREE_SIZE] = {};

    for (k1 = 0; k1 < (*T).n; k1++) {
        if ((*T).nodes[k1].data == p)
            break;
        if (k1 == (*T).n - 1)
            return ERROR;
    }

    count = 0;
    for (k2 = k1 + 1; k2 < (*T).n; k2++) {
        if ((*T).nodes[k2].parent == k1) {
            count++;
            if (count == i)
                break;
        }
        if (k2 == (*T).n - 1)
            return ERROR;
    }

    m = n = 0;
    stack[n] = k2;
    n++;
    (*T).nodes[k2].data = '\0';                    //抹掉此处的值

    k3 = k2 + 1;
    while (k3 < (*T).n && m < n) {
        if ((*T).nodes[k3].parent < stack[m])
            k3++;
        else if ((*T).nodes[k3].parent > stack[m])
            m++;
        else        //(*T).nodes[k3].parent==stack[m]
        {
            (*T).nodes[k3].data = '\0';                    //抹掉此处的值
            stack[n] = k3;
            n++;
            k3++;
        }
    }

    k5 = 0;
    for (k4 = 0; k4 < (*T).n; k4++)                            //遍历树，找出各结点现在的实际位置
    {
        if ((*T).nodes[k4].data) {
            order[k4] = k5;
            k5++;

            if (k4)                                        //不为头结点
                (*T).nodes[k4].parent = order[(*T).nodes[k4].parent];    //当前结点双亲结点位置发生变化
        }
    }

    k4 = -1;
    k5 = 0;
    while (k5 < (*T).n)                                        //遍历，去掉删除的结点
    {
        if ((*T).nodes[k5].data) {
            k4++;
            (*T).nodes[k4].data = (*T).nodes[k5].data;
            (*T).nodes[k4].parent = (*T).nodes[k5].parent;
        }

        k5++;
    }

    (*T).n = k4 + 1;

    return OK;
}

void LevelOrderTraverse_P(PTree T, void(Visit)(TElemType_P)) {
    int i;

    for (i = 0; i < T.n; i++)
        Visit(T.nodes[i].data);
}

void Print_P(PTree T) {
    int row[MAX_TREE_SIZE];                        //各结点实际所处行
    int col[MAX_TREE_SIZE];                        //各结点在其兄弟中的次序
    int i, j, tmp;                                //tmp存放当前结点的父结点位置
    int x[MAX_TREE_SIZE], y[MAX_TREE_SIZE];        //存放各结点打印时所处行和列（从0开始计数）
    int count;
    int t[MAX_TREE_SIZE][MAX_TREE_SIZE] = {};        //孩子链表存储结构
    char a[MAX_TREE_SIZE][MAX_TREE_SIZE] = {};    //按树的形状存放结点
    SqStack S;
    SElemType_Sq e;

    if (T.n) {
        j = 1;                                //j统计某孩子次序
        row[0] = 1;
        col[0] = j;
        tmp = T.nodes[0].parent;

        for (i = 1; i < T.n; i++) {
            if (T.nodes[i].parent != tmp) {
                j = 1;                            //若与上一个结点不属于同一双亲结点，则重新开始计数
                tmp = T.nodes[i].parent;
            } else
                j++;

            col[i] = j;
            row[i] = row[T.nodes[i].parent] + 1;
        }

        for (i = 1; i < T.n; i++)                                    //构造孩子链表
        {
            tmp = T.nodes[i].parent;
            t[tmp][col[i] - 1] = i;
        }

        count = 0;                                                //追踪行
        InitStack_Sq(&S);
        Push_Sq(&S, 0);
        while (!StackEmpty_Sq(S))                                    //确定每个结点在树中所在行
        {
            GetTop_Sq(S, &e);
            if (col[e] != 1)
                count++;
            x[e] = count;

            if (t[e][0])
                Push_Sq(&S, t[e][0]);
            else {
                while (!StackEmpty_Sq(S)) {
                    Pop_Sq(&S, &e);
                    if (t[T.nodes[e].parent][col[e]]) {
                        Push_Sq(&S, t[T.nodes[e].parent][col[e]]);
                        break;
                    }
                }
            }

        }

        for (i = 0; i < T.n; i++)                                        //确定每个结点在树中所在列
            y[i] = row[i] - 1;

        for (i = 0; i < T.n; i++)                                        //将各结点放入a中适当位置
            a[x[i]][2 * y[i]] = T.nodes[i].data;

        for (i = 0; i <= count; i++) {
            for (j = 0; j <= 2 * y[T.n - 1]; j++) {
                if (a[i][j])
                    printf("%c", a[i][j]);
                else
                    printf(".");
            }

            printf("\n");
        }
    } else
        printf("空树无法打印！！\n");
}

#endif //DATA_STRUCTURE_PARENTTREE_H
