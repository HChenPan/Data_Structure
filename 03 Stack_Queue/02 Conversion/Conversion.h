//
//文件夹: 03 Stack_Queue/02 Conversion
//文件名: Conversion
//内　容：进制转换相关操作列表
//Author Huangcp
//Date 2019/9/10 下午 10:58
//Version 1.0
//

#ifndef DATA_STRUCTURE_CONVERSION_H
#define DATA_STRUCTURE_CONVERSION_H

#include <stdio.h>
#include "../01 SequenceStack/SequenceStack.h"        //**▲03 栈和队列**//

/* 进制转换函数列表 */
/*━━━━━━━━━━━━━━━━━┓
┃(01)算法3.1：十进制数转八进制数。 ┃
┗━━━━━━━━━━━━━━━━━*/
void conversion(int i);


/*════╗
║ 算法3.1║
╚════*/
void conversion(int i) {
    SqStack S;
    SElemType_Sq e;

    InitStack_Sq(&S);

    printf("十进制数 %d 转换为八进制数后为：0", i);

    while (i) {
        Push_Sq(&S, i % 8);                //进栈时从低位到高位
        i = i / 8;
    }

    while (!StackEmpty_Sq(S)) {
        Pop_Sq(&S, &e);                    //出栈时从高位到低位
        printf("%d", e);
    }
}

#endif //DATA_STRUCTURE_CONVERSION_H
