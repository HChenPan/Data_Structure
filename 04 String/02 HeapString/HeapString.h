//
//文件夹: 04 String/02 HeapString
//文件名: HeapString
//内　容：堆串相关操作列表
//Author Huangcp
//Date 2019/9/11 下午 10:38
//Version 1.0
//

#ifndef DATA_STRUCTURE_HEAPSTRING_H
#define DATA_STRUCTURE_HEAPSTRING_H

#include <stdio.h>
#include <stdlib.h>                        //提供malloc、realloc、free、exit原型
#include <string.h>                        //提供strlen原型
#include "../../01 Introduction/Status.h"        //**▲01 绪论**//

/* 串的堆存储表示 */
typedef struct {
    char *ch;                            //若是非空串，则按串长分配存储区，否则ch为NULL
    int length;
} HString;

/* 堆串函数列表 */
/*━━━━━━━━━━┓
┃(01)初始化S为空串。 ┃
┗━━━━━━━━━━*/
void InitString_H(HString *S);

/*━━━━━━━━━━━━━━━━━━┓
┃(02)生成一个其值等于常量chars的串T。┃
┗━━━━━━━━━━━━━━━━━━*/
Status StrAssign_H(HString *T, char *chars);

/*━━━━━━━━━━━┓
┃(03)由串S复制得到串T。┃
┗━━━━━━━━━━━*/
Status StrCopy_H(HString *T, HString S);

/*━━━━━━━━━━━━━━━━━━━━┓
┃(04)若S为空串，返回TRUE,否则返回FALSE。 ┃
┗━━━━━━━━━━━━━━━━━━━━*/
Status StrEmpty_H(HString S);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(05)若S>T，返回值>0；若S<T，返回值<0；否则，返回值=0。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
Status StrCompare_H(HString S, HString T);

/*━━━━━━┓
┃(06)求串长。┃
┗━━━━━━*/
int StrLength_H(HString S);

/*━━━━━━┓
┃(07)清空S。 ┃
┗━━━━━━*/
Status ClearString_H(HString *S);

/*━━━━━━━━━━━━━━━━━━┓
┃(08)用T返回由S1和S2联接而成的新串。 ┃
┗━━━━━━━━━━━━━━━━━━*/
Status Concat_H(HString *T, HString S1, HString S2);

/*━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(09)用Sub返回串S的第pos个字符起长度为len的子串。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━*/
Status SubString_H(HString *Sub, HString S, int pos, int len);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(10)返回T在S中第pos个字符后第一次出现的位置，不存在则返回0。┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
int Index_H(HString S, HString T, int pos);

/*━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃(11)用V替换主串S中出现的所有与T相等的不重叠的子串。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━*/
Status Replace_H(HString *S, HString T, HString V);

/*━━━━━━━━━━━━━━━━━━━━━━┓
┃(12)算法4.4：在串S的第pos个字符之前插入串T。┃
┗━━━━━━━━━━━━━━━━━━━━━━*/
Status StrInsert_H(HString *S, int pos, HString T);

/*━━━━━━━━━━━━━━━━━━━━━━━┓
┃(13)从串S中删除第pos个字符起长度为len的子串。 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━*/
Status StrDelete_H(HString *S, int pos, int len);

/*━━━━━━━┓
┃(14)销毁串S。 ┃
┗━━━━━━━*/
void DestroyString_H(HString *S);

/*━━━━━━━┓
┃(15)输出串S。 ┃
┗━━━━━━━*/
void StrPrint_H(HString S);


void InitString_H(HString *S) {
    (*S).ch = NULL;
    (*S).length = 0;
}

Status StrAssign_H(HString *T, char *chars) {
    int i, j;

    InitString_H(T);

    i = strlen(chars);

    if (!i)
        return ERROR;
    else {
        (*T).ch = (char *) malloc(i * sizeof(char));
        if (!((*T).ch))
            exit(OVERFLOW);

        for (j = 0; j < i; j++)
            (*T).ch[j] = chars[j];

        (*T).length = i;
    }

    return OK;
}

Status StrCopy_H(HString *T, HString S) {
    int i;

    InitString_H(T);

    if (StrEmpty_H(S))
        return ERROR;

    (*T).ch = (char *) malloc(S.length * sizeof(char));
    if (!(*T).ch)
        exit(OVERFLOW);

    for (i = 0; i < S.length; i++)
        (*T).ch[i] = S.ch[i];

    (*T).length = S.length;

    return OK;
}

Status StrEmpty_H(HString S) {
    if (S.length == 0 && S.ch == NULL)
        return TRUE;
    else
        return FALSE;
}

Status StrCompare_H(HString S, HString T) {
    int i;

    for (i = 0; i < S.length && i < T.length; i++) {
        if (S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];
    }

    return S.length - T.length;
}

int StrLength_H(HString S) {
    if (StrEmpty_H(S))
        return 0;
    else
        return S.length;
}

Status ClearString_H(HString *S) {
    if ((*S).ch) {
        free((*S).ch);
        (*S).ch = NULL;
    }

    (*S).length = 0;

    return OK;
}

Status Concat_H(HString *T, HString S1, HString S2) {
    int i;

    InitString_H(T);

    (*T).length = S1.length + S2.length;

    (*T).ch = (char *) malloc((*T).length * sizeof(char));
    if (!(*T).ch)
        exit(OVERFLOW);

    for (i = 0; i < S1.length; i++)
        (*T).ch[i] = S1.ch[i];

    for (i = 0; i < S2.length; i++)
        (*T).ch[S1.length + i] = S2.ch[i];

    return OK;
}

Status SubString_H(HString *Sub, HString S, int pos, int len) {
    int i;

    InitString_H(Sub);

    if (StrEmpty_H(S))
        return ERROR;

    if (pos < 1 || pos > S.length || len < 0 || pos + len - 1 > S.length)
        return ERROR;

    if (len)                                //非空子串
    {
        (*Sub).ch = (char *) malloc(len * sizeof(char));
        if (!(*Sub).ch)
            exit(OVERFLOW);

        for (i = 0; i < len; i++)
            (*Sub).ch[i] = S.ch[i + pos - 1];

        (*Sub).length = len;
    }

    return OK;
}

int Index_H(HString S, HString T, int pos) {
    int s, t, i;
    HString Sub;

    InitString_H(&Sub);

    if (pos > 0) {
        s = S.length;
        t = T.length;
        i = pos;

        while (i + t - 1 <= s) {
            SubString_H(&Sub, S, i, t);

            if (StrCompare_H(Sub, T))
                i++;
            else
                return i;
        }
    }

    return 0;
}

Status Replace_H(HString *S, HString T, HString V) {
    int i;

    if (StrEmpty_H(T))
        return ERROR;

    i = Index_H(*S, T, 1);

    while (i != 0) {
        StrDelete_H(S, i, StrLength_H(T));

        StrInsert_H(S, i, V);

        i += StrLength_H(V);

        i = Index_H(*S, T, i);
    }

    return OK;
}

/*════╗
║ 算法4.4║
╚════*/
Status StrInsert_H(HString *S, int pos, HString T) {
    int i;

    if (pos < 1 || pos > (*S).length + 1)
        return ERROR;

    if (StrEmpty_H(T))
        return ERROR;
    else {
        (*S).ch = (char *) realloc((*S).ch, ((*S).length + T.length) * sizeof(char));
        if (!(*S).ch)
            exit(OVERFLOW);

        for (i = (*S).length - 1; i >= pos - 1; i--)        //为插入T而腾出位置
            (*S).ch[i + T.length] = (*S).ch[i];

        for (i = 0; i < T.length; i++)
            (*S).ch[pos - 1 + i] = T.ch[i];        //插入T

        (*S).length += T.length;
    }

    return OK;
}

Status StrDelete_H(HString *S, int pos, int len) {
    int i;

    if (StrEmpty_H(*S))
        return ERROR;

    if (pos < 1 || pos + len - 1 > (*S).length || len < 0)
        return ERROR;

    for (i = pos - 1; i + len <= (*S).length; i++)
        (*S).ch[i] = (*S).ch[i + len];

    (*S).length -= len;

    (*S).ch = (char *) realloc((*S).ch, (*S).length * sizeof(char));    //缩小分配的空间

    return OK;
}

void DestroyString_H(HString *S) {
    //堆串不能被销毁
}

void StrPrint_H(HString S) {
    int i;

    if (StrEmpty_H(S))
        printf("S为空串，不可输出！");

    for (i = 0; i < S.length; i++)
        printf("%c", S.ch[i]);
}

#endif //DATA_STRUCTURE_HEAPSTRING_H
