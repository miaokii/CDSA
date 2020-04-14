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
    struct Node * piror;
    struct Node * next;
}Node, *LinkList;

/* 创建双向链表 */
Status ListCreate(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L==NULL) return Error;
    (*L)->next = NULL;
    (*L)->piror = NULL;
    return OK;
}

/* 创建双向循环列表 */
Status CycListCreate(LinkList *L) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L==NULL) return Error;
    (*L)->next = *L;
    (*L)->piror = *L;
    return OK;
}

/* 双向链表插入 */
Status ListInsert(LinkList *L, int i, ElemType e) {
    // 位置不能小于1，并且L存在
    if (*L==NULL || i < 1) return Error;
    LinkList p = *L, temp;
    int j = 1;
    // 找到插入点前一个节点
    while (p->next && j < i) {
        p = p->next;
        j++;
    }
    
    // 如果到表尾，i还是大于j，表示插入位置不允许
    if (p->next == NULL && j != i) return Error;
    // 新节点
    temp = (LinkList)malloc(sizeof(Node));
    if (!temp) return Error;
    temp->data = e;
    temp->next = NULL;
    temp->piror = NULL;
    // 1、新节点的下一个节点
    temp->next = p->next;
    // 尾节点
    if (p->next == NULL) {
        // p下个节点为temp
        p->next = temp;
        // temp前一个节点为p
        temp->piror = p;
    } else {
        // 2、p后节点的piror指向temp
        p->next->piror = temp;
        // 3、p下个节点为temp
        p->next = temp;
        // 4、temp前一个节点为p
        temp->piror = p;
    }
    return OK;
}

/*双向循环列表插入*/
Status ListCycInsert(LinkList *L, int i, ElemType e) {
    // 边界
    if (*L==NULL || i < 1) return Error;
    
    LinkList p = *L, temp;
    int j = 1;
    // 找到插入点的上一个节点
    while ( p->next != *L && j<i) {
        p = p->next;
        j++;
    }
    // 如果到表尾，i还是大于j，表示插入位置不允许
    if (p->next == *L && j != i) return Error;
    
    temp = (LinkList)malloc(sizeof(Node));
    if (temp == NULL) return Error;
    temp->data = e;
    temp->piror = NULL;
    temp->next = NULL;
    
    temp->next = p->next;
    p->next->piror = temp;
    
    temp->piror = p;
    p->next = temp;
    
    return OK;
}

/* 双向链表删除节点 */
Status ListDelete(LinkList *L, int i, ElemType *e) {
    if (*L==NULL || i < 1) return Error;
    // p 从第一个节点开始
    LinkList p = (*L)->next;
    int j = 1;
    
    // 找到删除的节点
    while (p && j < i) {
        p = p->next;
        j++;
    }
    
    // 没有找到节点
    if (p == NULL) return Error;
    
    // 如果删除的节点是尾节点
    if (p->next == NULL) {
        p->piror->next = NULL;
        *e = p->data;
        free(p);
    } else {
        p->piror->next = p->next;
        p->next->piror = p->piror;
        *e = p->data;
        free(p);
    }
    return OK;
}

/* 删除双向循环链表的节点 */
Status ListCycDelete(LinkList *L, int i, ElemType *e) {
    if (*L==NULL || i < 1) return Error;
    LinkList p = (*L)->next;
    int j = 1;
    
    while (p != *L && j < i) {
        p = p->next;
        j++;
    }
    
    if (p == *L) return Error;
    
    *e = p->data;
    p->piror->next = p->next;
    p->next->piror = p->piror;
    free(p);
    return OK;
}

/* 查找双向列表位置 */
int ListIndex(LinkList L, ElemType e) {
    if (L==NULL) return -1;
    LinkList p = L->next;
    int j = 1;
    while (p) {
        if (p->data == e) {
            return j;
        }
        p = p->next;
        j++;
    }
    return -1;
}

/* 查找双向循环链表节点位置 */
int ListCycIndex(LinkList L, ElemType e) {
    if (L==NULL) return -1;
    LinkList p = L->next;
    int j = 1;
    while (p != L) {
        if (p->data == e) {
            return j;
        }
        p = p->next;
        j++;
    }
    return -1;
}

/* 删除指定节点 */
Status ListRemove(LinkList *L, ElemType e) {
    if (*L==NULL) return Error;
    LinkList p = (*L)->next, temp;
    while (p) {
        if (p->data == e) {
            temp = p;
            // 尾节点
            if (p->next == NULL) {
                p->piror->next = NULL;
            } else {
                p->piror->next = p->next;
                p->next->piror = p->piror;
            }
            free(temp);
        }
        p = p->next;
    }
    return OK;
}

/* 删除双向链表制定节点 */
Status ListCycRemove(LinkList *L, ElemType e) {
    if (*L==NULL) return Error;
    LinkList p = (*L)->next;
    while (p!=(*L)) {
        if (p->data == e) {
            p->piror->next = p->next;
            p->next->piror = p->piror;
            free(p);
        }
        p = p->next;
    }
    return OK;
}

/* 打印双向链表 */
void ListPrint(LinkList L) {
    LinkList p = L;
    if (L==NULL) return;
    while (p->next) {
        p=p->next;
        printf("%d ", p->data);
    }
    printf("\n");
}

/* 打印双向循环链表 */
void ListCycPrint(LinkList L) {
    LinkList p = L;
    if (L==NULL) return;
    while (p->next != L) {
        p=p->next;
        printf("%d ", p->data);
    }
    printf("\n");
}


int main(int argc, const char * argv[]) {
    
    LinkList L;
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
    
    LinkList L1;
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
