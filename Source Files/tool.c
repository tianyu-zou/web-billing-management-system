//
//  tool.c
//  解决方案
//
//  Created by tianyu on 2020/3/22.
//  Copyright © 2020 tianyu. All rights reserved.
//

#include "tool.h"

void timeToString(time_t t,char *pBuf)
{
    //char aTime[20] = {0};
    struct tm*p = localtime(&t);
    strftime(pBuf, 20," %Y-%m-%d %H:%M", p);
}

time_t stringToTime(char* pTime)
{
    struct tm tm1;
    time_t time1;
    sscanf(pTime, "%d-%d-%d %d:%d",&tm1.tm_year,&tm1.tm_mon,&tm1.tm_mday,&tm1.tm_hour,&tm1.tm_min);
    tm1.tm_year -=1900;
    tm1.tm_mon -=1;
    time1 = mktime(&tm1);
    return time1;
}

