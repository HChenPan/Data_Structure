//
//文件夹: 04 String/05 WordIndexTable
//文件名: WordIndexTable
//内　容：创建索引表相关操作列表
//Author Huangcp
//Date 2019/9/12 上午 01:02
//Version 1.0
//

#ifndef DATA_STRUCTURE_WORDINDEXTABLE_H
#define DATA_STRUCTURE_WORDINDEXTABLE_H

#include <stdio.h>                        //提供fopen、fclose、feof、fgets原型
#include <stdlib.h>                    //提供exit、strtol原型
#include <string.h>                        //提供strlen、strcmpi、strlwr原型
#include "../../01 Introduction/Status.h"                                    //**▲01 绪论**//
#include "../../02 Linear_List/09 ExtenLinkedList/ExtenLinkedList.h"    //**▲02 线性表**//
#include "../02 HeapString/HeapString.h"                            //**▲04 串**//

/* 宏定义 */
#define MaxBookNum 1000                    //允许的最大书目数
#define MaxKeyNum  2500                    //关键词索引表最大容量
#define MaxLineLen 500                    //书目串的最大长度
#define MaxWordNum 10                    //词表的最大容量

/* 类型定义 */
typedef Status Bool;
typedef struct                            //词表类型(顺序表)
{
    char *str[MaxWordNum];                //字符串数组
    int last;                            //词表的长度
} WordListType;
typedef struct                            //索引项类型
{
    HString key;                        //索引关键词
    ELinkList bnolist;                    //存放书号索引的链表
} IdxTermType;
typedef struct                            //索引表类型(有序表)
{
    IdxTermType item[MaxKeyNum + 1];        //索引表
    int num;                            //索引表中包含的索引项数目
} IdxListType;

/* 全局变量 */
char gBuf[MaxLineLen];                    //书目缓存区
WordListType gWordList = {{"a", "an", "the", "of", "and", "is", "to", "as", "in", "for"}, 10};//常用词词表
WordListType gWdList;                    //关键词词表(普通词表)

/* 创建索引表函数列表 */
/**
(01)算法4.9：读取书目文件，并创建相应的关键词索引表到另一文件。 
**/
void Main(char *bookinfo, char *bookidx);

/**
(02)算法4.10：初始化索引表，且在idxlist.item[0]设置一表头。 
**/
void InitIdxList(IdxListType *idxlist);

/**
(03)从文件f中读取一条书目信息存入书目缓冲区gBuf。 
**/
void GetLine(FILE *f);

/**
(04)从gBuf中提取书名关键词到词表gWdList，书号存入bno。
**/
void ExtractKeyWord(int *bno);

/**
(05)将书号bno对应的书名关键词按词典顺序插入索引表idxlist。
**/
Status InsIdxList(IdxListType *idxlist, int bno);

/**
(06)将生成的索引表idxlist输出到文件g。
**/
void PutText(FILE *g, IdxListType idxlist);

/**
(07)算法4.11：用wd返回词表gWdList中第i个关键词。
**/
void GetWord(int i, HString *wd);

/**
(08)算法4.12：查询在索引表idxlist中是否存在与wd相等的关键词。                       ┃
┃	  若存在，则返回wd在词表中的位置并置b为TRUE，否则返回wd应插入的位置并置b为FALSE。 
**/
int Locate(IdxListType idxlist, HString wd, Bool *b);

/**
(09)算法4.13：在索引表第i项上插入关键词wd，并初始化书号索引的链表为空表。 
**/
void InsertNewKey(IdxListType *idxlist, int i, HString wd);

/**
(10)算法4.14：在索引表的第i项中插入书号为bno的索引。
**/
Status InsertBook(IdxListType *idxlist, int i, int bno);

/**
(11)判断S包含的关键词是否为常用词。 
**/
Status isCommonWords(HString S);


/**
 算法4.9
**/
void Main(char *bookinfo, char *bookidx) {
    FILE *f, *g;
    char b[MaxLineLen];                        //书目临时缓存区
    IdxListType idxlist;                    //关键词索引表
    int i;
    LElemType_E bno;                        //书号

    if (f = fopen(bookinfo, "r"))                //以只读模式打开书目文件
    {
        if (g = fopen(bookidx, "w")) {
            InitIdxList(&idxlist);            //初始化索引表

            fgets(b, MaxLineLen, f);        //跳过文件第一行

            while (!feof(f))                    //开始读取文件f
            {
                GetLine(f);                    //从文件f读入一个书目信息到书目缓冲区gBuf

                ExtractKeyWord(&bno);        //从gBuf提取关键词到词表gWdList，书号存入bno

                InsIdxList(&idxlist, bno);    //将书号及对应的关键词插入索引表idxlist
            }

            PutText(g, idxlist);            //向g中写入数据
        }
    }

    fclose(g);
    fclose(f);                                //关闭文件
}

void InitIdxList(IdxListType *idxlist) {
    char *chars = "关键词            书号索引";        //作为索引表的表头

    StrAssign_H(&((*idxlist).item[0].key), chars);
    InitList_E(&((*idxlist).item[0].bnolist));

    (*idxlist).num = 0;                                //表头为第0条信息
}

void GetLine(FILE *f) {
    int len;

    fgets(gBuf, MaxLineLen, f);                //此处需要反复读取，故b必须为字符数组，不可为字符指针

    len = strlen(gBuf);                        //包括换行符的长度

    gBuf[len - 1] = '\0';                        //换行符处用'\0'取代
}

void ExtractKeyWord(int *bno) {
    char *title;
    FILE *fp;

    *bno = strtol(gBuf, &title, 10);                            //分解字符串gBuf，书号存入bno，书名存入title
    strlwr(title);                                                //大写变小写

    fp = tmpfile();                                                //建立临时文件
    fprintf(fp, "%s", title);                                    //把字符串写入临时文件
    fseek(fp, 0, SEEK_SET);                                        //文件指针移到起始位置

    for (gWdList.last = 0; gWdList.last < MaxWordNum; gWdList.last++) {
        gWdList.str[gWdList.last] = (char *) malloc(MaxLineLen * sizeof(char));
        if (!gWdList.str[gWdList.last])
            exit(OVERFLOW);
        //从临时文件中读取字符串
        if (fscanf(fp, "%s", gWdList.str[gWdList.last]) == EOF)    //读取失败则退出循环
            break;
    }
}

/**
 算法4.10 
**/
Status InsIdxList(IdxListType *idxlist, int bno) {
    int i, j;
    Bool boo;
    HString wd;

    if (!gWdList.last)
        return ERROR;

    for (i = 0; i < gWdList.last; i++) {
        GetWord(i, &wd);                            //用堆串wd获取关键词词表第i个字符串

        if (!isCommonWords(wd))                        //如果此关键词不是常用词，则需要进行插入操作
        {
            j = Locate(*idxlist, wd, &boo);

            if (boo == FALSE)                            //当前关键词不在索引表中，则需插入此关键词
                InsertNewKey(idxlist, j, wd);

            if (!InsertBook(idxlist, j, bno))        //插入书号
                return ERROR;
        }
    }
    return OK;
}

void PutText(FILE *g, IdxListType idxlist) {
    int i, j, m, n;
    Link p;
    HString S;
    ELinkList L;

    for (i = 0; i <= idxlist.num; i++) {
        S = idxlist.item[i].key;                    //输出关键词
        for (m = 0; m < S.length; m++)
            fprintf(g, "%c", S.ch[m]);

        if (i)                                        //不是表头
        {
            for (j = 1; j <= 18 - idxlist.item[i].key.length; j++)        //输入一定数量的空格隔开
                fprintf(g, " ");

            L = idxlist.item[i].bnolist;            //输出书号索引
            for (n = 1, p = L.head->next; n <= L.len; n++) {
                fprintf(g, "%03d", p->data);
                p = p->next;
                if (p)
                    fprintf(g, "，");
            }
        }

        if (i != idxlist.num)                            //未到最后一行
            fprintf(g, "\n");
    }

}

/**
 算法4.11 
**/
void GetWord(int i, HString *wd) {
    char *p = gWdList.str[i];

    StrAssign_H(wd, p);
}

/**
 算法4.12 
**/
int Locate(IdxListType idxlist, HString wd, Bool *b) {
    int i, m;

    for (i = idxlist.num; i > 0 && (m = StrCompare_H(idxlist.item[i].key, wd)) > 0; i--);

    if (m == 0 && idxlist.num != 0) {
        *b = TRUE;
        return i;
    } else {
        *b = FALSE;
        return i + 1;
    }
}

/**
 算法4.13 
**/
void InsertNewKey(IdxListType *idxlist, int i, HString wd) {
    int j;

    for (j = (*idxlist).num; j >= i; j--)                    //索引项后移
        (*idxlist).item[j + 1] = (*idxlist).item[j];

    StrCopy_H(&((*idxlist).item[i].key), wd);            //插入索引项

    (*idxlist).num++;                                    //索引书目增一

    InitList_E(&((*idxlist).item[i].bnolist));
}

/**
 算法4.14 
**/
Status InsertBook(IdxListType *idxlist, int i, LElemType_E bno) {
    Link p;

    if (!MakeNode_E(&p, bno))                            //分配失败
        return ERROR;

    Append_E(&((*idxlist).item[i].bnolist), p);            //插入新的书号索引

    return OK;
}

Status isCommonWords(HString S)                //此处指向的字符串并无空字符结尾
{                                            //常用词词表中的字符串是有空字符结尾的
    int i, len;
    char a[S.length + 1];
    Status flag = FALSE;

    for (i = 0; i < S.length; i++)
        a[i] = S.ch[i];
    a[i] = '\0';

    for (i = 0; i < gWordList.last; i++) {
        if (!strcmpi(a, gWordList.str[i]))    //对两字符串进行忽略大小写的比较
        {
            flag = TRUE;
            break;                            //两字符串相等则退出循环
        }
    }

    return flag;
}

#endif //DATA_STRUCTURE_WORDINDEXTABLE_H
