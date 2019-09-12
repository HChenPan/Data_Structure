//
//文件夹: 07 Graph/05 SpanningTree
//文件名: SpanningTree
//内　容：无向图生成树相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 02:41
//Version 1.0
//

#ifndef DATA_STRUCTURE_SPANNINGTREE_H
#define DATA_STRUCTURE_SPANNINGTREE_H

#include <stdlib.h>                                            //提供malloc、realloc、free、exit原型
#include "../01 MGraph/MGraph.h"                                        //**07 Graph**//
#include "../../06 Tree_BinaryTree/07 ChildSiblingTree/ChildSiblingTree.h"    //**▲06 树和二叉树**//

/* 无向图生成树函数列表 */
/*━━━━━━━━━━━━━━━━━━━━┓
┃(01)算法7.7：创建无向图的生成树（森林） ┃
┗━━━━━━━━━━━━━━━━━━━━*/
void DFSForest(MGraph G, CSTree *T);

/*━━━━━━━━━━━━━━━━━━━┓
┃(02)算法7.8：生成结点v起始的树（森林）┃
┗━━━━━━━━━━━━━━━━━━━*/
void DFSTree(MGraph G, int v, CSTree *T);


/*════╗
║ 算法7.7║
╚════*/
void DFSForest(MGraph G, CSTree *T) {
    int v;
    CSTree p, q;

    InitTree_CS(T);

    for (v = 1; v <= G.vexnum; v++)
        visited[v] = FALSE;

    for (v = 1; v <= G.vexnum; v++) {
        if (!visited[v])                            //第v顶点为新的生成树的根结点
        {
            p = (CSTree) malloc(sizeof(CSNode));    //分配根结点
            if (!p)
                exit(OVERFLOW);
            p->data = GetVex_M(G, v);
            p->firstchild = p->nextsibling = NULL;

            if (!(*T))                            //是第一棵生成树的根
                *T = p;
            else                                //是其他生成树的根（前一棵树根的兄弟）
                q->nextsibling = p;

            q = p;                                //q指示当前生成树的根
            DFSTree(G, v, &p);                    //建立以p为根的生成树
        }
    }
}

/*════╗
║ 算法7.8║
╚════*/
void DFSTree(MGraph G, int v, CSTree *T) {
    Status first;
    int w;
    CSTree p, q;

    visited[v] = TRUE;
    first = TRUE;

    for (w = FirstAdjVex_M(G, G.vexs[v]); w; w = NextAdjVex_M(G, G.vexs[v], G.vexs[w])) {
        if (!visited[w]) {
            p = (CSTree) malloc(sizeof(CSNode));        //分配孩子结点
            if (!p)
                exit(OVERFLOW);
            p->data = GetVex_M(G, w);
            p->firstchild = p->nextsibling = NULL;

            if (first) {
                (*T)->firstchild = p;
                first = FALSE;
            } else
                q->nextsibling = p;

            q = p;
            DFSTree(G, w, &q);
        }
    }
}

#endif //DATA_STRUCTURE_SPANNINGTREE_H
