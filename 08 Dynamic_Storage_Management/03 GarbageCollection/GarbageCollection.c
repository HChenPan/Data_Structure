//
//文件夹: 08 Dynamic_Storage_Management/03 GarbageCollection
//文件名: GarbageCollection
//内　容：无用单元搜集相关函数测试
//Author Huangcp
//Date 2019/9/13 上午 03:00
//Version 1.0
//

#include "GarbageCollection.h"

/* 函数原型 */
void Traverse(GList L, void(Visit)(GList));

void print(GList L);

int main(int argc, char *argv[]) {
    GList G;

    printf("创建并输出广义表：");
    {
        SString S;
        char *s = "((),(e),(a,(b,c,d)))";

        StrAssign_Sq(S, s);
        InitGList_GL_H_T(&G);
        CreateGList_GL_H_T_1(&G, S);
        Output_GL_H_T(G, Head);
        printf("\n\n");
    }
    PressEnter;

    printf("▼1\n▲函数 MakeList 测试...\n");                    //1.函数MakeList测试
    {
        printf("访问前的标志状态...\n");
        Traverse(G, print);
        printf("\n");
        MakeList(G);

        PressEnter;

        printf("访问后的标志状态...\n");
        Traverse(G, print);
        printf("\n");
    }
    PressEnter;

    return 0;
}

void Traverse(GList L, void(Visit)(GList)) {
    if (L) {
        Visit(L);

        if (L->tag == List) {
            Traverse(L->Union.ptr.hp, Visit);
            Traverse(L->Union.ptr.tp, Visit);
        }
    }
}

void print(GList L) {
    if (L->tag == Atom)
        printf("mark = %d 原子结点：%c\n", L->mark, L->Union.atom);
    else
        printf("mark = %d 表结点\n", L->mark);
}
