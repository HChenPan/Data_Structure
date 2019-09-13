//
//文件夹: 03 Stack_Queue/09 BankQueuing
//文件名: BankQueuing
//内　容：模拟银行排队相关操作列表
//Author Huangcp
//Date 2019/9/10 下午 11:25
//Version 1.0
//

#ifndef DATA_STRUCTURE_BANKQUEUING_H
#define DATA_STRUCTURE_BANKQUEUING_H

#include <stdio.h>
#include <stdlib.h>                        //提供malloc、realloc、free、exit原型
#include <time.h>                        //提供time原型
#include "../../01 Introduction/Status.h"        //**▲01 绪论**//

/* 宏定义 */
#define SleepTime 1                        //SleepTime代表休眠时间
#define DurationTime 20                    //办理业务持续时间从1到DurationTime分钟不等
#define IntervalTime 10                    //下一个客户到来时间间隔为1到IntervalTime分钟不等

/* 类型定义 */
typedef enum {
    Arrive, Leave_1, Leave_2, Leave_3, Leave_4
} EventType;                                //事件类型，0代表到达事件，1至4表示四个窗口的离开事件
typedef struct                            //事件链表
{
    int OccurTime;                        //事件发生时刻
    EventType NType;                    //事件类型
} Event;
typedef Event LElemType_L;                //事件链表元素
typedef struct LNode {
    LElemType_L data;
    struct LNode *next;
} LNode;
typedef LNode *LinkList;
typedef LinkList EventList;                                            //事件链表类型，定义为有序链表

#include "../../02 Linear_List/04 SinglyLinkedList/SinglyLinkedList.h"    //**▲02 线性表**//

typedef struct {
    int ArrivedTime;                    //客户到达时间
    int Duration;                        //办理事务所需的时间
    int Count;                            //此变量记录来到每个队列的客户是第几个
} QElemType_L;                            //队列的数据元素类型
#include "../07 LinkQueue/LinkQueue.h"    //**▲03 栈和队列**//

/* 全局变量 */
int gTotalTime, gCustomerNum;            //累计客户逗留时间，客户数
int gCloseTime = 480;                    //关门时间,假设银行每天营业8小时，480分
EventList gEv;                            //事件表
Event gEn;                                //事件
LinkQueue gQ[5];                        //4个客户队列,0号单元弃用
QElemType_L gCustomerRcd;                //客户记录

/* 模拟银行排队函数列表 */
/**
(01)算法3.6：模拟银行排队事件。 
**/
void Bank_Simulation_1();

/**
(02)银行开门，初始化各变量。
**/
void OpenForDay();

/**
(03)判断事件表是否为空。
**/
Status MoreEvent();

/**
(04)事件驱动，获取当前事件类型。
**/
void EventDrived(char *event);

/**
(05)处理客户到达事件。
**/
void CustomerArrived();

/**
(06)处理客户离开事件。
**/
void CustomerDeparture();

/**
(07)事件类型错误。
**/
void Invalid();

/**
(08)银行关门。
**/
void CloseForDay();

/**
(09)比较事件a和b发生的先后次序。
**/
int cmp(Event a, Event b);

/**
(10)生成随机数，包括当前客服办理业务所需时间和下一客户到达间隔的时间。
**/
void Random(int *durtime, int *intertime);

/**
(11)将事件插入事件表正确位置。
**/
Status OrderInsert(EventList gEv, Event gEn, int(cmp)(Event, Event));

/**
(12)求长度最短队列的序号。
**/
int Minimum();

/**
(13)显示当前队列的客户排队情况。
**/
void Show();

/**
(14)算法3.7：模拟银行排队事件。 
**/
void Bank_Simulation_2();


/**
 算法3.6
**/
void Bank_Simulation_1()                //银行业务模拟，统计一天内客户在银行逗留的平均时间
{
    char eventType;

    OpenForDay();                        //初始化

    while (MoreEvent()) {
        EventDrived(&eventType);        //事件驱动

        switch (eventType) {
            case 'A':
                CustomerArrived();
                break;
            case 'D':
                CustomerDeparture();
                break;
            default :
                Invalid();
        }
    }

    CloseForDay();
}

void OpenForDay() {
    int i;

    gTotalTime = 0;                    //初始化累计时间和客户数为0
    gCustomerNum = 0;

    InitList_L(&gEv);                //初始化事件链表为空表

    gEn.OccurTime = 0;                //设定第一个客户到达事件
    gEn.NType = Arrive;

    OrderInsert(gEv, gEn, cmp);        //插入事件表

    for (i = 1; i <= 4; ++i)
        InitQueue_L(&gQ[i]);        //置空队列

    Show();
}

Status MoreEvent() {
    if (!ListEmpty_L(gEv))
        return TRUE;
    else
        return FALSE;
}

void EventDrived(char *event) {
    ListDelete_L(gEv, 1, &gEn);

    if (gEn.NType == Arrive)
        *event = 'A';
    else
        *event = 'D';
}

void CustomerArrived()                            //处理客户到达事件，gEn.NType=0
{
    int durtime, intertime;
    int cur_LeftTime, suc_ArrivalTime;
    int i;

    ++gCustomerNum;                                //总客户数增一

    Random(&durtime, &intertime);                //生成当前客户办理业务需要的时间和下一个客户达到时间间隔
    cur_LeftTime = gEn.OccurTime + durtime;    //当前客户的离开时间
    suc_ArrivalTime = gEn.OccurTime + intertime;//下一个客户到达时间

    gCustomerRcd.ArrivedTime = gEn.OccurTime;    //记录当前客户信息
    gCustomerRcd.Duration = durtime;
    gCustomerRcd.Count = gCustomerNum;

    i = Minimum(gQ);                            //求长度最短队列
    EnQueue_L(&gQ[i], gCustomerRcd);            //当前客户进入最短队列
    Show();

    if (suc_ArrivalTime < gCloseTime)                //银行尚未关门，将下一客户到达事件插入事件表
    {
        gEn.OccurTime = suc_ArrivalTime;        //gEn的参数已经改变
        gEn.NType = Arrive;
        OrderInsert(gEv, gEn, cmp);
    }

    if (QueueLength_L(gQ[i]) == 1)                    //设定第i队列的队头客户的离开事件并插入事件表
    {
        gEn.OccurTime = cur_LeftTime;
        gEn.NType = i;
        OrderInsert(gEv, gEn, cmp);
    }
}

void CustomerDeparture()                        //处理客户离开事件,gEn.NType>0
{
    int i = gEn.NType;

    DeQueue_L(&gQ[i], &gCustomerRcd);            //删除第i队列的排头客户
    Show();

    gTotalTime += gEn.OccurTime - gCustomerRcd.ArrivedTime;    //累计客户逗留时间

    if (!QueueEmpty_L(gQ[i]))                    //设定第i队列的第一个离开事件并插入事件表
    {
        GetHead_L(gQ[i], &gCustomerRcd);
        gEn.OccurTime += gCustomerRcd.Duration;
        gEn.NType = i;
        OrderInsert(gEv, gEn, cmp);
    }
}

void Invalid() {
    printf("运行错误！");
    exit(OVERFLOW);
}

void CloseForDay() {
    printf("当天总共有%d个客户，平均逗留时间为%d分钟。\n", gCustomerNum, gTotalTime / gCustomerNum);
}

int cmp(Event a, Event b)                    //比较两事件发生次序
{
    if (a.OccurTime < b.OccurTime)                //a晚于b发生
        return -1;
    if (a.OccurTime == b.OccurTime)            //a、b同时发生
        return 0;
    if (a.OccurTime > b.OccurTime)                //a早于b发生
        return 1;
}

void Random(int *durtime, int *intertime) {
    srand((unsigned) time(NULL));
    *durtime = rand() % DurationTime + 1;        //办业务时间持续1到20分钟
    *intertime = rand() % IntervalTime + 1;    //下一个顾客来的时间为间隔1到10分钟
}

Status OrderInsert(EventList gEv, Event gEn, int (cmp)(Event, Event)) {
    int i;
    EventList p, pre, s;

    pre = gEv;
    p = gEv->next;                            //p指向第一个事件

    while (p && cmp(gEn, p->data) == 1)        //查找gEn在事件表中应该插入的位置
    {
        pre = p;
        p = p->next;
    }

    s = (LinkList) malloc(sizeof(LNode));
    if (!s)
        exit(OVERFLOW);

    s->data = gEn;                            //将gEn插入事件表
    s->next = pre->next;
    pre->next = s;

    return OK;
}

int Minimum() {
    int i1 = QueueLength_L(gQ[1]);
    int i2 = QueueLength_L(gQ[2]);
    int i3 = QueueLength_L(gQ[3]);
    int i4 = QueueLength_L(gQ[4]);

    if (i1 <= i2 && i1 <= i3 && i1 <= i4)
        return 1;
    if (i2 < i1 && i2 <= i3 && i2 <= i4)
        return 2;
    if (i3 < i1 && i3 < i2 && i3 <= i4)
        return 3;
    if (i4 < i1 && i4 < i2 && i4 < i3)
        return 4;
}

void Show() {
    int i;
    QueuePtr p;                                //记录到来的客户是第几个

    system("cls");

    for (i = 1; i <= 4; i++) {
        for (p = gQ[i].front; p; p = p->next) {
            if (p == gQ[i].front) {
                if (i == 1)
                    printf("柜台①●");
                if (i == 2)
                    printf("柜台②●");
                if (i == 3)
                    printf("柜台③●");
                if (i == 4)
                    printf("柜台④●");
            } else
                printf("（%03d）", p->data.Count);


            if (p == gQ[i].rear)
                printf("\n");
        }
    }

    Wait(SleepTime);
}

/**
 算法3.7
**/
void Bank_Simulation_2() {
    OpenForDay();                            //初始化

    while (!ListEmpty_L(gEv)) {
        ListDelete_L(gEv, 1, &gEn);

        if (gEn.NType == Arrive)
            CustomerArrived();                //处理客户到达事件
        else
            CustomerDeparture();            //处理客户离开事件
    }

    printf("当天总共有%d个客户，平均逗留时间为%d分钟。\n", gCustomerNum, gTotalTime / gCustomerNum);//计算平均逗留时间
}

#endif //DATA_STRUCTURE_BANKQUEUING_H
