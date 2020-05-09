//
//  money_file.c
//  解决方案
//
//  Created by tianyu on 2020/4/20.
//  Copyright © 2020 tianyu. All rights reserved.
//

#include "money_file.h"

int saveMoney(Money *pMoney,const char* pPath)
{
    FILE *fp;
    //打开文件
    if ((fp = fopen(pPath, "ab"))==NULL)
    {
        printf("打开文件失败");
        return FALSE;
    }
    //写入文件
    fwrite(pMoney, sizeof(Money), 1, fp);
    //关闭文件
    fclose(fp);
    return TRUE;
}
