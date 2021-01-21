//
//  main.c
//  Bothway Linked List
//
//  Created by miaokii on 2020/4/13.
//  Copyright © 2020 ly. All rights reserved.
//

#include "stdlib.h"
#include "twoWayLinkList.h"

int main(int argc, const char * argv[]) {
    
    TwoWayLinkList L;
    ListCreate(&L);
    printf("创建双向链表L：");
    for (int i = 1; i < 6; i++) {
        ListInsert(&L, i, i);
    }
    ListPrint(L);
    printf("在L的1位置插入5：");
    ListInsert(&L, 1, 5);
    ListPrint(L);
    
    ElemType e;
    int i = 5;
    ListDelete(&L, i, &e);
    printf("删除L的第%d个节点%d：", i, e);
    ListPrint(L);
    
    printf("查找L中节点5的位置：%d", ListIndex(L, 5));
    ListRemove(&L, 5);
    printf("\n删除L总所有节点5：");
    ListPrint(L);
    
    printf("\n\n");
    
    TwoWayLinkList L1;
    CycListCreate(&L1);
    printf("创建双向循环链表L1：");
    for (int i = 1; i < 6; i++) {
        ListCycInsert(&L1, i, i);
    }
    ListCycPrint(L1);
    
    printf("在L1的1位置插入5：");
    ListCycInsert(&L1, 1, 5);
    ListCycPrint(L1);
    
    printf("在L1的6位置插入1：");
    ListCycInsert(&L1, 6, 1);
    ListCycPrint(L1);
    
    ElemType a;
    int j = 1;
    ListCycDelete(&L1, j, &a);
    printf("删除L1的第%d个节点%d：", j, a);
    ListCycPrint(L1);
    
    printf("查找L1中节点2的位置：%d", ListCycIndex(L1, 2));
    
    ListCycRemove(&L1, 5);
    printf("\n删除L1总所有节点5：");
    ListCycPrint(L1);
    
    printf("\n");
    return 0;
}
