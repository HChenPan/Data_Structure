//
//文件夹: 04 String/04 KMP
//文件名: KMP
//内　容：KMP算法相关操作列表
//Author Huangcp
//Date 2019/9/12 上午 12:59
//Version 1.0
//

#ifndef DATA_STRUCTURE_KMP_H
#define DATA_STRUCTURE_KMP_H

#include <stdio.h>
#include "../01 SequenceString/SequenceString.h"            //**▲04 串**//

/* KMP算法函数列表 */
/*━━━━━━━━━━━━━┓
┃(1)算法4.6：KMP匹配算法。 ┃
┗━━━━━━━━━━━━━*/
int Index_KMP(SString S, SString T, int pos, int next[]);

/*━━━━━━━━━━━━━━━━┓
┃(2)算法4.7：求next函数值的算法。┃
┗━━━━━━━━━━━━━━━━*/
void get_next(SString T, int next[]);

/*━━━━━━━━━━━━━━━━━━━━┓
┃(3)算法4.8：改进后的求next函数值的算法。┃
┗━━━━━━━━━━━━━━━━━━━━*/
void get_nextval(SString T, int nextval[]);

/*════╗
║ 算法4.6║
╚════*/
int Index_KMP(SString S, SString T, int pos, int next[]) {
    int i = pos;
    int j = 1;

    if (pos < 1)
        return 0;

    while (i <= S[0] && j <= T[0]) {
        if (S[i] == T[j] || j == 0) {
            i++;
            j++;
        } else                            //失配时回到前一个适当的位置
            j = next[j];
    }

    if (j > T[0])                            //匹配成功
        return i - T[0];
    else                                //匹配失败
        return 0;
}

/*════╗
║ 算法4.7║
╚════*/
void get_next(SString T, int next[]) {
    int i = 1;
    int j = 0;

    next[1] = 0;                        //第一个字符处失配

    while (i < T[0]) {
        if (T[i] == T[j] || !j) {
            i++;
            j++;
            next[i] = j;
        } else
            j = next[j];
    }
}

/*════╗
║ 算法4.8║
╚════*/
void get_nextval(SString T, int nextval[]) {
    int i = 1;
    int j = 0;

    nextval[1] = 0;

    while (i < T[0]) {
        if (T[i] == T[j] || !j) {
            i++;
            j++;
            if (T[i] != T[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        } else
            j = nextval[j];
    }
}


#endif //DATA_STRUCTURE_KMP_H
