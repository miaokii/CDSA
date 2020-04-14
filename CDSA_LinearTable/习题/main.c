//
//  main.c
//  习题
//
//  Created by miaokii on 2020/4/14.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define Error -1;
#define OK 0;

typedef int ElemType;
typedef int Status;

typedef struct Node {
    ElemType data;
    struct Node * next;
}Node, *LinkList;

/* 使用数组 初始化列表 */
Status InitList(LinkList *L, ElemType * vals, int count) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) return Error;
    (*L)->next = NULL;
    
    LinkList temp;
    LinkList tail = *L;
    for (int i = 0; i < count; i++) {
        temp = (LinkList)malloc(sizeof(Node));
        temp->data = vals[i];
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
    }
    return OK;
}

void ListInsert(LinkList *L, int i, ElemType e) {
    if (*L==NULL || i < 1) return;
    LinkList p = (*L)->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    LinkList temp = (LinkList)malloc(sizeof(Node));
    if (temp==NULL) return;
    temp->data = e;
    temp->next = p->next;
    p->next = temp;
    return;
}

void ListPrint(LinkList L) {
    LinkList p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/*
    1、将2个递增的有序链表合并为⼀个链表的有序链表; 要求结果链表仍然使⽤两个链表的存储空间,不另外占⽤其他的存储空间. 表中不允许有重复的数据
    合并结果通过La返回怒
 */
void Merge1(LinkList *La, LinkList Lb) {
    
    LinkList pa = (*La)->next ;
    LinkList pb = Lb->next;
    
    int j = 0;
    while (pa && pb) {
        j++;
        // 插入pb
        if (pa->data > pb->data) {
            ListInsert(&(*La), j-1, pb->data);
            pb = pb->next;
        } else if (pa->data == pb->data) {
            pa = pa->next;
            pb = pb->next;
        } else {
            pa = pa->next;
        }
    }
    
    while (pb) {
        ListInsert(La, j, pb->data);
        pb = pb->next;
        j++;
    }
}

void Merge2(LinkList *La, LinkList Lb) {
    
    LinkList pa = (*La)->next ;
    LinkList pb = Lb->next;
    LinkList temp;
    while (pa && pb) {
        // 插入pb到pa
        if (pa->data > pb->data) {
            temp = pb->next;
            pb->next = pa->next;
            pb->next = pa->next;
            pb = temp;
        } else if (pa->data == pb->data) {
            pa = pa->next;
            pb = pb->next;
        } else {
            pa = pa->next;
        }
    }
    
    
}



int main(int argc, const char * argv[]) {
    
    LinkList La;
    LinkList Lb;
    ElemType a[] = {1, 2, 5, 8, 9, 14};
    ElemType b[] = {3, 5, 6, 8, 13, 14, 15, 29};
    int counta = sizeof(a) / sizeof(ElemType);
    int countb = sizeof(b) / sizeof(ElemType);
    InitList(&La, a, counta);
    InitList(&Lb, b, countb);
    printf("链表a：");
    ListPrint(La);
    printf("链表b：");
    ListPrint(Lb);
    
    Merge(&La, Lb);
    printf("合并ab：");
    ListPrint(La);
    
    return 0;
}
