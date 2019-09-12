//
//文件夹: 09 Search/06 BinarySortTree
//文件名: BinarySortTree
//内　容：二叉排序树相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 03:21
//Version 1.0
//

#ifndef DATA_STRUCTURE_BINARYSORTTREE_H
#define DATA_STRUCTURE_BINARYSORTTREE_H

#include <stdlib.h>
#include "../00 Base/Base.h"                //**09 Search**//

/* 宏函数 */
#define EQ(a, b) ((a)==(b))
#define LT(a, b) ((a) < (b))

/* 类型定义 */
typedef ElemType_Search BSTElemType;        //二叉排序树元素类型
typedef struct BSTNode                        //二叉排序树存储表示
{
    BSTElemType data;
    struct BSTNode *lchild;
    struct BSTNode *rchild;

    union                                    //匿名联合体，仅在第9章习题测试时使用
    {
        int RTag;                            //线索标志
    };
} BSTNode;                                    //二叉排序树结点
typedef BSTNode *BSTree;                    //指向二叉排序树结点的指针

/* 二叉排序树函数列表 */
/*━━━━━━━━━━┓
┃(01)创建二叉排序树。┃
┗━━━━━━━━━━*/
Status CreateBSTree(BSTree *BST, Table T);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(02)算法9.5(a)：查找，返回指向key的指针，若不存在返回MULL。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
BSTree SearchBST_1(BSTree BST, KeyType key);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(03)算法9.5(b)：查找，若不存在key，则插入到正确的位置。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
Status SearchBST_2(BSTree BST, KeyType key, BSTree f, BSTree *p);

/*━━━━━━━━━━━━━━━━┓
┃(04)算法9.6：插入e到二叉排序树。┃
┗━━━━━━━━━━━━━━━━*/
Status InsertBST(BSTree *BST, BSTElemType e);

/*━━━━━━━━━━━━━━━━━━━━┓
┃(05)中序遍历二叉排序树，生成关键字序列。┃
┗━━━━━━━━━━━━━━━━━━━━*/
void InOrderTraverse_BST(BSTree BST, void(Visit)(ElemType_Search));

/*━━━━━━━━━━┓
┃(06)算法9.7：删除。 ┃
┗━━━━━━━━━━*/
Status DeleteBST(BSTree *BST, KeyType key);

/*━━━━━━━━━━━━━━━┓
┃(07)算法9.8：删除p指向的结点。┃
┗━━━━━━━━━━━━━━━*/
Status Delete(BSTree *p);


Status CreateBSTree(BSTree *BST, Table T) {
    int i;

    *BST = NULL;

    if (T.length) {
        for (i = 1; i <= T.length; i++)
            InsertBST(BST, T.elem[i]);
    }

    return OK;
}

/*═════╗
║算法9.5(a)║
╚═════*/
BSTree SearchBST_1(BSTree BST, KeyType key) {
    if (!BST || EQ(key, BST->data.key))
        return BST;
    else if (LT(key, BST->data.key))
        return SearchBST_1(BST->lchild, key);
    else
        return SearchBST_1(BST->rchild, key);
}

/*═════╗
║算法9.5(b)║
╚═════*/
Status SearchBST_2(BSTree BST, KeyType key, BSTree f, BSTree *p) {//p指向查找路径上最后一个“能”被访问结点，f指向BST的双亲，初始值为NULL
    if (!BST) {
        *p = f;
        return FALSE;
    } else if (EQ(key, BST->data.key)) {
        *p = BST;
        return TRUE;
    } else if (LT(key, BST->data.key))
        return SearchBST_2(BST->lchild, key, BST, p);
    else
        return SearchBST_2(BST->rchild, key, BST, p);
}

/*════╗
║ 算法9.6║
╚════*/
Status InsertBST(BSTree *BST, BSTElemType e) {
    BSTree p, s;

    if (!SearchBST_2(*BST, e.key, NULL, &p))        //查找不成功
    {
        s = (BSTree) malloc(sizeof(BSTNode));
        s->data = e;
        s->lchild = s->rchild = NULL;

        if (!p)                                    //原树为空
            *BST = s;
        else if (LT(e.key, p->data.key))
            p->lchild = s;
        else
            p->rchild = s;

        return TRUE;                            //插入e.key
    } else                                        //查找成功
        return FALSE;
}

void InOrderTraverse_BST(BSTree BST, void(Visit)(ElemType_Search)) {
    if (BST) {
        InOrderTraverse_BST(BST->lchild, Visit);
        Visit(BST->data);
        InOrderTraverse_BST(BST->rchild, Visit);
    }

}

/*════╗
║ 算法9.7║
╚════*/
Status DeleteBST(BSTree *BST, KeyType key) {
    if (!(*BST))                        //不存在与关键字相等的数据元素
        return FALSE;
    else {
        if (EQ(key, (*BST)->data.key))
            return Delete(BST);
        else if (LT(key, (*BST)->data.key))
            return DeleteBST(&(*BST)->lchild, key);
        else
            return DeleteBST(&(*BST)->rchild, key);
    }
}

/*════╗
║ 算法9.8║
╚════*/
Status Delete(BSTree *p) {
    BSTree q, s;

    if (!(*p)->rchild) {
        q = *p;
        *p = (*p)->lchild;
        free(q);
    } else if (!(*p)->lchild) {
        q = *p;
        *p = (*p)->rchild;
        free(q);
    } else {
        q = *p;
        s = (*p)->lchild;

        while (s->rchild)        //寻找p的直接前驱
        {
            q = s;
            s = s->rchild;
        }

        (*p)->data = s->data;    //用p的直接前驱取代p

        if (q != *p)
            q->rchild = s->lchild;
        else
            q->lchild = s->lchild;

        free(s);
    }

    return TRUE;
}

#endif //DATA_STRUCTURE_BINARYSORTTREE_H
