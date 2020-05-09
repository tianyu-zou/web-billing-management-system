//
//  card_service.c
//  解决方案
//
//  Created by tianyu on 2020/3/9.
//  Copyright © 2020 tianyu. All rights reserved.
//

#include "card_service.h"
#include <string.h>
#include "tool.h"
#include "billing_file.h"

int getCard(void);
lpCardNode head = NULL;//头结点
Card card;//卡的信息结构体
int initCardList()
{
    head = (lpCardNode)malloc(sizeof(cardNode));
    if (!head)
    {
        head->next = NULL;
        cardList = head;
        return 1;
    }
    return 0;
}
//(1)利用尾插法添加信息
//(2)将信息添加到文件中
//(3)将信息保存到二进制文件中
int addCard(int o)
{
    //提示用户输出卡的信息
    printf("请输入卡号:");
    scanf("%s",card.aName);
    while(getSize(card.aName,18)==0)
    {
        printf("请输入长度小于18的用户名:");
        scanf("%s",card.aName);
    }
    printf("请输入密码:");
    scanf("%s",card.aPwd);
    while(getSize(card.aPwd,8)==0)
    {
        printf("请输入长度小于8的密码:");
        scanf("%s",card.aPwd);
    }
    printf("请选择充值金额:");
    scanf("%f",&card.fTotaUse);
    //对一些数据进行赋值
    card.nDel = 0;
    card.nStatus = 0;
    card.nUseCount = 0;
    card.fBalance = card.fTotaUse;
    card.tStart = card.tLastTime=card.tEnd = time(NULL);
    //输出添加卡信息
    printf("------添加卡的信息如下------\n");
    printf("卡号\t\t\t密码\t\t\t状态\t\t\t开卡金额\n");
    printf("%-10s\t%-10s\t%-10d\t%-10.1lf\n",card.aName,card.aPwd,card.nStatus,card.fTotaUse);
    const char* pPath= "/Users/tianyu/Desktop/寒假/计算机基础与编程实验/计费管理系统/解决方案/data/card.ams";
    if (TRUE==saveCard(&card, pPath))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//释放卡链表的空间
void releaseCardList()
{
    lpCardNode p;//遍历链表的辅助指针
    p = cardList;//对辅助指针赋值
    while (p->next!=NULL)
    {
        p = p->next;//遍历链表找到末尾指针
        free(p);
    }
    
}


void printCardList()
{
    lpCardNode p;//遍历链表的辅助指针
    p = cardList;//对辅助指针赋值
    while (p->next!=NULL)
    {
        p = p->next;//遍历链表找到末尾指针
        //printCard(p->data);
    }
}

int getSize(char*p,int n)
{
    if(strlen(p)<n)
        return 1;
    return 0;
}

//准确查找卡的信息
Card queryCard(char *pName)
{
    if(cardList==NULL)
    {
        cardList = (cardNode*)malloc(sizeof(cardNode));
        cardList->next = NULL;
    }
    getCard();
    lpCardNode p;
    p = cardList;
    while (p!=NULL)
    {
        if(strcmp(p->data.aName,pName)==0)
        {
            printf("卡号\t\t\t密码\t\t\t状态\t\t\t开卡金额\t  使用次数\t\t上次使用时间\n");
            char pBuf[20];
            timeToString(p->data.tLastTime, pBuf);
            printf("%-10s\t%-10s\t%-10d\t%-10.1lf%-10d%-10s\n",p->data.aName,p->data.aPwd,p->data.nStatus,p->data.fTotaUse,p->data.nUseCount,pBuf);
           return p->data;
        }
        p = p->next;
    }
    printf("没有此用户\n");
    return card;
}

//模糊查找卡的信息
Card* queryCards(char *pName)
{
    //初始化链表
    Card *pcard = NULL;
    //if(cardList==NULL)
    {
        cardList = (cardNode*)malloc(sizeof(cardNode));
        cardList->next = NULL;
    }
    //将卡信息保存到链表中
    getCard();
    //辅助卡结点
    lpCardNode p;
    //从头开始遍历链表
    p = cardList;
    int count = 0;
    free(pcard);
    printf("-----查询卡信息如下-----\n");
    while (p->next!=NULL)
    {
        //找到卡信息
        if(strstr(p->data.aName,pName)!=0)
        {
            //输出卡信息
            printf("卡号\t\t\t密码\t\t\t状态\t\t\t开卡金额\t  使用次数\t\t上次使用时间\t\t卡余额\n");
            char pBuf[20];
            timeToString(p->data.tLastTime, pBuf);
            printf("%-10s\t%-10s\t%-10d\t%-10.1lf%-10d%-10s\t%.1f\n",p->data.aName,p->data.aPwd,p->data.nStatus,p->data.fTotaUse,p->data.nUseCount,pBuf,p->data.fBalance);
            count++;
            pcard = (Card*)malloc(sizeof(Card)*count);
            pcard[count-1] = p->data;
        }
        p = p->next;
    }
    //未找到卡信息
    if (count == 0)
    {
        printf("没有此用户\n");
    }
    return pcard;
}
//从文件中获取卡的信息转化为链表
int getCard()
{
    const char* pPath= "/Users/tianyu/Desktop/寒假/计算机基础与编程实验/计费管理系统/解决方案/data/card.ams";
    int nCount = 0;
    //获取卡信息数量
    nCount = countCard(pPath);
    //初始化链表
    Card* pCard = NULL;
    pCard = (Card*)malloc(sizeof(card)*nCount);
    if (pCard == NULL)
    {
        return FALSE;//分配链表空间失败
    }
    //获取卡信息
    if (readCard(pCard, pPath)==FALSE)
    {
        free(pCard);
        pCard = NULL;
        return FALSE;//读取卡信息失败
    }
    //将卡信息保存到链表中
    for(int i = 0;i<nCount;i++)
    {
        lpCardNode add = (lpCardNode)malloc(sizeof(cardNode));//添加的新节点
        add->data=pCard[i];
        lpCardNode p;//遍历链表的辅助指针
        p = cardList;//对辅助指针赋值
        while (p->next!=NULL)
        {
           p = p->next;//遍历链表找到末尾指针
        }
        p->next = add;//将新节点添加到末尾指针后
        add->next = NULL;
    }
    return TRUE;
}
//卡上机
Card* doLogon(char *aName,char *aPsd,LogonInfo* pInfo)
{
    int nLine = 0;
    //定义cardList链表
    //if(cardList==NULL)
    free(cardList);
    {
        cardList = (cardNode*)malloc(sizeof(cardNode));
        cardList->next = NULL;
    }
    //获取卡信息失败
    if (getCard()==FALSE)
    {
        printf("卡信息读取失败!\n");
        exit(0);
    }
    //获取卡信息成功
    lpCardNode p;
    p = cardList;
    while (p->next!=NULL)
    {
        //找到卡信息后对卡的状态进行判断
        if((strcmp(aName, p->data.aName)==0)&&(strcmp(aPsd, p->data.aPwd)==0))
        {
            if (p->data.nStatus!=0)
            {
                printf("该卡正在使用或已经注销!\n");
                return 0;
            }
            if (p->data.fBalance<=0)
            {
                printf("余额不足!\n");
                return 0;
            }
            Billing* pBilling = (Billing*)malloc(sizeof(Billing));
            //更新链表中的卡信息
            p->data.nStatus = 1;//正在使用
            p->data.nUseCount++;//卡使用次数增加
            p->data.tLastTime = time(NULL);//最后使用时间改变
            //输出上机卡信息
            char s[20];
            timeToString(p->data.tLastTime, s);
            printf("-----上机信息如下-----\n");
            printf("上机成功!\n");
            printf("卡号\t\t余额\t\t上机时间\t\n");
        printf("%s\t%.1f\t%s\n",p->data.aName,p->data.fBalance,s);
            //更新卡文件
            const char* pPath= "/Users/tianyu/Desktop/寒假/计算机基础与编程实验/计费管理系统/解决方案/data/card.ams";
            updateCard(cardList, pPath, nLine);
            if (FALSE == addBilling(pBilling, p->data.aName))
            {
                printf("消费记录添加失败!\n");
                exit(0);
            }
            else{
                strcpy(pInfo->aCardName, p->data.aName);
                pInfo->fBalance = p->data.fBalance;
                pInfo->tLogon = pBilling->tStart;
                free(pBilling);
            }
            return &p->data;//返回查找到的卡
        }
        p = p->next;
        nLine++;
    }
    printf("账户或密码错误!\n");//账号密码错误提示
    return 0;
}


//卡下机
int doSettle(char *aName,char *aPsd,SettleInfo* pInfo)
{
    int nLine = 0;
    //定义cardList链表
    //if(cardList==NULL)
    free(cardList);
    {
        cardList = (cardNode*)malloc(sizeof(cardNode));
        cardList->next = NULL;
    }
    //获取卡信息失败
    if (getCard()==FALSE)
    {
        printf("卡信息读取失败!\n");
        exit(0);
    }
    //获取卡信息成功
    lpCardNode p;
    p = cardList;
    while (p->next!=NULL)
    {
        if((strcmp(aName, p->data.aName)==0)&&(strcmp(aPsd, p->data.aPwd)==0))
        {
            if (p->data.nStatus!=1)
            {
                printf("该卡未被使用或已经注销!\n");
                return 0;
            }
            if (p->data.fBalance<=0)
            {
                printf("余额不足!\n");
                return 0;
            }
            Billing* pBilling = (Billing*)malloc(sizeof(Billing));
            //更新链表中的卡信息
            p->data.nStatus = 0;//已经下机
            //p->data.nUseCount++;//卡使用次数不变
            //输出下机卡信息
            char s[20];
            timeToString(p->data.tLastTime, s);
            double sum = 0;
            sum = getMoney(p->data.tLastTime);
            p->data.tLastTime = time(NULL);//最后使用时间改变
            char q[20];
            timeToString(p->data.tLastTime, q);
            p->data.fBalance-=sum;
            printf("-----下机信息如下-----\n");
            printf("下机成功!\n");
            printf("卡号\t\t消费\t余额\t\t上机时间\t\t\t\t下机时间\n");
            printf("%s\t%.1lf\t%.1f\t%s\t%s\n",p->data.aName,sum,p->data.fBalance,s,q);
            //更新卡文件
            const char* pPath= "/Users/tianyu/Desktop/寒假/计算机基础与编程实验/计费管理系统/解决方案/data/card.ams";
            //更新文件中的卡信息
            if(FALSE == updateCard(cardList, pPath, nLine))
            {
                printf("卡信息修改失败!\n");
                return FALSE;
            }
            strcpy(pBilling->aCardName, p->data.aName);
            pBilling->fAmount = sum;
            //更新消费信息的文件
            if (FALSE == saveBilling(pBilling,BILLINGPATH))
            {
                printf("消费记录添加失败!\n");
                return FALSE;
            }
            else{
                strcpy(pInfo->aCardName, p->data.aName);
                pInfo->fBalance = p->data.fBalance;
                pInfo->tEnd = time(NULL);
                free(pBilling);
            }
            return TRUE;//返回成功
        }
        p = p->next;
        nLine++;
    }
    printf("账户或密码错误!\n");//账号密码错误提示
    return 0;
}

//卡充值
int doAddMoney(char *aName,char *aPsd)
{
    int nLine = 0;
    //定义cardList链表
    //if(cardList==NULL)
    free(cardList);
    {
        cardList = (cardNode*)malloc(sizeof(cardNode));
        cardList->next = NULL;
    }
    //获取卡信息失败
    if (getCard()==FALSE)
    {
        printf("卡信息读取失败!\n");
        exit(0);
    }
    //获取卡信息成功
    lpCardNode p;
    p = cardList;
    while (p->next!=NULL)
    {
        if((strcmp(aName, p->data.aName)==0)&&(strcmp(aPsd, p->data.aPwd)==0))
        {
            if (p->data.nStatus==2)
            {
                printf("该卡已经注销!\n");
                return 0;
            }
            printf("请输入充值金额:");
            float addSum;
            scanf("%f",&addSum);
            //更新链表中的卡信息
            p->data.fBalance+=addSum;
            p->data.fTotaUse+=addSum;
            //p->data.nUseCount++;//卡使用次数不变
            //输出充值卡信息
            char s[20];
            timeToString(p->data.tLastTime, s);
            char q[20];
            timeToString(p->data.tLastTime, q);
            printf("-----充值信息如下-----\n");
            printf("充值成功!\n");
            printf("卡号\t\t充值金额\t\t余额\n");
            printf("%s\t%.1lf\t%.1f\n",p->data.aName,addSum,p->data.fBalance);
            //更新卡文件
            const char* pPath= "/Users/tianyu/Desktop/寒假/计算机基础与编程实验/计费管理系统/解决方案/data/card.ams";
            //更新文件中的卡信息
            if(FALSE == updateCard(cardList, pPath, nLine))
            {
                printf("卡信息修改失败!\n");
                return FALSE;
            }
            //将充值信息保存到充值结构体中
            Money sMoney;
            strcpy(sMoney.aCardName, aName);
            sMoney.fMoney = addSum;
            sMoney.nDel = 0;
            sMoney.nStatus = 0;
            sMoney.tTime = time(NULL);
            if(saveMoney(&sMoney, MONEYPATH)==FALSE)
            {
                printf("充值信息添加失败");
                return FALSE;
            };
            return TRUE;//返回成功
        }
        p = p->next;
        nLine++;
    }
    printf("账户或密码错误!\n");//账号密码错误提示
    return 0;
}

//卡退费
int doRefundMoney(char *aName,char *aPsd)
{
    int nLine = 0;
    //定义cardList链表
    //if(cardList==NULL)
    free(cardList);
    {
        cardList = (cardNode*)malloc(sizeof(cardNode));
        cardList->next = NULL;
    }
    //获取卡信息失败
    if (getCard()==FALSE)
    {
        printf("卡信息读取失败!\n");
        exit(0);
    }
    //获取卡信息成功
    lpCardNode p;
    p = cardList;
    while (p->next!=NULL)
    {
        if((strcmp(aName, p->data.aName)==0)&&(strcmp(aPsd, p->data.aPwd)==0))
        {
            if (p->data.nStatus!=0)
            {
                printf("该卡不能退费!\n");
                return 0;
            }
            if(p->data.fBalance<=0)
            {
                printf("余额不足!\n");
                return 0;
            }
            float refundSum;
            //更新链表中的卡信息
            refundSum = p->data.fBalance;
            p->data.fBalance = 0;
            p->data.fTotaUse-=refundSum;
            //p->data.nUseCount++;//卡使用次数不变
            //输出下机卡信息
            char s[20];
            timeToString(p->data.tLastTime, s);
            char q[20];
            timeToString(p->data.tLastTime, q);
            printf("-----退费信息如下-----\n");
            printf("退费成功!\n");
            printf("卡号\t\t退费金额\t余额\n");
            printf("%s\t%.1lf\t%.1f\n",p->data.aName,refundSum,p->data.fBalance);
            //更新卡文件
            const char* pPath= "/Users/tianyu/Desktop/寒假/计算机基础与编程实验/计费管理系统/解决方案/data/card.ams";
            //更新文件中的卡信息
            if(FALSE == updateCard(cardList, pPath, nLine))
            {
                printf("卡信息修改失败!\n");
                return FALSE;
            }
            //将充值信息保存到充值结构体中
            Money sMoney;
            strcpy(sMoney.aCardName, aName);
            sMoney.fMoney = refundSum;
            sMoney.nDel = 0;
            sMoney.nStatus = 1;
            sMoney.tTime = time(NULL);
            if(saveMoney(&sMoney, MONEYPATH)==FALSE)
            {
                printf("退费信息添加失败");
                return FALSE;
            };
            return TRUE;//返回成功
        }
        p = p->next;
        nLine++;
    }
    printf("账户或密码错误!\n");//账号密码错误提示
    return 0;
}

//卡注销
int annulCard(char *aName,char *aPsd)
{
    int nLine = 0;
    //定义cardList链表
    free(cardList);
    {
        cardList = (cardNode*)malloc(sizeof(cardNode));
        cardList->next = NULL;
    }
    //获取卡信息失败
    if (getCard()==FALSE)
    {
        printf("卡信息读取失败!\n");
        exit(0);
    }
    //获取卡信息成功
    lpCardNode p;
    p = cardList;
    while (p->next!=NULL)
    {
        if((strcmp(aName, p->data.aName)==0)&&(strcmp(aPsd, p->data.aPwd)==0))
        {
            if (p->data.nStatus!=0)
            {
                printf("该卡不能注销!\n");
                return 0;
            }
            float refundSum;
            //更新链表中的卡信息
            refundSum = p->data.fBalance;
            p->data.fBalance = 0;
            p->data.fTotaUse-=refundSum;
            p->data.nStatus = 2;//将卡的状态改为注销
            //输出注销卡信息
            char s[20];
            timeToString(p->data.tLastTime, s);
            char q[20];
            timeToString(p->data.tLastTime, q);
            printf("-----注销信息如下-----\n");
            printf("注销成功!\n");
            printf("卡号\t\t退费金额\n");
            printf("%s\t%.1lf\n",p->data.aName,refundSum);
            //更新卡文件
            const char* pPath= "/Users/tianyu/Desktop/寒假/计算机基础与编程实验/计费管理系统/解决方案/data/card.ams";
            //更新文件中的卡信息
            if(FALSE == updateCard(cardList, pPath, nLine))
            {
                printf("卡信息修改失败!\n");
                return FALSE;
            }
            return TRUE;//返回成功
        }
        p = p->next;
        nLine++;
    }
    printf("账户或密码错误!\n");//账号密码错误提示
    return 0;
}

//查询统计
int doQurryStatic(char *aName,char *aPsd)
{
    char a[18] = "admin";
    char a1[8] = "12345";
    //定义billingList链表
    Billing billingList[100];
    for (int i = 0;i<20;i++)
    {
        billingList[i].fAmount = 0;
    }
    //获取消费信息失败
    if (readBilling(billingList,BILLINGPATH )==FALSE)
    {
        printf("消费信息读取失败!\n");
        exit(0);
    }
    //获取消费信息成功
    //以管理员身份登陆
    double sum = 0;
    if((strcmp(aName, a) ==0)&&(strcmp(aPsd, a1)==0))
    {
        int i = 0;
        while (billingList[i].fAmount != 0)
        {
            sum+=billingList[i].fAmount;
            i++;
        }
        printf("营业额为:%.2f\n",sum);
    }
    else
    {
        printf("请输入管理员账号密码\n");
    }
    
    return TRUE;
}
