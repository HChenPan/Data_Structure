//
//文件夹: 07 Graph\07 MiniSpanningTree
//文件名: MiniSpanningTree
//内　容：最小生成树相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 02:41
//Version 1.0
//

#ifndef DATA_STRUCTURE_MINISPANNINGTREE_H
#define DATA_STRUCTURE_MINISPANNINGTREE_H

#include <stdio.h>
#include "../../06 Tree_BinaryTree/08 MFSet/MFSet.h"    //**▲06 树和二叉树**//
#include "../01 MGraph/MGraph.h"                    //**07 Graph**//

/* 最小生成树类型定义 */
typedef struct {
    VertexType_M adjvex;        //较早加入当前边的端点
    VRType lowcost;                //当前边的权值
} Edge;                            //辅助数组
typedef struct {
    int a, b;                    //端点
    int w;                        //权值
} EdgeSetType;

/* 最小生成树函数列表 */
/**
(01)算法7.9：用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边。 
**/
void MinSpanTree_PRIM_1(MGraph G, VertexType_M u);

/**
(02)返回最小边联接的端点序号。
**/
int Minimum_1(Edge closedge[], int n);

/**
(03)普里姆算法，与教材算法只在形式上有所区别。
**/
void MinSpanTree_PRIM_2(MGraph G, VertexType_M u);

/**
(04)返回最小边联接的端点序号。
**/
int Minimum_2(MGraph G, int start[], int mark[], int n);

/**
(05)用克鲁斯卡尔算法构造网G的最小生成树T，并输出T的各条边。 
**/
void MinSpanTree_KRUSKAL(MGraph G);

/**
(06)按权值从小到大排列各边。
**/
void sort(EdgeSetType EdgeSet[], int left, int right);

/**
(07)将网中各顶点初始化为一个并查集S。 
**/
void Initial(MGraph G, MFSet *S);

/**
(08)建立一个二元关系R。 
**/
void BuildRelation(Relation *R, int a, int b);


void MinSpanTree_PRIM_1(MGraph G, VertexType_M u)    //假设图的权值均大于0
{
    int i, j, k;
    Edge closedge[G.vexnum + 1];                        //0号单元弃用

    k = LocateVex_M(G, u);

    for (j = 1; j <= G.vexnum; j++)                        //辅助数组初始化
    {
        if (j != k) {

            closedge[j].adjvex = u;
            closedge[j].lowcost = G.arcs[k][j].adj;
        }
    }

    closedge[k].lowcost = 0;

    printf("    %c\n", u);
    for (i = 1; i <= G.vexnum - 1; i++)                    //总共需要G.vexnum-1次寻找最小边
    {
        k = Minimum_1(closedge, G.vexnum);
        printf("%2d, %c\n", closedge[k].lowcost, G.vexs[k]);

        closedge[k].lowcost = 0;

        for (j = 1; j <= G.vexnum; j++) {                                            //当前树到某一顶点的最小权值小于上一棵树到某一顶点的最小权值
            if (G.arcs[k][j].adj < closedge[j].lowcost) {
                closedge[j].adjvex = G.vexs[k];
                closedge[j].lowcost = G.arcs[k][j].adj;
            }
        }
    }
}

int Minimum_1(Edge closedge[], int n) {
    int i, j;
    int min = INT_MAX;

    for (i = 1, j = 0; i <= n; i++) {
        if (closedge[i].lowcost)                        //从权值不为0的边中选择拥有最小权值的边
        {
            if (closedge[i].lowcost <= min) {
                min = closedge[i].lowcost;
                j = i;
            }
        }
    }

    return j;
}

void MinSpanTree_PRIM_2(MGraph G, VertexType_M u) {
    int i, j, k;
    int start[G.vexnum + 1], mark[G.vexnum + 1];

    if (G.vexnum == 1) {
        printf("此有向网只有一个顶点，其最小生成树为：%c\n", G.vexs[1]);
        return;
    }

    k = LocateVex_M(G, u);

    for (j = 1; j <= G.vexnum; j++) {
        start[j] = k;
        if (j != k)
            mark[j] = 0;
        else
            mark[j] = 1;
    }

    for (i = 1; i <= G.vexnum - 1; i++) {
        k = Minimum_2(G, start, mark, G.vexnum);
        printf("%c—%c, %2d\n", G.vexs[start[k]], G.vexs[k], G.arcs[start[k]][k].adj);

        mark[k] = 1;

        for (j = 1; j <= G.vexnum; j++) {
            if (mark[j] != 1) {
                if (G.arcs[k][j].adj < G.arcs[start[j]][j].adj)
                    start[j] = k;
            }
        }
    }
}

int Minimum_2(MGraph G, int start[], int mark[], int n) {
    int i, j;
    int min = INT_MAX;

    for (i = 1, j = 0; i <= n; i++) {
        if (mark[i] != 1 && G.arcs[start[i]][i].adj < min) {
            min = G.arcs[start[i]][i].adj;
            j = i;
        }
    }

    return j;
}

void MinSpanTree_KRUSKAL(MGraph G) {
    int i, j, count;
    int x, y;
    EdgeSetType r[100];
    MFSet S;                                //图中各顶点集合
    Relation R;

    if (G.vexnum == 1) {
        printf("此有向网只有一个顶点，其最小生成树为：%c\n", G.vexs[1]);
        return;
    }

    Initial(G, &S);

    count = 0;
    for (i = 1; i <= G.vexnum; i++)                //找出无向网中的各条边
    {
        for (j = i; j <= G.vexnum; j++) {
            if (G.arcs[i][j].adj != INFINITY) {
                ++count;
                r[count].a = i;
                r[count].b = j;
                r[count].w = G.arcs[i][j].adj;
            }
        }
    }

    sort(r, 1, G.arcnum);                    //对各条边根据权重从小到大排序

    count = 0;                                //统计加入树的边数
    for (i = 1; i <= G.arcnum; i++) {
        x = find_mfset(S, r[i].a);
        y = find_mfset(S, r[i].b);

        if (x != y)                            //通过并查集判断加入的边是否会形成回路
        {
            BuildRelation(&R, r[i].a, r[i].b);
            EquivalenceClass_mfset_1(&S, R);

            printf("%c—%c  %2d\n", G.vexs[r[i].a], G.vexs[r[i].b], r[i].w);

            if (++count == G.vexnum - 1)
                break;
        }
    }
}

void sort(EdgeSetType EdgeSet[], int left, int right)//快速排序
{
    int i, j;
    EdgeSetType tmp;

    i = left;
    j = right;

    if (i < j) {
        tmp = EdgeSet[left];

        while (i != j) {
            while (i < j && EdgeSet[j].w > tmp.w)        //从右往左扫描
                j--;

            if (i < j) {
                EdgeSet[i] = EdgeSet[j];
                i++;
            }

            while (i < j && EdgeSet[i].w < tmp.w)        //从左往右扫描
                i++;

            if (i < j) {
                EdgeSet[j] = EdgeSet[i];
                j--;
            }
        }

        EdgeSet[i] = tmp;                            //至此i==j，完成第一轮快排

        sort(EdgeSet, left, i - 1);
        sort(EdgeSet, j + 1, right);
    }
}

void Initial(MGraph G, MFSet *S) {
    int i;
    FILE *fp;

    fp = tmpfile();                                    //创建并打开一个临时文件夹

    fprintf(fp, "%d\n", G.vexnum);
    for (i = 1; i <= G.vexnum; i++)
        fprintf(fp, "%d ", i);
    fseek(fp, 0, SEEK_SET);

    Initial_mfset(fp, S);
}

void BuildRelation(Relation *R, int a, int b) {
    R->n = 1;
    R->nodes[0].i = a;
    R->nodes[0].j = b;
}

#endif //DATA_STRUCTURE_MINISPANNINGTREE_H
