//
//  main.c
//  Single Cycle Linked List
//
//  Created by miaokii on 2020/4/13.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "oneWayCycleLinkList.h"

int main(int argc, const char * argv[]) {
    
    LinkList L;
    printf("创建L，以0作为结尾：");
    OneWayCycLinkListInit(&L);
    printf("L：");
    ListPrint(L);
    
    int i = 5;
    printf("在L第%d个位置插入%d：\n", i, i);
    InsertList(&L, i, i);
    ListPrint(L);
    
    i = 10;
    ElemType d;
    DeleteList(&L, i, &d);
    printf("在L第%d个位置删除%d：\n", i, d);
    ListPrint(L);
    
    i = 4;
    FindList(L, i, &d);
    printf("查找L第%d个节点%d：\n", i, d);
    ListPrint(L);
    
    int val;
    i = -1;
    printf("输入查找的值：\n");
    scanf("%d", &val);
    FindIndex(L, &i, val);
    printf("查找%d在L中的位置(-1未找到)：%d\n", val, i);
    
    return 0;
}
