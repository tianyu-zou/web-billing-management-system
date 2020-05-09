//
//  card_file.c
//  解决方案
//
//  Created by tianyu on 2020/3/9.
//  Copyright © 2020 tianyu. All rights reserved.
//

#include "card_file.h"
#include <stdlib.h>
int saveCard(Card* pCard,const char* pPath)
{
    FILE*fp = NULL;
    //打开文件
    if((fp = fopen(pPath, "ab"))==NULL)
    {
        return FALSE;//打开文件失败
    }
    //将过期时间设置为一年后
    struct tm*start;
    struct tm*end;
    start = localtime(&pCard->tStart);
    end = localtime(&pCard->tEnd);
    //将截止时间增加一年
    end->tm_year = start->tm_year+1;
    pCard->tEnd = mktime(end);
    //将卡结构体存储到二进制文件中
    fwrite(pCard, sizeof(Card), 1, fp);
    //关闭文件
    fclose(fp);
    //返回成功
    return TRUE;
}
//获取卡信息
int readCard(Card* pCard,const char* pPath)
{
    FILE* fp = NULL;
    // 以只读的方式打开文件
    if((fp = fopen(pPath, "rb")) == NULL)
    {
        //打开失败
        printf("打开文件失败\n");
        return FALSE;
    }
    int i = 0;//卡的位置
    while (!feof(fp))
    {
        //将卡信息从文件中读入卡结构体中
        fread(&pCard[i], sizeof(Card), 1, fp);
        i++;
    }
    //关闭文件
    fclose(fp);
    //返回成功
    return TRUE;
}

//获取卡的数量
int countCard(const char*pPath)
{
    FILE* fp = NULL;
    // 以只读的方式打开文件
    if((fp = fopen(pPath, "rb")) == NULL)
    {
        return FALSE;
    }
    Card pcard;
    int ncount = 0;//卡的数量
    while (!feof(fp))
    {
        fread(&pcard, sizeof(Card), 1, fp);
        ncount++;
    }
    fclose(fp);
    return ncount;
}

//清空
void free1()
{
    FILE* fp = NULL;
    //打开文件
    fp = fopen(CARDPATH, "wb");
    fclose(fp);
}
//更新卡信息
int updateCard(cardNode *pCard,const char *pPath,int nIndex)
{
    free1();
    FILE* fp = NULL;
    //打开文件
    fp = fopen(pPath, "wb");
    if(fp == NULL)
    {
        return FALSE;//打开文件失败
    }
    //遍历文件
    //移到文件标示位置
    //fseek(fp, lPosition, 0);
    pCard = pCard->next;
    while (pCard->next!=NULL)
    {
        fwrite(pCard, sizeof(Card), 1, fp);
        pCard = pCard->next;
    }
    //关闭文件
    fclose(fp);
    return TRUE;
}
