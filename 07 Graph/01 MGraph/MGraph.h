//
//文件夹: 07 Graph/01 MGraph
//文件名: MGraph
//内　容：图、表的数组（邻接矩阵）表示法相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 02:22
//Version 1.0
//

#ifndef DATA_STRUCTURE_MGRAPH_H
#define DATA_STRUCTURE_MGRAPH_H

#include <stdio.h>
#include <limits.h>                                            //提供宏INT_MAX
#include <stdlib.h>                                        //提供rand、srand原型
#include <stdarg.h>                                            //提供宏va_list、va_start、va_arg、va_end
#include "../../01 Introduction/Status.h"                            //**01 Introduction**//
#include "../../01 Introduction/Scanf.h"                            //**01 Introduction**//
#include "../../03 Stack_Queue/07 LinkQueue/LinkQueue.h"    //**03 Stack_Queue**//

/* 宏定义 */
#define INFINITY INT_MAX                        //最大值∞
#define MAX_VERTEX_NUM 20                        //最大顶点个数

/* 图、表的数组（邻接矩阵）表示法类型定义 */
typedef enum {
    DG, DN, UDG, UDN
} GraphKind;        //0-有向图，1-有向网（带权值），2-无向图，3-无向网（带权值）
typedef struct {
} InfoType;                        //弧相关信息
typedef int VRType;                                //图、表顶点关系类型
typedef struct ArcCell {
    VRType adj;                                    //带权图中表示权值，无权图中用0、1表示是否相邻
    InfoType info;                                //该弧相关信息，可以忽略
} ArcCell;
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM + 1][MAX_VERTEX_NUM + 1]; //邻接矩阵

/* 图、表（数组表示法）的存储表示 */
typedef char VertexType_M;                //图、表顶点类型
typedef struct {
    VertexType_M vexs[MAX_VERTEX_NUM + 1];//顶点向量
    AdjMatrix arcs;                        //邻接矩阵
    int vexnum, arcnum;                    //图、表的当前顶点数和弧数
    int IncInfo;                        //IncInfo为0则各弧不含其它信息
    GraphKind kind;                        //图、表的种类标志
} MGraph;

/* 全局变量 */
Status visited[MAX_VERTEX_NUM + 1];        //标志数组
void (*VisitFunc)(VertexType_M e);        //函数指针变量

/* 图、表（数组表示法）函数列表 */
/*━━━━━━━━━━━━━┓
┃(01)算法7.1：创建图、表。 ┃
┗━━━━━━━━━━━━━*/
Status CreateGraph_M(FILE *fp, MGraph *G);

/*━━━━━━━━┓
┃(02)构造有向图。┃
┗━━━━━━━━*/
Status CreateDG_M(FILE *fp, MGraph *G);

/*━━━━━━━━┓
┃(03)构造有向网。┃
┗━━━━━━━━*/
Status CreateDN_M(FILE *fp, MGraph *G);

/*━━━━━━━━┓
┃(04)构造无向图。┃
┗━━━━━━━━*/
Status CreateUDG_M(FILE *fp, MGraph *G);

/*━━━━━━━━━━━━━┓
┃(05)算法7.2：构造无向网。 ┃
┗━━━━━━━━━━━━━*/
Status CreateUDN_M(FILE *fp, MGraph *G);

/*━━━━━━━━━┓
┃(06)清空图（网）。┃
┗━━━━━━━━━*/
void ClearGraph_M(MGraph *G);

/*━━━━━━━━━━━┓
┃(07)寻找顶点u的位置。 ┃
┗━━━━━━━━━━━*/
int LocateVex_M(MGraph G, VertexType_M u);

/*━━━━━━━━━━━━┓
┃(08)返回第v个结点的值。 ┃
┗━━━━━━━━━━━━*/
VertexType_M GetVex_M(MGraph G, int order);

/*━━━━━━━━━━━┓
┃(09)对顶点v赋值value。┃
┗━━━━━━━━━━━*/
Status PutVex_M(MGraph *G, VertexType_M v, VertexType_M value);

/*━━━━━━━━━━━━━━━━┓
┃(10)返回v的第一个邻接顶点序号。 ┃
┗━━━━━━━━━━━━━━━━*/
int FirstAdjVex_M(MGraph G, VertexType_M v);

/*━━━━━━━━━━━━━━━━━━━┓
┃(11)返回v相对于w的下一个邻接顶点序号。┃
┗━━━━━━━━━━━━━━━━━━━*/
int NextAdjVex_M(MGraph G, VertexType_M v, VertexType_M w);

/*━━━━━━━━━━┓
┃(12)插入顶点v到图。 ┃
┗━━━━━━━━━━*/
Status InsertVex_M(MGraph *G, VertexType_M v);

/*━━━━━━━━━━━┓
┃(13)从图中删除顶点v。 ┃
┗━━━━━━━━━━━*/
Status DeleteVex_M(MGraph *G, VertexType_M v);

/*━━━━━━━━━━━━━━━━━━━━━━━┓
┃(14)插入弧<v,w>到图,弧的相关信息InfoType可选。┃
┗━━━━━━━━━━━━━━━━━━━━━━━*/
Status InsertArc_M(MGraph *G, VertexType_M v, VertexType_M w, VRType adj, ...);

/*━━━━━━━━━┓
┃(15)删除弧<v,w>。 ┃
┗━━━━━━━━━*/
Status DeleteArc_M(MGraph *G, VertexType_M v, VertexType_M w);

/*━━━━━━━━━━━━━━┓
┃(16)算法7.4：深度优先遍历。 ┃
┗━━━━━━━━━━━━━━*/
void DFSTraverse_M(MGraph G, void(Visit)(VertexType_M));

/*━━━━━━━━━━━━━━━━━━┓
┃(17)算法7.5：深度优先遍历核心函数。 ┃
┗━━━━━━━━━━━━━━━━━━*/
void DFS_M(MGraph G, int v);

/*━━━━━━━━━━━━━━┓
┃(18)算法7.6：广度优先遍历。 ┃
┗━━━━━━━━━━━━━━*/
void BFSTraverse_M(MGraph G, void(Visit)(VertexType_M));

/*━━━━━━━━━┓
┃(19)输出图（表）。┃
┗━━━━━━━━━*/
void OutputMGraph(MGraph G);

/*━━━━━━━━━━━┓
┃(20)录入弧的相关信息。┃
┗━━━━━━━━━━━*/
void Input(FILE *fp, InfoType *info);


/*════╗
║ 算法7.1║
╚════*/
Status CreateGraph_M(FILE *fp, MGraph *G) {
    Scanf(fp, "%d", &((*G).kind));

    switch ((*G).kind)                                //随机创建有向图、网或无向图网的一种。
    {
        case DG:
            return CreateDG_M(fp, G);
        case DN:
            return CreateDN_M(fp, G);
        case UDG:
            return CreateUDG_M(fp, G);
        case UDN:
            return CreateUDN_M(fp, G);
        default:
            return ERROR;
    }
}

Status CreateDG_M(FILE *fp, MGraph *G) {
    int i, j, k;
    VertexType_M v1, v2;
    char tmp;

    Scanf(fp, "%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
    Scanf(fp, "%c", &tmp);                        //跳过换行符

    for (i = 1; i <= (*G).vexnum; i++)
        Scanf(fp, "%c", &((*G).vexs[i]));
    Scanf(fp, "%c", &tmp);                        //跳过换行符

    for (i = 1; i <= (*G).vexnum; i++)                //初始化邻接矩阵
    {
        for (j = 1; j <= (*G).vexnum; j++)
            (*G).arcs[i][j].adj = 0;
    }

    for (k = 1; k <= (*G).arcnum; k++) {
        Scanf(fp, "%c%c", &v1, &v2);

        i = LocateVex_M(*G, v1);
        j = LocateVex_M(*G, v2);

        if (!i || !j)
            return ERROR;

        (*G).arcs[i][j].adj = 1;
        if ((*G).IncInfo == 1)                        //若有弧的其他信息，则录入
            Input(fp, &((*G).arcs[i][j].info));
    }

    return OK;
}

Status CreateDN_M(FILE *fp, MGraph *G) {
    int i, j, k;
    VertexType_M v1, v2;
    VRType w;
    char tmp;

    Scanf(fp, "%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
    Scanf(fp, "%c", &tmp);                        //跳过换行符

    for (i = 1; i <= (*G).vexnum; i++)
        Scanf(fp, "%c", &((*G).vexs[i]));
    Scanf(fp, "%c", &tmp);                        //跳过换行符

    for (i = 1; i <= (*G).vexnum; i++)                    //初始化邻接矩阵
    {
        for (j = 1; j <= (*G).vexnum; j++)
            (*G).arcs[i][j].adj = INFINITY;
    }

    for (k = 1; k <= (*G).arcnum; k++) {
        Scanf(fp, "%c%c%d", &v1, &v2, &w);

        i = LocateVex_M(*G, v1);
        j = LocateVex_M(*G, v2);

        if (!i || !j)
            return ERROR;

        (*G).arcs[i][j].adj = w;
        if ((*G).IncInfo == 1)                            //若有弧的其他信息，则录入
            Input(fp, &((*G).arcs[i][j].info));
    }

    return OK;
}

Status CreateUDG_M(FILE *fp, MGraph *G) {
    int i, j, k;
    VertexType_M v1, v2;
    char tmp;

    Scanf(fp, "%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
    Scanf(fp, "%c", &tmp);                            //跳过换行符

    for (i = 1; i <= (*G).vexnum; i++)
        Scanf(fp, "%c", &((*G).vexs[i]));
    Scanf(fp, "%c", &tmp);                            //跳过换行符

    for (i = 1; i <= (*G).vexnum; i++)                    //初始化邻接矩阵
    {
        for (j = 1; j <= (*G).vexnum; j++)
            (*G).arcs[i][j].adj = 0;
    }

    for (k = 1; k <= (*G).arcnum; k++) {
        Scanf(fp, "%c%c", &v1, &v2);

        i = LocateVex_M(*G, v1);
        j = LocateVex_M(*G, v2);

        if (!i || !j)
            return ERROR;

        (*G).arcs[i][j].adj = 1;
        if ((*G).IncInfo == 1)                            //若有弧的其他信息，则录入
            Input(fp, &((*G).arcs[i][j].info));

        (*G).arcs[j][i] = (*G).arcs[i][j];            //填充对称点
    }

    return OK;
}

/*════╗
║ 算法7.2║
╚════*/
Status CreateUDN_M(FILE *fp, MGraph *G) {
    int i, j, k;
    VertexType_M v1, v2;
    VRType w;
    char tmp;

    Scanf(fp, "%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
    Scanf(fp, "%c", &tmp);                            //跳过换行符

    for (i = 1; i <= (*G).vexnum; i++)
        Scanf(fp, "%c", &((*G).vexs[i]));
    Scanf(fp, "%c", &tmp);                            //跳过换行符

    for (i = 1; i <= (*G).vexnum; i++)                    //初始化邻接矩阵
    {
        for (j = 1; j <= (*G).vexnum; j++)
            (*G).arcs[i][j].adj = INFINITY;
    }

    for (k = 1; k <= (*G).arcnum; k++) {
        Scanf(fp, "%c%c%d", &v1, &v2, &w);

        i = LocateVex_M(*G, v1);
        j = LocateVex_M(*G, v2);

        if (!i || !j)
            return ERROR;

        (*G).arcs[i][j].adj = w;
        if ((*G).IncInfo == 1)                            //若有弧的其他信息，则录入
            Input(fp, &((*G).arcs[i][j].info));

        (*G).arcs[j][i] = (*G).arcs[i][j];            //填充对称点
    }

    return OK;
}

void ClearGraph_M(MGraph *G) {
    (*G).vexnum = 0;
    (*G).arcnum = 0;
    (*G).IncInfo = 0;
}

int LocateVex_M(MGraph G, VertexType_M u) {
    int i;

    for (i = 1; i <= G.vexnum; i++) {
        if (G.vexs[i] == u)
            return i;
    }

    return 0;
}

VertexType_M GetVex_M(MGraph G, int order) {
    if (order >= 1 && order <= G.vexnum)
        return G.vexs[order];
    else
        return '\0';
}

Status PutVex_M(MGraph *G, VertexType_M v, VertexType_M value) {
    int k;

    k = LocateVex_M(*G, v);

    if (k) {
        (*G).vexs[k] = value;
        return OK;
    } else
        return ERROR;
}

int FirstAdjVex_M(MGraph G, VertexType_M v) {
    int k, j, t;

    k = LocateVex_M(G, v);

    if (k) {
        if (G.kind % 2)                //网
            t = INFINITY;
        else                        //图
            t = 0;

        for (j = 1; j <= G.vexnum; j++) {
            if (G.arcs[k][j].adj != t)
                return j;
        }
    }

    return 0;
}

int NextAdjVex_M(MGraph G, VertexType_M v, VertexType_M w) {
    int k1, k2, j, t;

    k1 = LocateVex_M(G, v);
    k2 = LocateVex_M(G, w);

    if (k1 && k2) {
        if (G.kind % 2)                //网
            t = INFINITY;
        else                        //图
            t = 0;

        for (j = k2 + 1; j <= G.vexnum; j++) {
            if (G.arcs[k1][j].adj != t)
                return j;
        }
    }

    return 0;
}

Status InsertVex_M(MGraph *G, VertexType_M v) {
    int i, k, t;

    if ((*G).vexnum == MAX_VERTEX_NUM)
        return ERROR;                //顶点数已满

    if ((*G).kind % 2)                    //网
        t = INFINITY;
    else                            //图
        t = 0;

    k = (*G).vexnum + 1;
    (*G).vexs[k] = v;

    for (i = 1; i <= k; i++) {
        (*G).arcs[i][k].adj = t;
        (*G).arcs[k][i].adj = t;
    }

    (*G).vexnum++;

    return OK;
}

Status DeleteVex_M(MGraph *G, VertexType_M v) {
    int i, j, k, t;

    // 待删除定点序号
    k = LocateVex_M(*G, v);

    if (!k)
        return ERROR;

    if ((*G).kind % 2)                            //网
        t = INFINITY;
    else                                    //图
        t = 0;

    for (i = 1; i <= k; i++) {
        if ((*G).arcs[k][i].adj != t)            //计算新的弧数
            (*G).arcnum--;

        if ((*G).kind == DG || (*G).kind == DN)    //有向
        {
            if ((*G).arcs[i][k].adj != t)
                (*G).arcnum--;
        }
    }

    /* 从邻接矩阵中删除该顶点所在的列与行 */

    // 列往前覆盖
    for (i = 1; i <= (*G).vexnum; i++) {
        for (j = k + 1; j <= (*G).vexnum; j++)
            (*G).arcs[i][j - 1] = (*G).arcs[i][j];
    }

    // 行往上覆盖
    for (i = k + 1; i <= (*G).vexnum; i++) {
        for (j = 1; j <= (*G).vexnum - 1; j++)
            (*G).arcs[i - 1][j] = (*G).arcs[i][j];
    }

    // 从顶点数组中删除该顶点的信息
    for (i = k; i < (*G).vexnum; i++) {
        (*G).vexs[i] = (*G).vexs[i + 1];
    }

    // 顶点数减一
    (*G).vexnum--;

    return OK;
}

Status InsertArc_M(MGraph *G, VertexType_M v, VertexType_M w, VRType adj, ...) {
    int k1, k2;

    k1 = LocateVex_M(*G, v);
    k2 = LocateVex_M(*G, w);

    if (!k1 || !k2)
        return ERROR;

    (*G).arcs[k1][k2].adj = adj;                    //弧的信息（相邻？权值？）

    va_list ap;                                        //存在弧的其他信息，则录入
    va_start(ap, adj);
    (*G).arcs[k1][k2].info = va_arg(ap, InfoType);    //结构可直接复制
    va_end(ap);

    if ((*G).kind == UDG || (*G).kind == UDN)    //无向
        (*G).arcs[k2][k1] = (*G).arcs[k1][k2];

    (*G).arcnum++;                            //弧数增一

    return OK;
}

Status DeleteArc_M(MGraph *G, VertexType_M v, VertexType_M w) {
    int k1, k2;

    k1 = LocateVex_M(*G, v);
    k2 = LocateVex_M(*G, w);

    if (!k1 || !k2)
        return ERROR;

    if ((*G).kind % 2)                            //网
        (*G).arcs[k1][k2].adj = INFINITY;
    else                                    //图
        (*G).arcs[k1][k2].adj = 0;

    if ((*G).kind == UDG || (*G).kind == UDN)    //无向
        (*G).arcs[k2][k1] = (*G).arcs[k1][k2];

    (*G).arcnum--;                            //弧数减一

    return OK;
}

/*════╗
║ 算法7.4║
╚════*/
void DFSTraverse_M(MGraph G, void(Visit)(VertexType_M)) {
    int v;

    VisitFunc = Visit;

    for (v = 1; v <= G.vexnum; v++)
        visited[v] = FALSE;                    //初始化为未访问

    for (v = 1; v <= G.vexnum; v++) {
        if (!visited[v])                        //未访问
            DFS_M(G, v);
    }
}

/*════╗
║ 算法7.5║
╚════*/
void DFS_M(MGraph G, int v) {
    int w;

    visited[v] = TRUE;

    VisitFunc(G.vexs[v]);

    for (w = FirstAdjVex_M(G, G.vexs[v]); w; w = NextAdjVex_M(G, G.vexs[v], G.vexs[w])) {
        if (!visited[w])
            DFS_M(G, w);
    }
}

/*════╗
║ 算法7.6║
╚════*/
void BFSTraverse_M(MGraph G, void(Visit)(VertexType_M)) {
    int v, w;
    LinkQueue Q;
    QElemType_L e;

    for (v = 1; v <= G.vexnum; v++)
        visited[v] = FALSE;                    //初始化为未访问

    InitQueue_L(&Q);

    for (v = 1; v <= G.vexnum; v++) {
        if (!visited[v]) {
            visited[v] = TRUE;
            Visit(G.vexs[v]);
            EnQueue_L(&Q, v);
            while (!QueueEmpty_L(Q)) {
                DeQueue_L(&Q, &e);
                for (w = FirstAdjVex_M(G, G.vexs[e]); w; w = NextAdjVex_M(G, G.vexs[e], G.vexs[w])) {
                    if (!visited[w]) {
                        visited[w] = TRUE;
                        Visit(G.vexs[w]);
                        EnQueue_L(&Q, w);
                    }
                }
            }
        }
    }
}

void OutputMGraph(MGraph G) {
    int i, j;

    if (!G.vexnum && !G.arcnum)
        printf("空图（表）！\n");
    else {
        printf("  ");
        for (i = 1; i <= G.vexnum; i++)
            printf("%2c ", G.vexs[i]);
        printf("\n");

        for (i = 1; i <= G.vexnum; i++) {
            printf("%c ", G.vexs[i]);
            for (j = 1; j <= G.vexnum; j++) {
                if (G.arcs[i][j].adj == INFINITY)
                    printf("∞ ");
                else
                    printf("%2d ", G.arcs[i][j]);
            }

            printf("\n");
        }
    }
}

void Input(FILE *fp, InfoType *info) {
    //录入弧的信息，本文档涉及到的弧默认无其他信息
}

#endif //DATA_STRUCTURE_MGRAPH_H
