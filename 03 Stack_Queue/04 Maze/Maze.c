//
//文件夹: 03 Stack_Queue/04 Maze
//文件名: Maze
//内　容：迷宫相关函数测试
//Author Huangcp
//Date 2019/9/10 下午 11:04
//Version 1.0
//

#include "Maze.h"
int main(int argc, char *argv[])
{
    MazeType maze[N][N];
    PosType start, end;
    SElemType_Sq e;
    char Re = 'Y';

    while(Re=='Y' || Re=='y')
    {
        InitMaze(maze, &start, &end);	//初始化迷宫，包括出入口
        ShowMaze(maze);					//显示迷宫的初始状态
        MazePath(maze,start,end);		//迷宫寻路

        printf("重置？（Y/N）：");
        scanf("%c", &Re);
    }

    return 0;
}