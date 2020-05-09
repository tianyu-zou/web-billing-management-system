//
//  main.c
//  解决方案
//
//  Created by tianyu on 2020/3/9.
//  Copyright © 2020 tianyu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "menu.h"//调用主菜单文件
#include "model.h"//调用程序中自定义的数据类型
#include "card_service.h"//调用卡的相关功
int main(int argc, const char * argv[]) {
    printf("欢迎进入计费管理系统\n");
    int kill = 0;
    int nSelection = -1;//进行操作的变量
    while (nSelection) {
        outputMenu();//调用输出菜单函数
        scanf("%d",&nSelection);
        switch (nSelection) {
            case 0:
            {
                return 0;
                break;
            }
            case 1:
            {
                printf("-----添加卡-----\n");
                addCard(kill);
                kill++;
                break;
            }
            case 2:
            {
                printf("-----查询卡-----\n");
                char pName[18];
                Card *cardFind;
                printf("请输入需要查找的用户名:");
                scanf("%s",pName);
                cardFind = queryCards(pName);
                break;
            }
            case 3:
            {
                printf("-----卡上机-----\n");
                logon();
                break;
            }
            case 4:
            {
                printf("-----卡下机-----\n");
                settle();
                break;
            }
            case 5:
            {
                printf("-----卡充值-----\n");
                addMoney();
                break;
            }
            case 6:
            {
                printf("-----卡退费-----\n");
                refundMoney();
                break;
            }
                case 7:
            {
                printf("-----查询统计-----\n");
                qurryStatic();
                break;
            }
            case 8:
            {
                printf("-----卡注销-----\n");
                annul();
                break;
            }
            default:
            {
                printf("您输入的编号有误\n");
                break;
            }
        }
    }
    
    return 0;
}
