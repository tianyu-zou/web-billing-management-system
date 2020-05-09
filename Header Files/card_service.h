//
//  card_service.h
//  解决方案
//
//  Created by tianyu on 2020/3/9.
//  Copyright © 2020 tianyu. All rights reserved.
//
//#include "model.h"
#include <stdlib.h>
#include <stdio.h>
#include "model.h"
#include "card_file.h"
#include "billing_file.h"
#include "money_file.h"
#ifndef card_service_h
#define card_service_h
int getSize(char*p,int n);
int initCardList(void);
int addCard(int o);
static lpCardNode cardList = NULL;//全局卡链表
Card queryCard(char *pName);
int getCard(void);
Card* queryCards(char *pName);

Card* doLogon(char *aName,char *aPsd,LogonInfo* pInfo);//卡上机实现函数

int doSettle(char *aName,char *aPsd,SettleInfo* pInfo);//卡下机实现函数
int doAddMoney(char *aName,char *aPsd);//卡充值
int doRefundMoney(char *aName,char *aPsd);//卡退费
int annulCard(char *aName,char *aPsd);//卡注销
int doQurryStatic(char *aName,char *aPsd);//查询统计
#endif
