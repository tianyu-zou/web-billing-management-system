//
//  menu.c
//  解决方案
//
//  Created by tianyu on 2020/3/9.
//  Copyright © 2020 tianyu. All rights reserved.
//

#include "menu.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"
#include "card_service.h"
//菜单
void outputMenu()
{
    printf("--------菜单--------\n");
    printf("1、添加卡\n");
    printf("2、查询卡\n");
    printf("3、上机\n");
    printf("4、下机\n");
    printf("5、充值\n");
    printf("6、退费\n");
    printf("7、查询统计\n");
    printf("8、注销卡\n");
    printf("0、退出\n");
    printf("请输入您需要进行的操作:");
}

//卡上机
void logon()
{
    char aName[18];//上机卡账号
    char aPsd[8];//上机卡密码
    Card *aCard;//上机卡
    //int nReasult = 0;
    LogonInfo* pInfo = (LogonInfo*)malloc(sizeof(LogonInfo));
    //用户输入账号和密码
    do
    {
        if (strlen(aPsd)>1)
        {
            printf("您的账号密码格式错误请重新输入\n");
        }
        printf("请您输入账号:");
        scanf("%s",aName);
        printf("请您输入密码:");
        scanf("%s",aPsd);
        //利用getSize函数判断账号密码的格式正确与否
    }while ((getSize(aName, 18)&&getSize(aPsd, 8))==0);
    
    //开始上机获取上机结果
    aCard = doLogon(aName,aPsd,pInfo);
    
}

//卡下机
void settle()
{
    char aName[18];//下机卡账号
    char aPsd[8];//下机卡密码
    //int nReasult = 0;
    SettleInfo* pInfo = (SettleInfo*)malloc(sizeof(SettleInfo));
    //用户输入账号和密码
    do
    {
        if (strlen(aPsd)>1)
        {
            printf("您的账号密码格式错误请重新输入\n");
        }
        printf("请您输入账号:");
        scanf("%s",aName);
        printf("请您输入密码:");
        scanf("%s",aPsd);
        //利用getSize函数判断账号密码的格式正确与否
    }while ((getSize(aName, 18)&&getSize(aPsd, 8))==0);
    
    //开始下机,获取下机结果
    doSettle(aName,aPsd,pInfo);
}

//卡充值
void addMoney()
{
    char aName[18];//充值卡账号
    char aPsd[8];//充值卡密码
    //用户输入账号和密码
    do
    {
        if (strlen(aPsd)>1)
        {
            printf("您的账号密码格式错误请重新输入\n");
        }
        printf("请您输入账号:");
        scanf("%s",aName);
        printf("请您输入密码:");
        scanf("%s",aPsd);
        //利用getSize函数判断账号密码的格式正确与否
    }while ((getSize(aName, 18)&&getSize(aPsd, 8))==0);
    
    //开始充值,获取充值结果
    doAddMoney(aName, aPsd);
}

//卡退费
void refundMoney()
{
    char aName[18];//退费卡账号
    char aPsd[8];//退费卡密码
    //用户输入账号和密码
    do
    {
        if (strlen(aPsd)>1)
        {
            printf("您的账号密码格式错误请重新输入\n");
        }
        printf("请您输入账号:");
        scanf("%s",aName);
        printf("请您输入密码:");
        scanf("%s",aPsd);
        //利用getSize函数判断账号密码的格式正确与否
    }while ((getSize(aName, 18)&&getSize(aPsd, 8))==0);
    
    //开始退费,获取退费结果
    doRefundMoney(aName, aPsd);
}

//卡注销
void annul()
{
    char aName[18];//注销卡账号
    char aPsd[8];//注销卡密码
    //用户输入账号和密码
    do
    {
        if (strlen(aPsd)>1)
        {
            printf("您的账号密码格式错误请重新输入\n");
        }
        printf("请您输入账号:");
        scanf("%s",aName);
        printf("请您输入密码:");
        scanf("%s",aPsd);
        //利用getSize函数判断账号密码的格式正确与否
    }while ((getSize(aName, 18)&&getSize(aPsd, 8))==0);
    
    //开始注销,获取注销结果
    annulCard(aName, aPsd);
}

//查询统计
void qurryStatic()
{
    char aName[18];//注销卡账号
    char aPsd[8];//注销卡密码
    //用户输入账号和密码
    do
    {
        if (strlen(aPsd)>1)
        {
            printf("您的账号密码格式错误请重新输入\n");
        }
        printf("请您输入账号:");
        scanf("%s",aName);
        printf("请您输入密码:");
        scanf("%s",aPsd);
        //利用getSize函数判断账号密码的格式正确与否
    }while ((getSize(aName, 18)&&getSize(aPsd, 8))==0);
    
    //开始注销,获取注销结果
    doQurryStatic(aName, aPsd);
}

