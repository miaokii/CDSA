//
//  main.c
//  Linked list
//
//  Created by miaokii on 2020/4/10.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "链表.h"
#include "顺序表.h"

typedef int Status;
typedef int ElemType;


int main(int argc, const char * argv[]) {
    LinkList L;
    Status iStatus;
    iStatus = InitList(&L);
    printf("L 是否初始化成功?（0：失败,1：成功）： %d\n",iStatus);
    
    for (int i = 1; i <= 8; i++) {
        ListInsert(&L, i, i);
    }
    printf("L 插入后：");
    ListPrint(L);
    
    int i = 8;
    ElemType e;
    GetElem(L, i, &e);
    printf("L 第%d个节点值：%d\n", i, e);
    
    int j = 10;
    ElemType e1;
    ListDelete(&L, j, &e1);
    printf("L 删除第%d个节点，该节点值为：%d，删除后L：", j, e1);
    ListPrint(L);
    
    ListClear(&L);
    printf("L 删除所有节点，删除后L：");
    ListPrint(L);
    
    ListCreateHead(&L, 10);
    printf("前插法创建L随机链表：");
    ListPrint(L);
    
    ListClear(&L);
    
    ListCreateTail(&L, 10);
    printf("尾插法创建L随机链表：");
    ListPrint(L);
    
    return 0;
}
