//
//文件夹: 09 Search/02 BinSearch
//文件名: BinSearch
//内　容：折半查找相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 03:20
//Version 1.0
//

#ifndef DATA_STRUCTURE_BINSEARCH_H
#define DATA_STRUCTURE_BINSEARCH_H

#include "../00 Base/Base.h"        //**09 Search**//

/* 宏函数 */
#define EQ(a, b) ((a)==(b))
#define LT(a, b) ((a) < (b))

/* 折半查找函数列表 */
/**
(01)算法9.2：折半查找关键字key的位置。
**/
int Search_Bin(Table T, KeyType key);

/**
 算法9.2
**/
int Search_Bin(Table T, KeyType key) {
    int low, high, mid;

    low = 1;
    high = T.length;

    while (low <= high) {
        mid = (low + high) / 2;

        if (EQ(key, T.elem[mid].key))
            return mid;
        else if (LT(key, T.elem[mid].key))
            high = mid - 1;
        else
            low = mid + 1;
    }

    return 0;
}

#endif //DATA_STRUCTURE_BINSEARCH_H
