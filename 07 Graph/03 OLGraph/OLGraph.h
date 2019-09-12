//
//文件夹: 07 Graph/03 OLGraph
//文件名: OLGraph
//内　容：有向图（十字链表）相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 02:32
//Version 1.0
//

#ifndef DATA_STRUCTURE_OLGRAPH_H
#define DATA_STRUCTURE_OLGRAPH_H

#include <stdio.h>
#include <stdlib.h>                                        //提供malloc、realloc、free、exit原型
#include <stdarg.h>                                            //提供宏va_list、va_start、va_arg、va_end
#include "../../01 Introduction/Status.h"                            //**01 Introduction**//
#include "../../01 Introduction/Scanf.h"                            //**01 Introduction**//
#include "../../03 Stack_Queue/07 LinkQueue/LinkQueue.h"    //**03 Stack_Queue**//

/* 宏定义 */
#define MAX_VERTEX_NUM 20                        //最大顶点个数

/* 有向图（十字链表）类型定义 */
typedef struct                                    //弧相关信息
{
    //本文档不设弧信息
} InfoType;
typedef struct ArcBox                            //弧结点
{
    int tailvex, headvex;                        //该弧的尾和头顶点的位置
    struct ArcBox *hlink, *tLink;                //分别为弧头相同和弧尾相同的弧的链域
    InfoType info;                                //该弧相关信息
} ArcBox;
typedef char VertexType_OL;                        //有向图顶点类型
typedef struct VexNode {
    VertexType_OL data;
    ArcBox *firstin, *firstout;                    //分别指向该顶点第一条入弧和出弧
} VexNode;
typedef struct                                    //有向图（十字链表）存储结构
{
    VexNode xlist[MAX_VERTEX_NUM + 1];            //表头向量
    int vexnum, arcnum;                            //有向图当前顶点数和弧数
    int IncInfo;                                //IncInfo为0则各弧不含其它信息
} OLGraph;

/* 全局变量 */
Status visited[MAX_VERTEX_NUM + 1];        //标志数组
void (*VisitFunc)(VertexType_OL e);        //函数指针变量

/* 有向图（十字链表）函数列表 */
/*━━━━━━━━━━━━━┓
┃(01)算法7.3：构造有向图。 ┃
┗━━━━━━━━━━━━━*/
Status CreateDG_OL(FILE *fp, OLGraph *G);


/*━━━━━━┓
┃(02)清空图。┃
┗━━━━━━*/
void ClearGraph_OL(OLGraph *G);


/*━━━━━━━━━━━┓
┃(03)寻找顶点u的位置。 ┃
┗━━━━━━━━━━━*/
int LocateVex_OL(OLGraph G, VertexType_OL u);


/*━━━━━━━━━━━━┓
┃(04)返回第v个结点的值。 ┃
┗━━━━━━━━━━━━*/
VertexType_OL GetVex_M(OLGraph G, int order);


/*━━━━━━━━━━━┓
┃(05)对顶点v赋值value。┃
┗━━━━━━━━━━━*/
Status PutVex_OL(OLGraph *G, VertexType_OL v, VertexType_OL value);


/*━━━━━━━━━━━━━━━━┓
┃(06)返回v的第一个邻接顶点序号。 ┃
┗━━━━━━━━━━━━━━━━*/
int FirstAdjVex_OL(OLGraph G, VertexType_OL v);


/*━━━━━━━━━━━━━━━━━━━┓
┃(07)返回v相对于w的下一个邻接顶点序号。┃
┗━━━━━━━━━━━━━━━━━━━*/
int NextAdjVex_OL(OLGraph G, VertexType_OL v, VertexType_OL w);


/*━━━━━━━━━━┓
┃(08)插入顶点v到图。 ┃
┗━━━━━━━━━━*/
Status InsertVex_OL(OLGraph *G, VertexType_OL v);


/*━━━━━━━━━━━┓
┃(09)从图中删除顶点v。 ┃
┗━━━━━━━━━━━*/
Status DeleteVex_OL(OLGraph *G, VertexType_OL v);


/*━━━━━━━━━━━┓
┃(10)插入弧<v,w>到图。 ┃
┗━━━━━━━━━━━*/
Status InsertArc_OL(OLGraph *G, VertexType_OL v, VertexType_OL w, ...);


/*━━━━━━━━━┓
┃(11)删除弧<v,w>。 ┃
┗━━━━━━━━━*/
Status DeleteArc_OL(OLGraph *G, VertexType_OL v, VertexType_OL w);


/*━━━━━━━━━┓
┃(12)深度优先遍历。┃
┗━━━━━━━━━*/
void DFSTraverse_OL(OLGraph G, void (Visit)(VertexType_OL));


/*━━━━━━━━━━━━━┓
┃(13)深度优先遍历核心函数。┃
┗━━━━━━━━━━━━━*/
void DFS_OL(OLGraph G, int v);


/*━━━━━━━━━┓
┃(14)广度优先遍历。┃
┗━━━━━━━━━*/
void BFSTraverse_OL(OLGraph G, void (Visit)(VertexType_OL));


/*━━━━━━┓
┃(15)输出图。┃
┗━━━━━━*/
void OutputOLGraph(OLGraph G);


/*━━━━━━━━━━━┓
┃(16)录入弧的相关信息。┃
┗━━━━━━━━━━━*/
void Input(FILE *fp, InfoType *info);


/*════╗
║ 算法7.3║
╚════*/
Status CreateDG_OL(FILE *fp, OLGraph *G) {
    int i, j, k;
    VertexType_OL v1, v2;
    char tmp;
    ArcBox *p;

    Scanf(fp, "%d%d%d", &((*G).vexnum), &((*G).arcnum), &((*G).IncInfo));
    Scanf(fp, "%c", &tmp);                            //跳过换行符

    for (i = 1; i <= (*G).vexnum; i++)                    //构造表头向量
    {
        Scanf(fp, "%c", &((*G).xlist[i].data));        //输入顶点值
        (*G).xlist[i].firstin = NULL;                //初始化指针
        (*G).xlist[i].firstout = NULL;
    }
    Scanf(fp, "%c", &tmp);                            //跳过换行符

    for (k = 1; k <= (*G).arcnum; k++)                    //输入各弧并构造十字链表
    {
        Scanf(fp, "%c%c", &v1, &v2);                //输入一条弧的起始点和终点

        i = LocateVex_OL(*G, v1);                    //确定v1和v2在G中位置
        j = LocateVex_OL(*G, v2);

        if (!i || !j)
            return ERROR;

        p = (ArcBox *) malloc(sizeof(ArcBox));        //假定有足够空间
        if (!p)
            exit(OVERFLOW);

        p->tailvex = i;                                //对弧结点和顶点结点赋值
        p->headvex = j;

        p->hlink = (*G).xlist[j].firstin;
        (*G).xlist[j].firstin = p;

        p->tLink = (*G).xlist[i].firstout;
        (*G).xlist[i].firstout = p;

        if ((*G).IncInfo == 1)                            //表示有弧的其他信息，录入
            Input(fp, &(p->info));
    }

    return OK;
}

void ClearGraph_OL(OLGraph *G) {
    int i;
    ArcBox *p, *q;

    for (i = 1; i <= (*G).vexnum; i++) {
        p = (*G).xlist[i].firstout;
        while (p) {
            q = p;
            p = p->tLink;
            free(q);
        }
    }

    (*G).vexnum = 0;
    (*G).arcnum = 0;
}

int LocateVex_OL(OLGraph G, VertexType_OL u) {
    int i;

    for (i = 1; i <= G.vexnum; i++) {
        if (G.xlist[i].data == u)
            return i;
    }

    return 0;
}

VertexType_OL GetVex_OL(OLGraph G, int order) {
    if (order >= 1 && order <= G.vexnum)
        return G.xlist[order].data;
    else
        return '\0';
}

Status PutVex_OL(OLGraph *G, VertexType_OL v, VertexType_OL value) {
    int k;

    k = LocateVex_OL(*G, v);

    if (k) {
        (*G).xlist[k].data = value;
        return OK;
    } else
        return ERROR;
}

int FirstAdjVex_OL(OLGraph G, VertexType_OL v) {
    int k;

    k = LocateVex_OL(G, v);

    if (k) {
        if (G.xlist[k].firstout)
            return G.xlist[k].firstout->headvex;
    }

    return 0;
}

int NextAdjVex_OL(OLGraph G, VertexType_OL v, VertexType_OL w) {
    int k1, k2;
    ArcBox *p, *q;

    k1 = LocateVex_OL(G, v);
    k2 = LocateVex_OL(G, w);

    if (k1 && k2) {
        if (G.xlist[k1].firstout && G.xlist[k1].firstout->tLink) {
            p = G.xlist[k1].firstout;
            q = p->tLink;

            while (p->headvex != k2 && q->tLink) {
                p = q;
                q = q->tLink;
            }

            if (p->headvex == k2)
                return q->headvex;
        }
    }

    return 0;
}

Status InsertVex_OL(OLGraph *G, VertexType_OL v) {
    int i, k, t;

    if ((*G).vexnum == MAX_VERTEX_NUM)
        return ERROR;                //顶点数已满

    (*G).vexnum++;

    (*G).xlist[(*G).vexnum].data = v;
    (*G).xlist[(*G).vexnum].firstin = NULL;
    (*G).xlist[(*G).vexnum].firstout = NULL;

    return OK;
}

Status DeleteVex_OL(OLGraph *G, VertexType_OL v) {
    int i, k;
    ArcBox *p;

    k = LocateVex_OL(*G, v);

    if (!k)
        return ERROR;

    while ((*G).xlist[k].firstout)                        //删除从顶点v出发的弧
    {
        p = (*G).xlist[k].firstout;
        DeleteArc_OL(G, (*G).xlist[p->tailvex].data, (*G).xlist[p->headvex].data);
    }

    while ((*G).xlist[k].firstin)                        //删除指向顶点v的弧（适用于有向图或有向网）
    {
        p = (*G).xlist[k].firstin;
        DeleteArc_OL(G, (*G).xlist[p->tailvex].data, (*G).xlist[p->headvex].data);
    }

    for (i = k + 1; i <= (*G).vexnum; i++)                        //重新安排各顶点位置
    {
        (*G).xlist[i - 1].data = (*G).xlist[i].data;
        (*G).xlist[i - 1].firstin = (*G).xlist[i].firstin;
        (*G).xlist[i - 1].firstout = (*G).xlist[i].firstout;
    }

    (*G).vexnum--;

    return OK;
}

Status InsertArc_OL(OLGraph *G, VertexType_OL v, VertexType_OL w, ...) {
    int k1, k2;
    ArcBox *p, *q, *r;

    k1 = LocateVex_OL(*G, v);
    k2 = LocateVex_OL(*G, w);

    if (!k1 || !k2)
        return ERROR;

    p = (ArcBox *) malloc(sizeof(ArcBox));
    if (!p)
        exit(OVERFLOW);
    p->tailvex = k1;
    p->headvex = k2;

    va_list ap;                                            //存在弧信息，则录入
    va_start(ap, w);
    p->info = va_arg(ap, InfoType);                        //结构可直接复制
    va_end(ap);

    q = (*G).xlist[k1].firstout;
    if (!q || q->headvex > p->headvex) {
        p->tLink = q;
        (*G).xlist[k1].firstout = p;
    } else {
        while (q->tLink && q->tLink->headvex < p->headvex)
            q = q->tLink;

        p->tLink = q->tLink;
        q->tLink = p;
    }


    r = (*G).xlist[k2].firstin;
    if (!r || r->tailvex > p->tailvex) {
        p->hlink = r;
        (*G).xlist[k2].firstin = p;
    } else {
        while (r->hlink && r->hlink->tailvex < p->tailvex)
            r = r->hlink;

        p->hlink = r->hlink;
        r->hlink = p;
    }

    (*G).arcnum++;                                    //弧数增一

    return OK;
}

Status DeleteArc_OL(OLGraph *G, VertexType_OL v, VertexType_OL w) {
    int k1, k2;
    ArcBox *p, *q, *r;

    k1 = LocateVex_OL(*G, v);
    k2 = LocateVex_OL(*G, w);

    if (!k1 || !k2)
        return ERROR;

    p = (*G).xlist[k1].firstout;
    if (p && p->headvex == k2)
        (*G).xlist[k1].firstout = p->tLink;
    else {
        q = p;
        p = p->tLink;
        while (p && p->headvex != k2) {
            q = p;
            p = p->tLink;
        }

        if (p)
            q->tLink = p->tLink;
        else                                        //欲删除的弧不存在
            return ERROR;
    }

    p = (*G).xlist[k2].firstin;
    if (p->tailvex == k1)
        (*G).xlist[k2].firstin = p->hlink;
    else {
        r = p;
        p = p->hlink;
        while (p->tailvex != k1) {
            r = p;
            p = p->hlink;
        }

        r->hlink = p->hlink;
    }

    free(p);

    (*G).arcnum--;                            //弧数减一

    return OK;
}

void DFSTraverse_OL(OLGraph G, void (Visit)(VertexType_OL)) {
    int v;

    VisitFunc = Visit;

    for (v = 1; v <= G.vexnum; v++)
        visited[v] = FALSE;                    //初始化为未访问

    for (v = 1; v <= G.vexnum; v++) {
        if (!visited[v])                        //未访问
            DFS_OL(G, v);
    }
}

void DFS_OL(OLGraph G, int v) {
    int w;

    visited[v] = TRUE;

    VisitFunc(G.xlist[v].data);

    for (w = FirstAdjVex_OL(G, G.xlist[v].data); w; w = NextAdjVex_OL(G, G.xlist[v].data, G.xlist[w].data)) {
        if (!visited[w])
            DFS_OL(G, w);
    }
}

void BFSTraverse_OL(OLGraph G, void (Visit)(VertexType_OL)) {
    int v, w;
    LinkQueue Q;
    QElemType_L e;

    for (v = 1; v <= G.vexnum; v++)
        visited[v] = FALSE;                    //初始化为未访问

    InitQueue_L(&Q);

    for (v = 1; v <= G.vexnum; v++) {
        if (!visited[v]) {
            visited[v] = TRUE;
            Visit(G.xlist[v].data);
            EnQueue_L(&Q, v);
            while (!QueueEmpty_L(Q)) {
                DeQueue_L(&Q, &e);
                for (w = FirstAdjVex_OL(G, G.xlist[e].data); w; w = NextAdjVex_OL(G, G.xlist[e].data,
                                                                                  G.xlist[w].data)) {
                    if (!visited[w]) {
                        visited[w] = TRUE;
                        Visit(G.xlist[w].data);
                        EnQueue_L(&Q, w);
                    }
                }
            }
        }
    }
}

void OutputOLGraph(OLGraph G) {
    int i, j;
    ArcBox *p;

    if (!G.vexnum && !G.arcnum)
        printf("空图（表）！\n");
    else {
        for (i = 1; i <= G.vexnum; i++) {
            printf("%c→ ", G.xlist[i].data);
            p = G.xlist[i].firstout;
            j = 1;
            while (p) {
                while (p->headvex != j) {
                    printf("      ");
                    j++;
                }
                printf("(%-c %c) ", G.xlist[p->tailvex].data, G.xlist[p->headvex].data);
                p = p->tLink;
                j++;
            }
            printf("\n");
        }
    }
}

void Input(FILE *fp, InfoType *info) {
    //录入弧的信息，本文档涉及到的弧默认无其他信息
}

#endif //DATA_STRUCTURE_OLGRAPH_H
