//
//  billing_file.h
//  解决方案
//
//  Created by tianyu on 2020/4/6.
//  Copyright © 2020 tianyu. All rights reserved.
//

#ifndef billing_file_h
#define billing_file_h
#include "Global.h"
#include "model.h"
#include "tool.h"
#include <stdio.h>
#include <string.h>
#include "Global.h"
int saveBilling(const Billing* pBilling,const char* pPath);
int addBilling(Billing* pBilling,const char* pName);
int updateBilling(const Billing* pBilling,const char* pPath,int nIndex);
int readBilling(Billing* pBilling,const char* pPath);
int countBilling(const char*pPath);
double getMoney(time_t tStart);
#endif /* billing_file_h */
