//
//  main.c
//  Bothway Linked List
//
//  Created by miaokii on 2020/4/13.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

#define OK 1
#define Error 0;

typedef int ElemType;
typedef int Status;

typedef struct Node {
    ElemType data;
    Node * piror;
    Node * next;
}Node, *LinkList;

/* 创建双向链表 */
Status ListCreate(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L==NULL) return Error;
    (*L)->next = NULL;
    (*L)->data = NULL;
    return OK;
}

/* 创建双向循环列表 */
Status CycListCreate(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L==NULL) return Error;
    (*L)->next = *L;
    (*L)->piror = *L;
}

/* 双向链表插入 */
Status ListInsert(LinkList *L, int i, ElemType e) {
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
