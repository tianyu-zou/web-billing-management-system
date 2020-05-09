//
//  billing_file.c
//  解决方案
//
//  Created by tianyu on 2020/4/6.
//  Copyright © 2020 tianyu. All rights reserved.
//

#include "billing_file.h"

int saveBilling(const Billing* pBilling,const char* pPath)
{
    FILE* fp;
    //打开文件
    if((fp = fopen(pPath, "ab"))==NULL)
    {
        printf("打开文件失败!\n");
        return FALSE;
    }
    //将计费信息保存到文件中
    fwrite(pBilling, sizeof(Billing), 1, fp);
    //关闭文件
    fclose(fp);
    return TRUE;
}
int readBilling(Billing* pBilling,const char* pPath)
{
    FILE* fp = NULL;
    Billing a ;
    // 以只读的方式打开文件
    if((fp = fopen(pPath, "rb")) == NULL)
    {
        return FALSE;
    }
    int i = 0;//卡的位置
    while(!feof(fp))
    {
        if((fread(&a, sizeof(Billing), 1, fp))!= FALSE)
        {
            
            pBilling[i] = a;
            i++;
        }
    }
    fclose(fp);
    return TRUE;
}
int countBilling(const char* pPath)
{
    FILE* fp = NULL;
    Billing *a = NULL;
    // 以只读的方式打开文件
    if((fp = fopen(pPath, "rb")) == NULL)
    {
        return FALSE;
    }
    int i = 0;//卡的位置
    while(!feof(fp))
    {
        
        if((fread(a, sizeof(Billing), 1, fp))!= FALSE)
        {
            i++;
        }
    }
    fclose(fp);
    return i;
}
int addBilling(Billing* pBilling,const char* pName)
{
    const char* pPath = "/Users/tianyu/Desktop/寒假/计算机基础与编程实验/计费管理系统/解决方案/data/billing.ams ";
    strcpy(pBilling->aCardName, pName);
    if (FALSE==saveBilling(pBilling, pPath))
    {
        printf("添加失败!\n");
        return FALSE;
    }
    return TRUE;
}

int updateBilling(const Billing* pBilling,const char* pName,int nIndex)
{
    const char* pPath = "/Users/tianyu/Desktop/寒假/计算机基础与编程实验/计费管理系统/解决方案/data/billing.ams ";
     FILE* fp = NULL;
       //打开文件
       fp = fopen(pPath, "ab+");
       if(fp == NULL)
       {
           printf("打开失败\n");
           return FALSE;//打开文件失败
           
       }
       //将数据写入文件
       fwrite(pBilling, sizeof(Billing), 1, fp);
       //关闭文件
       fclose(fp);
       return TRUE;
}

double getMoney(time_t tStart)
{
    double sum;
    char a[20];
    //计算使用时间
    timeToString(tStart, a);
    struct tm tm1;
    sscanf(a, "%d-%d-%d %d:%d",&tm1.tm_year,&tm1.tm_mon,&tm1.tm_mday,&tm1.tm_hour,&tm1.tm_min);
    struct tm tm2;
    time_t now;
    now = time(NULL);
    timeToString(now, a);
    sscanf(a, "%d-%d-%d %d:%d",&tm2.tm_year,&tm2.tm_mon,&tm2.tm_mday,&tm2.tm_hour,&tm2.tm_min);
    //根据定价计算费用
    sum = (((tm2.tm_mday-tm1.tm_mday)*24+tm2.tm_hour-tm1.tm_hour)*60+tm2.tm_min-tm1.tm_min)/UNIT*CHARGE;
    //如果不满15分钟则算15分钟
    if (sum==0)
    {
        sum = 0.5;
    }
    return sum;
}
