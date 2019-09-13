//
//文件夹: 07 Graph\08 ArticulationPoint
//文件名: ArticulationPoint
//内　容：无向图关节点相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 02:42
//Version 1.0
//

#ifndef DATA_STRUCTURE_ARTICULATIONPOINT_H
#define DATA_STRUCTURE_ARTICULATIONPOINT_H

#include <stdio.h>
#include "../../01 Introduction/Status.h"                    //**01 Introduction**//
#include "../02 ALGraph/ALGraph.h"                    //**07 Graph**//

/* 全局变量 */
int count;
int low[MAX_VERTEX_NUM + 1];                            //以当前结点为根的树可以直接追溯的最早祖先位置
int node[MAX_VERTEX_NUM + 1];                            //存放关节点，0号单元统计关节点个数

/* 无向图关节点函数列表 */
/**
(01)算法7.10：查找并输出G上全部关节点。 
**/
void FindArticul(ALGraph G);

/**
(02)算法7.11：从第v0个顶点出发深度优先遍历图G，查找并输出所有关节点。 
**/
void DFSArticul(ALGraph G, int v0);

/**
(03)存储先序编号为n的关节点到node中。 
**/
Status StorageAPoint(int n);

/**
(04)输出G中全部关节点。 
**/
void OutputAPoint(ALGraph G);


/**
算法7.10
**/
void FindArticul(ALGraph G) {
    int i, v;
    ArcNode *p;

    count = 1;
    visited[1] = 1;                                        //设定邻接表上1号顶点为生成树的根（0号单元弃用）

    for (i = 2; i <= G.vexnum; i++)
        visited[i] = 0;                                    //其余顶点尚未访问

    p = G.vertices[1].firstarc;
    v = p->adjvex;

    DFSArticul(G, v);                                    //先遍历根结点最左边的子树

    if (count < G.vexnum)                                    //生成树的根有至少两棵子树
    {
        StorageAPoint(1);

        while (p->nextarc)                                //依次遍历其他子树
        {
            p = p->nextarc;
            v = p->adjvex;

            if (visited[v] == 0)
                DFSArticul(G, v);
        }
    }
}

/**
算法7.11
**/
void DFSArticul(ALGraph G, int v0) {
    int min, w;                                            //min暂存low[]的值
    ArcNode *p;

    visited[v0] = min = ++count;                        //v0是第count个访问的顶点

    for (p = G.vertices[v0].firstarc; p; p = p->nextarc) {
        w = p->adjvex;                                    //w为v0的邻接顶点

        if (visited[w] == 0)                                //w未曾访问，是v0的孩子
        {
            DFSArticul(G, w);                            //返回前求得low[w]

            if (low[w] < min)
                min = low[w];

            if (low[w] >= visited[v0])                        //v0子树可直接追溯的最早祖先不超过自身
                StorageAPoint(v0);
        } else                                            //w已访问，是v0在生成树上的祖先
        {
            if (visited[w] < min)
                min = visited[w];
        }

        low[v0] = min;
    }
}

Status StorageAPoint(int n) {
    int i;

    for (i = 1; i <= node[0]; i++) {
        if (node[i] == n)                                    //该关节点已存储过
            return ERROR;
    }

    node[0]++;
    node[node[0]] = n;

    return OK;
}

void OutputAPoint(ALGraph G) {
    int i;

    for (i = 1; i <= node[0]; i++)
        printf("第 %2d 个找到的关节点 %c，先序编号为 %2d\n", i, G.vertices[node[i]].data, node[i]);
}

#endif //DATA_STRUCTURE_ARTICULATIONPOINT_H
