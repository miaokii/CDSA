//
//  linkList.c
//  链表
//
//  Created by miaokii on 2020/4/30.
//  Copyright © 2020 ly. All rights reserved.
//

#include "linkList.h"
#include "stdlib.h"
#include <stdio.h>

/**
    创建单链表
 */
Status InitLinkList(LinkList *L) {
    // 创建头节点，L指向头节点，头节点不存储值
    // LinkList本身就是 struct Node * 类型
    *L = (LinkList)malloc(sizeof(Node));
    // 存储空间分配失败
    if (*L==NULL) return ERROR;
    // 头节点指针域为空
    (*L)->next = NULL;
    return OK;
}

/**
    打印链表
 */
void LinkListPrint(LinkList L) {
    // 第一个节点是首元节点
    if (L==NULL) return;
    LinkList p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void LinkListDetailPrint(LinkList L) {
    if (L==NULL) return;
    LinkList p = L->next;
    while (p) {
        printf("%p:%d ", p, p->data);
        p = p->next;
    }
    printf("\n");
}

/**
    单链表插入
    初始条件：L已经存在，且 1 < i
    操作结果：L第i个位置插入新节点e
 */
Status LinkListInsert(LinkList *L, int i, ElemType e) {
    
    // L时形参，传入的是链表的首地址，所以先要取值
    LinkList p = *L;
    // 从头节点开始找
    int j = 1;
    // 找到第i-1个节点
    while (p && j < i) {
        p = p->next;
        j += 1;
    }
    // 第i个元素不存在
    if (j > i || !p) return ERROR;
    
    // 新节点
    LinkList s = (LinkList)malloc(sizeof(Node));
    // s的next为p的next
    s->next = p->next;
    // 赋值
    s->data = e;
    p->next = s;
    return OK;
}

/**
    单链表取值
    初始条件：L存在，且1<=i<=length
    操作结果：通过e返回第i个元素
 */
Status LinkListGetElem(LinkList L, int i, ElemType *e) {
    // L的第一个节点
    LinkList p = L->next;
    int j = 1;
    
    while (p && j < i) {
        p = p->next;
        j++;
    }
    
    if (!p || j > i) return ERROR;
    *e = p->data;
    return OK;
}

/**
    删除单链表元素
    初始条件：L存在，且1<=i<=length
    操作结果：删除L第i个元素，并返回e的值
 */
Status LinkListDelete(LinkList *L, int i, ElemType *e) {
    // 指向第一个元素
    LinkList p = *L;
    LinkList temp;
    int j = 1;
    
    // 查找第i-1个节点
    while (p->next && j < i) {
        p = p->next;
        j++;
    }
    // 如果i>n或者i<1，删除位置不合理
    if (!(p->next) || j > i) return ERROR;
    // temp指向被删除的节点
    temp = p->next;
    // temp的后继节点给p的后继
    p->next = temp->next;
    // 返回删除值
    *e = temp->data;
    // 释放节点
    free(temp);
    return OK;
}

/**
    清空链表
 */
Status LinkListClear(LinkList *L) {
    LinkList p = (*L)->next;
    LinkList q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    // 头节点指针域空
    (*L)->next = NULL;
    return OK;
}

/**
    单链表前插法
    随机产生n个元素值，建立带有头结点的单链表L
 */
void LinkListCreateHead(LinkList *L, int n) {
    // 带有头节点的
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    
    LinkList p;
    int i = 1;
    while (i <= n) {
        // 新节点
        p = (LinkList)malloc(sizeof(Node));
        p->data = rand() % 100;
        // 新节点next为头节点next
        p->next = (*L)->next;
        // 插入头节点之后
        (*L)->next = p;
        i++;
    }
}

/**
    单链表后插法
 */
void LinkListCreateTail(LinkList *L, int n) {
    
    // 初始化
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    
    LinkList next = *L;
    int j = 1;
    while (j <= n) {
        LinkList new = (LinkList)malloc(sizeof(Node));
        new->next = NULL;
        new->data = random()%100;
        next->next = new;
        next=new;
        j++;
    }
}
