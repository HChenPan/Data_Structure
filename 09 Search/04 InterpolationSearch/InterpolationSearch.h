//
//文件夹: 09 Search/04 InterpolationSearch
//文件名: InterpolationSearch
//内　容：插值查找相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 03:52
//Version 1.0
//

#ifndef DATA_STRUCTURE_INTERPOLATIONSEARCH_H
#define DATA_STRUCTURE_INTERPOLATIONSEARCH_H

#include "../00 Base/Base.h"                    //**09 Search**//

/* 插值查找函数列表 */
/*━━━━━━━━━━━━━━━━┓
┃(01)插值法查找关键字key的位置。 ┃
┗━━━━━━━━━━━━━━━━*/
int Search_Int(Table T, KeyType key);

int Search_Int(Table T, KeyType key) {
    int low, high, m;
    float j;

    low = 1;
    high = T.length;

    while (low <= high) {
        m = (1.0 * (key - T.elem[low].key) / (T.elem[high].key - T.elem[low].key)) * (high - low) + low;    //注意浮点数转整型

        if (key < T.elem[m].key)
            high = m - 1;
        else if (key > T.elem[m].key)
            low = m + 1;
        else
            return m;
    }

}

#endif //DATA_STRUCTURE_INTERPOLATIONSEARCH_H
