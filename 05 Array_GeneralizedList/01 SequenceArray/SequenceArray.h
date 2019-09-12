//
//文件夹: 05 Array_GeneralizedList/01 SequenceArray
//文件名: SequenceArray
//内　容：数组相关操作列表
//Author Huangcp
//Date 2019/9/12 上午 01:14
//Version 1.0
//

#ifndef DATA_STRUCTURE_SEQUENCEARRAY_H
#define DATA_STRUCTURE_SEQUENCEARRAY_H


#include <stdio.h>
#include <stdlib.h>                                //提供malloc、realloc、free、exit原型
#include <stdarg.h>                                //提供宏va_start、va_arg、va_end
#include "../../01 Introduction/Status.h"                //**▲01 绪论**//

/* 宏定义 */
#define MAX_ARRAY_DIM 8                            //数组的最大维度为8

/* 数组类型定义 */
typedef int AElemType_Sq;
typedef struct                                    //数组的顺序存储表示
{
    AElemType_Sq *base;                            //数组元素基址（存放数组元素）
    int dim;                                    //数组维数
    int *bounds;                                //数组维界基址（存放数组行、列信息）
    int *constants;                                //数组映像函数常量基址（存储跨越某个维度时需要越过的元素个数）
} Array;

/* 数组函数列表 */
/*━━━━━━━━━━━━━━┓
┃(01)初始化维数为dim的数组。 ┃
┗━━━━━━━━━━━━━━*/
Status InitArray(Array *A, int dim, ...);

/*━━━━━━━┓
┃(02)销毁数组。┃
┗━━━━━━━*/
Status DestroyArray(Array *A);

/*━━━━━━━━━━━━━━━━━━━━┓
┃(03)求出ap指示的值在数组A中的相对位置。 ┃
┗━━━━━━━━━━━━━━━━━━━━*/
Status LocateArray(Array A, va_list ap, int *off);

/*━━━━━━━━━━━━━━━━━┓
┃(04)取值，可变参数是dim个下标值。 ┃
┗━━━━━━━━━━━━━━━━━*/
Status ValueArray(Array A, AElemType_Sq *e, ...);

/*━━━━━━━━━━━━━━━━━┓
┃(05)赋值，可变参数是dim个下标值。 ┃
┗━━━━━━━━━━━━━━━━━*/
Status AssignArray(Array *A, AElemType_Sq e, ...);

/*━━━━━━━━━━━━━━┓
┃(06)按行依次输出数组中内容。┃
┗━━━━━━━━━━━━━━*/
void ArrayPrint(Array A);


Status InitArray(Array *A, int dim, ...) {
    int elemtotal;                                        //统计数组中总元素个数
    va_list ap;                                            //ap存放可变参数表信息
    int i;

    if (dim < 1 || dim > MAX_ARRAY_DIM)                        //数组维数有限制
        return ERROR;

    A->dim = dim;                                        //初始化数组维度

    A->bounds = (int *) malloc(dim * sizeof(int));            //初始化数组维度信息表
    if (!A->bounds)
        return OVERFLOW;

    elemtotal = 1;

    va_start(ap, dim);                                    //使ap指向第一个可变参数，dim相当于起始标识
    for (i = 0; i < dim; i++) {
        A->bounds[i] = va_arg(ap, int);                    //获取数组行、列信息
        if (A->bounds[i] <= 0)
            return UNDERFLOW;

        elemtotal *= A->bounds[i];
    }
    va_end(ap);                                            //置空ap

    A->base = (AElemType_Sq *) malloc(elemtotal * sizeof(AElemType_Sq));
    if (!A->base)                                        //初始化数组空间
        return OVERFLOW;

    A->constants = (int *) malloc(dim * sizeof(int));        //初始化数组映像函数常量信息表
    if (!A->constants)
        return OVERFLOW;

    A->constants[dim - 1] = 1;
    for (i = dim - 2; i >= 0; i--)                                //假设数组维度为2，则constants存储移动每一行、每一列所需跨越的元素个数
        A->constants[i] = A->bounds[i + 1] * A->constants[i + 1];

    return OK;
}

Status DestroyArray(Array *A) {
    if (!A->base)
        return ERROR;
    free(A->base);
    A->base = NULL;

    if (!A->bounds)
        return ERROR;
    free(A->bounds);
    A->bounds = NULL;

    if (!A->constants)
        return ERROR;
    free(A->constants);
    A->constants = NULL;

    A->dim = 0;

    return OK;
}

Status LocateArray(Array A, va_list ap, int *off) {
    int i, ind;

    *off = 0;

    for (i = 0; i < A.dim; i++) {
        ind = va_arg(ap, int);
        if (ind < 0 || ind >= A.bounds[i])            //保证下标不越界
            return OVERFLOW;

        *off += A.constants[i] * ind;            //某个维度的单位元素个数*需要跨过的单位
    }

    return OK;
}

Status ValueArray(Array A, AElemType_Sq *e, ...) {
    va_list ap;
    Status result;
    int off;

    va_start(ap, *e);

    result = LocateArray(A, ap, &off);
    if (result == OVERFLOW)
        return result;

    *e = *(A.base + off);

    return OK;
}

Status AssignArray(Array *A, AElemType_Sq e, ...) {
    va_list ap;
    Status result;
    int off;

    va_start(ap, e);

    result = LocateArray(*A, ap, &off);
    if (result == OVERFLOW)
        return result;

    *(A->base + off) = e;

    return OK;
}

void ArrayPrint(Array A) {
    int i, j;

    for (i = 0, j = 1; i < A.dim; i++)
        j *= A.bounds[i];

    for (i = 0; i < j; i++)
        printf("%d ", A.base[i]);
}

#endif //DATA_STRUCTURE_SEQUENCEARRAY_H
