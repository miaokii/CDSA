//
//  main.c
//  Single Cycle Linked List
//
//  Created by miaokii on 2020/4/13.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

typedef int ElemType;
typedef int Status;

#define OK 1
#define Error 0

typedef struct Node {
    ElemType data;
    struct Node *next;
}Node, *LinkList;

/*
    初始化循环列表
 */
Status InitCycList(LinkList *L) {
    int val;
    // 新节点
    LinkList temp = NULL;
    // 尾节点
    LinkList tail = NULL;
    while (1) {
        // 输入
        scanf("%d", &val);
        // 输入0结束
        if (val == 0) break;
        // 链表不存在
        if (*L==NULL) {
            // 创建头节点
            *L = (LinkList)malloc(sizeof(Node));
            // 创建失败
            if (*L==NULL) return Error;
            // 赋值
            (*L)->data = val;
            // 循环指向自己
            (*L)->next = *L;
            // 尾节点也是自己
            tail = *L;
        } else {
//            // 创建新节点
            temp = (LinkList)malloc(sizeof(Node));
            // 创建失败
            if (temp == NULL) return Error;
            // 赋值
            temp->data = val;
            // 拼接到尾节点
            tail->next = temp;
            // 更改尾节点
            tail = temp;
            /*
             // 头插法，逆序
             // temp是头节点，为节点next为头节点
             tail->next = temp;
             // 头节点next为L
             temp->next = *L;
             // 更改头节点
             *L = temp;
             */
        }
    }
    // 尾节点next指向头节点
    tail->next = *L;
    return OK;
}

/*
    插入
    如果插入到第一个节点，需要更改L指向
 */
Status InsertList(LinkList *L, int i, ElemType e) {
    // 插入点的前一个节点
    LinkList p = *L;
    // 插入点
    LinkList temp = NULL;
    // 边界
    if (*L==NULL || i < 1) return Error;
    // 创建节点
    temp = (LinkList)malloc(sizeof(Node));
    if (temp == NULL) return Error;
    temp->data = e;
    
    // 如果插入点是头节点
    if (i == 1) {
        // next
        temp->next = *L;
        // 修改头节点
        *L = temp;
        // 找到尾节点
        for (;p->next != *L; p=p->next);
        // 修改尾节点的next
        p->next = *L;
    } else {
        // 找到插入点前一个节点
        int j = 1;
        for (; j < i - 1 && p->next != *L; j++, p=p->next);
        // 如果到达尾节点，但j还未到i-1，表明插入索引超出范围
        if (p->next == *L && j != i - 1) return Error;
        // 修改新节点next
        temp->next = p->next;
        // 插入新节点
        p->next = temp;
    }
    return OK;
}

/*
    删除节点
    如果删除第一个节点，需要修改L指向
 */
Status DeleteList(LinkList *L, int i, ElemType *e) {
    
    LinkList p = *L, temp = NULL;
    // 边界
    if (p == NULL || i < 1) return Error;
    
    // 删除首节点
    if (i == 1) {
        temp = *L;
        // 找到最后一个节点
        for (; p->next != *L; p = p->next);
        *L = (*L)->next;
        p->next = *L;
        *e = temp->data;
        free(temp);
    } else {
        // 找到删除节点前一个节点
        int j = 1;
        for (; p->next != *L && j < i-1; j++, p = p->next);
        // 如果到达尾节点，但j还未到i-1，表明插入索引超出范围
        if (p->next == *L && j != i - 1) return Error;
        // 删除的节点
        temp = p->next;
        // 删除的值
        *e = temp->data;
        // 修改前驱节点的next
        p->next = temp->next;
        // 释放
        free(temp);
    }
    
    return OK;
}

/*
    查找节点i的值，通过e返回
 */
Status FindList(LinkList L, int i, ElemType *e) {
    LinkList p = L;
    if (p==NULL) return Error;
    int j = 1;
    for (; j < i && p->next != L; p=p->next, j++);
    // 如果到达尾节点，但j还未到i-1，表明插入索引超出范围
    if (p->next == L && j != i) return Error;
    *e = p->data;
    return OK;
}

/*
    查找元素e的第一个位置
 */
Status FindIndex(LinkList L, int *i, ElemType e) {
    LinkList p = L;
    if (p==NULL) return Error;
    int j = 1;
    // 只找一遍
    for (; p->next != L && p->data != e; p=p->next, j++);
    if (p->next == L && p->data != e) {
        *i = -1;
        return Error;
    };
    *i = j;
    return OK;
}

/*
    打印列表
 */
void ListPrint(LinkList L) {
    LinkList p = L;
    if (L==NULL) return;
    do {
        printf("%d ", p->data);
        p = p->next;
    } while (p != L);
    printf("\n");
}


int main(int argc, const char * argv[]) {
    
    LinkList L;
    printf("创建L，以0作为结尾：");
    InitCycList(&L);
    printf("L：");
    ListPrint(L);
    
    int i = 5;
    printf("在L第%d个位置插入%d：", i, i);
    InsertList(&L, i, i);
    ListPrint(L);
    
    i = 10;
    ElemType d;
    DeleteList(&L, i, &d);
    printf("在L第%d个位置删除%d：", i, d);
    ListPrint(L);
    
    i = 4;
    FindList(L, i, &d);
    printf("查找L第%d个节点%d：", i, d);
    ListPrint(L);
    
    int val;
    i = -1;
    printf("输入查找的值：");
    scanf("%d", &val);
    FindIndex(L, &i, val);
    printf("查找%d在L中的位置(-1未找到)：%d\n", val, i);
    
    return 0;
}
