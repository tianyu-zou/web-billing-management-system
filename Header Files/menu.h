//
//  menu.h
//  解决方案
//
//  Created by tianyu on 2020/3/9.
//  Copyright © 2020 tianyu. All rights reserved.
//

#ifndef menu_h
#define menu_h
#include "model.h"
#include <stdio.h>

void add(void);//声明添加卡函数
void outputMenu(void);//声明输出菜单函数
Card query(char *pName);//声明查询卡函数
void exitApp(void);//声明退出应用程序函数
void logon(void);//卡上机函数
void settle(void);//卡上机函数
void addMoney(void);//卡充值
void refundMoney(void);//卡退费
void annul(void);//卡注销
void qurryStatic(void);
#endif /* menu_h */
