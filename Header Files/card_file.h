//
//  card_file.h
//  解决方案
//
//  Created by tianyu on 2020/3/9.
//  Copyright © 2020 tianyu. All rights reserved.
//

#ifndef card_file_h
#define card_file_h
#include "menu.h"
#include "model.h"
#include "Global.h"
#include "tool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int saveCard(Card* pCard,const char* pPath);
int readCard(Card* pCard,const char* pPath);
int countCard(const char*pPath);
int updateCard(cardNode *pCard,const char *pPath,int nIndex);
void free1(void);
#endif /* card_file_h */
