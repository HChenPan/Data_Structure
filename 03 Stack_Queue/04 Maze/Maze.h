//
//文件夹: 03 Stack_Queue/04 Maze
//文件名: Maze
//内　容：迷宫相关函数测试
//Author Huangcp
//Date 2019/9/10 下午 11:04
//Version 1.0
//

#ifndef DATA_STRUCTURE_MAZE_H
#define DATA_STRUCTURE_MAZE_H

#include <stdio.h>
#include <stdlib.h>                    //提供system、rand、srand原型
#include <time.h>                        //提供time原型
#include "../../01 Introduction/Status.h"        //**▲01 绪论**//

/* 宏定义 */
#define N 15                            //迷宫的大小为N×N
#define X 4                                //X用于随机数取余，其生成的随机数范围是0到X-1
//X越大，生成可通行迷宫的概率就越大
#define SleepTime 3                        //SleepTime代表休眠时间间隔

/* 迷宫类型定义 */
typedef enum                            //迷宫通道块类型
{
    Wall,                                //外墙
    Obstacle,                            //迷宫障碍
    Way,                                //路径
    DeadLock,                            //路径上的“死胡同”
    East, South, West, North                //访问方向-东南西北
} MazeNode;
typedef struct                            //迷宫通道块坐标
{
    int x;                                //通道块的横、纵坐标定义
    int y;
} PosType;
typedef struct                            //通道块信息
{
    int ord;                        //通道块的“序号”
    PosType seat;                        //通道块的“坐标位置”
    int di;                            //下一个该访问的“方向”
} SElemType_Sq;

#include "../01 SequenceStack/SequenceStack.h"    //**▲03 栈和队列**//

typedef int MazeType;                    //迷宫元素类型

/* 迷宫函数列表 */
/**
(01)算法3.3：迷宫寻路（穷举法） 
**/
Status MazePath(MazeType maze[][N], PosType start, PosType end);

/**
(02)迷宫的初始化,包括出入口的初始化 
**/
void InitMaze(MazeType maze[][N], PosType *start, PosType *end);

/**
(03)在屏幕上画出迷宫
**/
void PaintMaze(MazeType maze[][N]);

/**
(04)迷宫的显示
**/
void ShowMaze(MazeType maze[][N]);

/**
(05)比较迷宫中两个通道块是否为同一通道块
**/
Status EqualPosType(PosType a, PosType b);

/**
(06)判定此通道块是否未访问
**/
Status Pass(PosType seat, MazeType maze[][N]);

/**
(07)遇到未访问结点时留下初始足迹
**/
void FootPrint(PosType seat, MazeType maze[][N]);

/**
(08)更新通道块的信息
**/
void SetSElemType(SElemType_Sq *e, int ord, PosType seat, int di);

/**
(09)当前通道块的后继
**/
PosType NextPos(PosType seat, int di);

/**
(10)判断当前位置是否越界
**/
Status IsCross(PosType seat);

/**
(11)标记当前位置上的通道块不可访问
**/
void MarkPrint(PosType seat, MazeType maze[][N]);


/**
 算法3.3
**/
Status MazePath(MazeType maze[][N], PosType start, PosType end) {
    SqStack S;
    SElemType_Sq nodeInf;                    //nodeInf存储当前通道块信息
    PosType curPos;                            //当前位置
    int curStep;                            //当前通道块序号

    InitStack_Sq(&S);
    curPos = start;                            //设定当前位置为"出口位置"
    curStep = 1;

    do {
        if (Pass(curPos, maze))                //当前位置可通过，即是未曾访问的通道块
        {
            FootPrint(curPos, maze);        //留下足迹
            ShowMaze(maze);

            SetSElemType(&nodeInf, curStep, curPos, East);    //设置通道块信息
            Push_Sq(&S, nodeInf);            //加入路径

            if (EqualPosType(curPos, end))    //到达终点
            {
                printf("\n寻路成功！！\n\n");
                return TRUE;
            }

            curPos = NextPos(curPos, East);    //下一位置是当前位置的东邻
            curStep++;                        //探索下一步
        } else                                //当前位置不能通过
        {
            if (!StackEmpty_Sq(S)) {
                Pop_Sq(&S, &nodeInf);        //修改结点指向

                while (nodeInf.di == North && !StackEmpty_Sq(S))    //此通道块4个方向都遍历过
                {
                    MarkPrint(nodeInf.seat, maze);                //留下不能通过的标记，并退回一步
                    ShowMaze(maze);

                    Pop_Sq(&S, &nodeInf);
                }

                if (nodeInf.di < North) {
                    maze[nodeInf.seat.x][nodeInf.seat.y] = ++nodeInf.di;//改变探索方向，在迷宫数组中留下标记
                    ShowMaze(maze);

                    Push_Sq(&S, nodeInf);

                    curPos = NextPos(nodeInf.seat, nodeInf.di);
                }
            }
        }
    } while (!StackEmpty_Sq(S));

    printf("\n寻路失败！！\n\n");

    return FALSE;
}

void
InitMaze(MazeType maze[][N], PosType *start, PosType *end) {                                                //迷宫规模为N×N
    int i, j, tmp;

    srand((unsigned) time(NULL));                //用系统时间做随机数种子

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == 0 || j == 0 || i == N - 1 || j == N - 1)
                maze[i][j] = Wall;                //迷宫外墙
            else {
                tmp = rand() % X;                    //生成随机数填充迷宫
                if (!tmp)
                    maze[i][j] = Obstacle;        //1/X的概率生成障碍
                else
                    maze[i][j] = Way;            //其它地方加入路径
            }
        }
    }

    (*start).x = 1;                                //迷宫入口
    (*start).y = 0;
    (*end).x = N - 2;                                //迷宫出口
    (*end).y = N - 1;

    maze[1][0] = maze[N - 2][N - 1] = Way;            //开放入口和出口
    maze[1][1] = maze[N - 2][N - 2] = Way;            //为了提高成功率，入口处和出口处临近的结点一直设为通路
}

void PaintMaze(MazeType maze[][N]) {
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            if (maze[i][j] == Wall)                //外墙
                printf("▇");
            else if (maze[i][j] == Obstacle)        //内部障碍
                printf("▓");
            else if (maze[i][j] == East)            //朝东探索
                printf("→");
            else if (maze[i][j] == South)            //朝南探索
                printf("↓");
            else if (maze[i][j] == West)            //朝西探索
                printf("←");
            else if (maze[i][j] == North)            //朝北探索
                printf("↑");
            else if (maze[i][j] == DeadLock)        //访问过且不能通过的结点
                printf("★");
            else                                //未访问过的路径结点
                printf("  ");

            if (j != 0 && j % (N - 1) == 0)                //每隔N个结点换行
                printf("\n");
        }
}

void ShowMaze(MazeType maze[][N])    //相当于刷新操作
{
    Wait(SleepTime);                //暂停
    system("cls");                    //先清除屏幕现有内容
    PaintMaze(maze);                //在屏幕上画出迷宫
}

Status EqualPosType(PosType seat1, PosType seat2) {
    if (seat1.x == seat2.x && seat1.y == seat2.y)
        return TRUE;    //两通道块坐标相等返回1
    else
        return ERROR;
}

Status Pass(PosType seat, MazeType maze[][N]) {
    int x = seat.x;
    int y = seat.y;

    if (!IsCross(seat) && maze[x][y] == Way)    //结点不能越界
        return TRUE;
    else
        return ERROR;
}

void FootPrint(PosType seat, MazeType maze[][N])    //所谓留下足迹即设置其下一次访问方向
{
    maze[seat.x][seat.y] = East;                    //初始设置向东探索
}

void SetSElemType(SElemType_Sq *e, int ord, PosType seat, int di) {
    (*e).ord = ord;
    (*e).seat = seat;
    (*e).di = di;
}

PosType NextPos(PosType seat, int di) {
    PosType tmp = seat;

    switch (di) {
        case East:
            tmp.y++;            //向东
            break;
        case South:
            tmp.x++;            //向南
            break;
        case West:
            tmp.y--;            //向西
            break;
        case North:
            tmp.x--;            //向北
            break;
    }

    return tmp;
}

Status IsCross(PosType seat) {
    int x = seat.x;
    int y = seat.y;

    if (x < 0 || y < 0 || x > N - 1 || y > N - 1)
        return TRUE;                    //越界
    else
        return FALSE;
}

void MarkPrint(PosType seat, MazeType maze[][N]) {
    int x = seat.x;
    int y = seat.y;

    maze[x][y] = DeadLock;                //留下不能通过的标记
}

#endif //DATA_STRUCTURE_MAZE_H
