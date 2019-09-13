//
//文件夹: 09 Search/05 NearlyOptimalSearchTree
//文件名: NearlyOptimalSearchTree
//内　容：次优查找树相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 03:21
//Version 1.0
//

#ifndef DATA_STRUCTURE_NEARLYOPTIMALSEARCHTREE_H
#define DATA_STRUCTURE_NEARLYOPTIMALSEARCHTREE_H

#include <stdlib.h>
#include <math.h>
#include "../00 Base/Base.h"                //**09 Search**//
#include "../../06 Tree_BinaryTree/02 BinaryTree/BinaryTree.h"//**▲06 树和二叉树**//

/* 类型定义 */
typedef BiTree SOSTree;

/*全局变量*/
char ch[] = "\0ABCDEFGHI";

/* 静态树表查找函数列表 */
/**
(01)建立累计权值表。
**/
void FindSW(float sw[], Table T);

/**
(02)找出左右累计权值差最小的分界点。
**/
int MinSW(float sw[], int low, int high);

/**
(03)算法9.3：次优查找树构造函数。 
**/
void SecondOptimal(BiTree *BT, ElemType_Search R[], float sw[], int low, int high);

/**
(04)算法9.4：用有序表T构造次优查找树。
**/
Status CreateSOSTree(SOSTree *BT, Table T);

/**
(5)判断关键字key是否在次优查找树BT中。
**/
Status Search_SOST(SOSTree BT, KeyType key);


void FindSW(float sw[], Table T) {
    int i;

    sw[0] = 0.0;

    for (i = 1; i <= T.length; i++)
        sw[i] = sw[i - 1] + T.elem[i].weight;
}

int MinSW(float sw[], int low, int high) {
    int i, j;
    float min, tmp, dw;

    dw = sw[high] + sw[low - 1];
    min = fabs(sw[high] - sw[low]);

    for (i = j = low; i <= high; i++) {
        tmp = fabs(dw - sw[i] - sw[i - 1]);

        if (tmp < min) {
            j = i;
            min = tmp;
        }
    }

    return j;
}

/**
 算法9.3
**/
void SecondOptimal(BiTree *BT, ElemType_Search R[], float sw[], int low, int high) {
    int i;

    i = MinSW(sw, low, high);

    *BT = (BiTree) malloc(sizeof(BiTNode));
    (*BT)->data = ch[R[i].key];

    if (i == low)
        (*BT)->lchild = NULL;
    else
        SecondOptimal(&((*BT)->lchild), R, sw, low, i - 1);

    if (i == high)
        (*BT)->rchild = NULL;
    else
        SecondOptimal(&((*BT)->rchild), R, sw, i + 1, high);
}

/**
 算法9.4
**/
Status CreateSOSTree(SOSTree *BT, Table T) {
    float sw[T.length + 1];

    if (T.length == 0)
        *BT = NULL;
    else {
        FindSW(sw, T);
        SecondOptimal(BT, T.elem, sw, 1, T.length);
    }

    return OK;
}

Status Search_SOST(SOSTree BT, KeyType key) {
    if (BT) {
        if (ch[key] == BT->data)
            return OK;
        else if (ch[key] < BT->data)
            return Search_SOST(BT->lchild, key);
        else
            return Search_SOST(BT->rchild, key);
    }

    return FALSE;
}

#endif //DATA_STRUCTURE_NEARLYOPTIMALSEARCHTREE_H
