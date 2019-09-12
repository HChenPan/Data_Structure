//
//文件夹: 02 Linear_List/01 Union
//文件名: Union
//内　容：算法: 2.1 求并集相关操作列表
//Author Huangcp
//Date 2019/9/9 下午 11:56
//Version 1.0
//


#ifndef DATA_STRUCTURE_UNION_H
#define DATA_STRUCTURE_UNION_H

#include "../02 SequenceList/SequenceList.h"
/* 并集函数列表 */
/*━━━━━━━━━━━┓
┃(01)算法2.1：A=A∪B。 ┃
┗━━━━━━━━━━━*/
void Union(SqList *La, SqList Lb);

/*━━━━━━━━━━━━┓
┃(02)判断两元素是否相等。┃
┗━━━━━━━━━━━━*/
Status equal(LElemType_Sq e1, LElemType_Sq e2);

/*════╗
║ 算法2.1║ 
╚════*/
void Union(SqList *La, SqList Lb) {
    int La_len, Lb_len;
    int i;
    LElemType_Sq e;

    La_len = ListLength_Sq(*La);            //求顺序表长度 
    Lb_len = ListLength_Sq(Lb);

    for (i = 1; i <= Lb_len; i++) {
        GetElem_Sq(Lb, i, &e);                //取Lb中第i个元素赋给e 
        if (!LocateElem_Sq(*La, e, equal))    //若e不在La中则插入
            ListInsert_Sq(La, ++La_len, e);
    }
}

Status equal(LElemType_Sq e1, LElemType_Sq e2) {
    return e1 == e2 ? TRUE : FALSE;
}

#endif //DATA_STRUCTURE_UNION_H
