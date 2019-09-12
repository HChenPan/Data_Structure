//
//文件夹: 09 Search/01 SequnceSearch
//文件名: SequenceSearch
//内　容：顺序查找（无序表）相关操作列表
//Author Huangcp
//Date 2019/9/13 上午 03:19
//Version 1.0
//

#ifndef DATA_STRUCTURE_SEQUENCESEARCH_H
#define DATA_STRUCTURE_SEQUENCESEARCH_H

#include "../00 Base/Base.h"                    //**09 Search**//

/* 宏函数 */
#define EQ(a, b) ((a)==(b))

/* 顺序查找函数列表 */
/*━━━━━━━━━━━━━━━━━━━┓
┃(01)算法9.1：顺序查找关键字key的位置。┃
┗━━━━━━━━━━━━━━━━━━━*/
int Search_Seq(Table T, KeyType key);

/*════╗
║ 算法9.1║
╚════*/
int Search_Seq(Table T, KeyType key) {
    int i;

    T.elem[0].key = key;

    for (i = T.length; !EQ(T.elem[i].key, key); --i);

    return i;
}

#endif //DATA_STRUCTURE_SEQUENCESEARCH_H
