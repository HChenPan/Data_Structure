//
//文件夹: 06 Tree_BinaryTree/11 NQueens
//文件名: NQueens
//内　容：N皇后问题相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 02:17
//Version 1.0
//

#ifndef DATA_STRUCTURE_NQUEENS_H
#define DATA_STRUCTURE_NQUEENS_H

#include <stdio.h>
#include "../../01 Introduction/Status.h"                //**01 Introduction**//

/* 宏定义 */
#define N 8                                        //棋盘最大范围N*N

/* N皇后问题类型定义 */
typedef int ChessBoard;                            //棋盘类型

/* 全局变量 */
int order;                                        //跟踪每一种解法

/* N皇后问题函数列表 */
/**
(01)初始化N*N的棋盘c。
**/
void InitChessBoard_CB(ChessBoard c[N][N]);

/**
(02)算法6.16：在指定大小棋盘上求出N皇后问题的各解。 
**/
void Trial_CB(int i, ChessBoard c[N][N]);

/**
(03)判断在x行y列放入棋子后棋盘布局是否合理。
**/
Status Layout_CB(int x, int y, ChessBoard c[N][N]);

/**
(04)展示棋盘中的皇后布局。
**/
void Output_CB(ChessBoard c[N][N]);


void InitChessBoard_CB(ChessBoard c[N][N]) {
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            c[i][j] = 0;                                //0表示棋盘无棋子
}

/**
 算法6.16 
**/
void Trial_CB(int i, ChessBoard c[N][N]) {
    int j;

    if (N <= 3) {
        printf("此N值下无解！！\n");
        return;
    }

    if (i > N) {
        printf(" %d 皇后问题的第 %d 种解法...\n", N, ++order);
        Output_CB(c);
        printf("\n");
        //PressEnter;									//可设置此语句逐步运行
    } else {
        for (j = 1; j <= N; j++) {
            c[i - 1][j - 1] = 1;                            //在第i行第j列放置一个棋子

            if (Layout_CB(i, j, c))                        //判断此时布局是否合理
                Trial_CB(i + 1, c);

            c[i - 1][j - 1] = 0;                            //移去第i行第j列的棋子
        }
    }
}

Status Layout_CB(int x, int y, ChessBoard c[N][N])        //x、y为新加入结点的行和列
{
    int k, count;
    int m, n;

    count = 0;
    for (k = 1; k <= N; k++) {
        if (c[x - 1][k - 1] == 1)
            count++;
        if (count > 1)
            return ERROR;
    }

    count = 0;
    for (k = 1; k <= N; k++) {
        if (c[k - 1][y - 1] == 1)
            count++;
        if (count > 1)
            return ERROR;
    }

    m = x - 1;
    n = y - 1;
    while (m >= 1 && n >= 1) {
        if (c[m - 1][n - 1])
            return ERROR;
        m = m - 1;
        n = n - 1;
    }

    m = x + 1;
    n = y + 1;
    while (m <= N && n <= N) {
        if (c[m - 1][n - 1])
            return ERROR;
        m = m + 1;
        n = n + 1;
    }

    m = x + 1;
    n = y - 1;
    while (m <= N && n >= 1) {
        if (c[m - 1][n - 1])
            return ERROR;
        m = m + 1;
        n = n - 1;
    }

    m = x - 1;
    n = y + 1;
    while (m >= 1 && n <= N) {
        if (c[m - 1][n - 1])
            return ERROR;
        m = m - 1;
        n = n + 1;
    }

    return OK;
}

void Output_CB(ChessBoard c[N][N]) {
    int i, j;

    printf("┏");
    for (i = 1; i <= N - 1; i++)
        printf("━┳");
    printf("━┓\n");

    for (i = 1; i <= N; i++) {
        printf("┃");
        for (j = 1; j <= N; j++) {
            if (c[i - 1][j - 1] == 1)
                printf("●┃");
            else
                printf("  ┃");
        }
        printf("\n");

        if (i < N) {
            printf("┣");
            for (j = 1; j <= N - 1; j++)
                printf("━╋");
            printf("━┫");
            printf("\n");
        }
    }

    printf("┗");
    for (i = 1; i <= N - 1; i++)
        printf("━┻");
    printf("━┛\n");
}

#endif //DATA_STRUCTURE_NQUEENS_H
