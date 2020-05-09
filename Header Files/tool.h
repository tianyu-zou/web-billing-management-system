//
//  tool.h
//  解决方案
//
//  Created by tianyu on 2020/3/22.
//  Copyright © 2020 tianyu. All rights reserved.
//

#ifndef tool_h
#define tool_h

#include <stdio.h>
#include <time.h>
#include "model.h"
#include <string.h>
void timeToString(time_t time,char *pBuf);//声明转换为输出的时间形式
time_t stringToTime(char*pTime);//声明c转换为保存的时间形式
#endif /* tool_h */
