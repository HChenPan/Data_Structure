//
//文件夹: 07 Graph\09 TopologicalSort
//文件名: TopologicalSort
//内　容：有向图拓扑排序相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 02:42
//Version 1.0
//

#ifndef DATA_STRUCTURE_TOPOLOGICALSORT_H
#define DATA_STRUCTURE_TOPOLOGICALSORT_H

#include <stdio.h>
#include "../../01 Introduction/Status.h"                                //**01 Introduction**//
#include "../../03 Stack_Queue/01 SequenceStack/SequenceStack.h"    //**03 Stack_Queue**//
#include "../02 ALGraph/ALGraph.h"                                //**07 Graph**//

/* 有向图拓扑排序函数列表 */
/**
(01)算法7.12：求有向图拓扑排序。
**/
Status TopologicalSort(ALGraph G, int Topo[]);

/**
(02)对有向图各顶点求入度。
**/
void FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM + 1]);


/**
算法7.12
**/
Status TopologicalSort(ALGraph G, int Topo[])            //数组Topo存储拓扑序列
{
    SqStack S;
    ArcNode *p;
    int i, k, count, indegree[MAX_VERTEX_NUM + 1];

    FindInDegree(G, indegree);                            //对各顶点求入度
    InitStack_Sq(&S);                                    //初始化栈

    for (i = 1; i <= G.vexnum; i++)                            //建立入度为0的顶点栈
    {
        if (!indegree[i])
            Push_Sq(&S, i);                                //入度为0者进栈
    }

    count = 0;                                            //对输出顶点计数

    while (!StackEmpty_Sq(S)) {
        Pop_Sq(&S, &i);
        count++;                                        //与教材写法略有出入
        Topo[count] = i;                                //不直接输出，而是暂存于数组中

        for (p = G.vertices[i].firstarc; p; p = p->nextarc) {
            k = p->adjvex;                                //对i号顶点的每个邻接点的入度减一
            if (!(--indegree[k]))
                Push_Sq(&S, k);
        }
    }

    if (count < G.vexnum)
        return ERROR;
    else
        return OK;
}

void FindInDegree(ALGraph G, int indegree[MAX_VERTEX_NUM + 1]) {
    int i;
    ArcNode *p;

    for (i = 1; i <= G.vexnum; i++)
        indegree[i] = 0;                                //初始化入度数组

    for (i = 1; i <= G.vexnum; i++) {
        p = G.vertices[i].firstarc;
        while (p) {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
}

#endif //DATA_STRUCTURE_TOPOLOGICALSORT_H
