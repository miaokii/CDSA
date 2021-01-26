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
#include "linkList.h"
#include "seqlist.h"

#include "LinkListTest.h"

void linkListHandle() {
    LinkList L;
    Status iStatus;
    
    iStatus = InitLinkList(&L);
    printf("L 是否初始化成功?（0：失败,1：成功）： %d\n",iStatus);
    
    for (int i = 1; i <= 8; i++) {
        LinkListInsert(&L, i, i);
    }
    printf("L 插入后：");
    LinkListPrint(L);
    
    int i = 8;
    ElemType e;
    LinkListGetElem(L, i, &e);
    printf("L 第%d个节点值：%d\n", i, e);
    
    i = 2;
    ElemType e1;
    LinkListDelete(&L, i, &e1);
    printf("L 删除第%d个节点，该节点值为：%d，删除后L：", i, e1);
    LinkListPrint(L);
    
    LinkListClear(&L);
    printf("L 删除所有节点，删除后L：");
    LinkListPrint(L);
    
    LinkListCreateHead(&L, 10);
    printf("前插法创建L随机链表：");
    LinkListPrint(L);
    
    LinkListClear(&L);
    
    LinkListCreateTail(&L, 10);
    printf("尾插法创建L随机链表：");
    LinkListPrint(L);
}

int main(int argc, const char * argv[]) {
    
    // linkListHandle();
    
    ElemType a[] = {1, 2, 3, 4, 5, 6};
    ElemType b[] = {1, 8, 13, 15, 24, 80};
    
    LinkList La;
    LinkList Lb;
    
    InitLinkList(&La);
    InitLinkList(&Lb);
    
    for (int i = 0; i < sizeof(a)/sizeof(ElemType); i++) {
        LinkListInsert(&La, i+1, a[i]);
    }
    
    for (int i = 0; i < sizeof(b)/sizeof(ElemType); i++) {
        LinkListInsert(&Lb, i+1, b[i]);
    }
    
    printf("La：");
    LinkListPrint(La);
    printf("Lb：");
    LinkListPrint(Lb);
    
    // Merge(&La, &Lb);
    // printf("合并 La Lb 到 La：\n");
    
    // Intersection(&La, Lb);
    // printf("La和Lb的交集La：\n");
    
    // Reverse(&La);
    // printf("反转La：\n");
    
    // printf("删除La介于30-100之间的值：\n");
    // DeleteRangeList(&La, 30, 100);
    
    printf("循环移动La 3位：\n");
    int aCount = sizeof(a)/sizeof(ElemType);
    Translate(&La, aCount, 5);
    
    printf("La：");
    LinkListPrint(La);
    printf("Lb：");
    LinkListPrint(Lb);
    
    return 0;
}
