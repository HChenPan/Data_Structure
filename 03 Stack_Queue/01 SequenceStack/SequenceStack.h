//
//文件夹: 03 Stack_Queue/01 SequenceStack
//文件名: SequenceStack
//内　容：顺序栈相关操作列表
//Author Huangcp
//Date 2019/9/10 下午 10:52
//Version 1.0
//

#ifndef DATA_STRUCTURE_SEQUENCESTACK_H
#define DATA_STRUCTURE_SEQUENCESTACK_H

#include <stdio.h>
#include <stdlib.h>                        //提供malloc、realloc、free、exit原型
#include "../../01 Introduction/Status.h"        //**▲01 绪论**//

/* 宏定义 */
#define STACK_INIT_SIZE    100                //顺序栈存储空间的初始分配量
#define STACKINCREMENT    10                //顺序栈存储空间的分配增量

/* 顺序栈类型定义 */
/*在迷宫、表达式、二叉树二叉链表、孩子兄弟树等算法中，此类型需要重新定义*/
#if !defined DATA_STRUCTURE_MAZE_H				&& \
    !defined DATA_STRUCTURE_EXPRESSION_H		&& \
    !defined DATA_STRUCTURE_BINARYTREE_H		&& \
    !defined DATA_STRUCTURE_CHILDSIBLINGTREE_H	&& \
    !defined Question_8
typedef int SElemType_Sq;
#endif
typedef struct {
    SElemType_Sq *base;                //在栈构造之前和销毁之后，base的值为NULL
    SElemType_Sq *top;                //栈顶指针
    int stacksize;                    //当前已分配的存储空间，以元素为单位
} SqStack;

/* 顺序栈函数列表 */
/**
(01)构造空栈S。 
**/
Status InitStack_Sq(SqStack *S);

/**
(02)销毁S。 
**/
Status DestroyStack_Sq(SqStack *S);

/**
(03)置空S。 
**/
Status ClearStack_Sq(SqStack *S);

/**
(04)判断S是否为空。 
**/
Status StackEmpty_Sq(SqStack S);

/**
(05)返回S元素个数。 
**/
int StackLength_Sq(SqStack S);

/**
(06)用e获取栈顶元素。 
**/
Status GetTop_Sq(SqStack S, SElemType_Sq *e);

/**
(07)元素e进栈。 
**/
Status Push_Sq(SqStack *S, SElemType_Sq e);

/**
(08)元素e出栈。 
**/
Status Pop_Sq(SqStack *S, SElemType_Sq *e);

/**
(09)访问栈。
**/
Status StackTraverse_Sq(SqStack S, void(Visit)(SElemType_Sq));


Status InitStack_Sq(SqStack *S) {
    (*S).base = (SElemType_Sq *) malloc(STACK_INIT_SIZE * sizeof(SElemType_Sq));
    if (!(*S).base)
        exit(OVERFLOW);

    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;

    return OK;
}

Status DestroyStack_Sq(SqStack *S) {
    free((*S).base);

    (*S).base = NULL;
    (*S).top = NULL;
    (*S).stacksize = 0;

    return OK;
}

Status ClearStack_Sq(SqStack *S) {
    (*S).top = (*S).base;

    return OK;
}

Status StackEmpty_Sq(SqStack S) {
    if (S.top == S.base)
        return TRUE;
    else
        return FALSE;
}

int StackLength_Sq(SqStack S) {
    return S.top - S.base;
}

Status GetTop_Sq(SqStack S, SElemType_Sq *e) {
    if (S.top == S.base)
        return ERROR;

    *e = *(S.top - 1);                            //并不破坏栈

    return OK;

}

Status Push_Sq(SqStack *S, SElemType_Sq e) {
    if ((*S).top - (*S).base >= (*S).stacksize)        //栈满，追加存储空间
    {
        (*S).base = (SElemType_Sq *) realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType_Sq));
        if (!(*S).base)
            exit(OVERFLOW);                        //存储分配失败
        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }

    *(S->top) = e;                                //进栈先赋值，栈顶指针再自增
    (S->top)++;

    return OK;
}

Status Pop_Sq(SqStack *S, SElemType_Sq *e) {
    if ((*S).top == (*S).base)
        return ERROR;

    (*S).top--;                                    //出栈栈顶指针先递减，再赋值
    *e = *((*S).top);

    return OK;
}

Status
StackTraverse_Sq(SqStack S, void(Visit)(SElemType_Sq)) {                                                //遍历不应该破坏栈
    SElemType_Sq *p = S.base;

    while (p < S.top)
        Visit(*p++);

    return OK;
}

#endif //DATA_STRUCTURE_SEQUENCESTACK_H
