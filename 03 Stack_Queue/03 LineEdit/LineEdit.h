//
//文件夹: 03 Stack_Queue/03 LineEdit
//文件名: LineEdit
//内　容：行编辑程序相关操作列表
//Author Huangcp
//Date 2019/9/10 下午 11:00
//Version 1.0
//

#ifndef DATA_STRUCTURE_LINEEDIT_H
#define DATA_STRUCTURE_LINEEDIT_H

#include <stdio.h>
#include "../01 SequenceStack/SequenceStack.h"        //**▲03 栈和队列**//

/* 行编辑程序函数列表 */
/*━━━━━━━━━━━━━┓
┃(01)算法3.2：行编辑程序。 ┃
┗━━━━━━━━━━━━━*/
void LineEdit(char Buffer[]);

/*━━━━━━━━┓
┃(02)打印元素e。 ┃
┗━━━━━━━━*/
void Print(SElemType_Sq e);

/*════╗
║ 算法3.2║
╚════*/
/* 与严蔚敏课本所述算法略有差别，但算法思想一致 */
void LineEdit(char Buffer[]) {
    SqStack S;                        //接收输入的字符
    SElemType_Sq e;
    int i;
    char ch;

    InitStack_Sq(&S);

    i = 0;
    ch = Buffer[i++];
    while (ch != '\0') {
        while (ch != '\0' && ch != '\n') {
            switch (ch) {
                case '#':
                    Pop_Sq(&S, &e);
                    break;
                case '@':
                    ClearStack_Sq(&S);
                    break;
                default :
                    Push_Sq(&S, ch);
            }
            ch = Buffer[i++];
        }

        if (ch == '\n') {
            Push_Sq(&S, ch);
            StackTraverse_Sq(S, Print);
            ClearStack_Sq(&S);
            ch = Buffer[i++];
        }
    }

    if (ch == '\0') {
        StackTraverse_Sq(S, Print);
        DestroyStack_Sq(&S);
    }
}

void Print(SElemType_Sq e) {
    printf("%c", e);
}

#endif //DATA_STRUCTURE_LINEEDIT_H
