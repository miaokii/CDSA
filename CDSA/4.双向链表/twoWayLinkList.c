//
//  twoWayCycleLinkList.c
//  双向链表
//
//  Created by miaokii on 2021/1/21.
//  Copyright © 2021 ly. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "twoWayLinkList.h"

/* 创建双向链表 */
Status ListCreate(TwoWayLinkList *L) {
    *L = (TwoWayLinkList)malloc(sizeof(TwoWayNode));
    if (*L==NULL) return ERROR;
    (*L)->next = NULL;
    (*L)->piror = NULL;
    return OK;
}

/* 创建双向循环列表 */
Status CycListCreate(TwoWayLinkList *L) {
    *L = (TwoWayLinkList)malloc(sizeof(TwoWayNode));
    if (*L==NULL) return ERROR;
    (*L)->next = *L;
    (*L)->piror = *L;
    return OK;
}

/* 双向链表插入 */
Status ListInsert(TwoWayLinkList *L, int i, ElemType e) {
    // 位置不能小于1，并且L存在
    if (*L==NULL || i < 1) return ERROR;
    TwoWayLinkList p = *L, temp;
    int j = 1;
    // 找到插入点前一个节点
    while (p->next && j < i) {
        p = p->next;
        j++;
    }
    
    // 如果到表尾，i还是大于j，表示插入位置不允许
    if (p->next == NULL && j != i) return ERROR;
    // 新节点
    temp = (TwoWayLinkList)malloc(sizeof(TwoWayNode));
    if (!temp) return ERROR;
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
Status ListCycInsert(TwoWayLinkList *L, int i, ElemType e) {
    // 边界
    if (*L==NULL || i < 1) return ERROR;
    
    TwoWayLinkList p = *L, temp;
    int j = 1;
    // 找到插入点的上一个节点
    while ( p->next != *L && j<i) {
        p = p->next;
        j++;
    }
    // 如果到表尾，i还是大于j，表示插入位置不允许
    if (p->next == *L && j != i) return ERROR;
    
    temp = (TwoWayLinkList)malloc(sizeof(TwoWayNode));
    if (temp == NULL) return ERROR;
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
Status ListDelete(TwoWayLinkList *L, int i, ElemType *e) {
    if (*L==NULL || i < 1) return ERROR;
    // p 从第一个节点开始
    TwoWayLinkList p = (*L)->next;
    int j = 1;
    
    // 找到删除的节点
    while (p && j < i) {
        p = p->next;
        j++;
    }
    
    // 没有找到节点
    if (p == NULL) return ERROR;
    
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
Status ListCycDelete(TwoWayLinkList *L, int i, ElemType *e) {
    if (*L==NULL || i < 1) return ERROR;
    TwoWayLinkList p = (*L)->next;
    int j = 1;
    
    while (p != *L && j < i) {
        p = p->next;
        j++;
    }
    
    if (p == *L) return ERROR;
    
    *e = p->data;
    p->piror->next = p->next;
    p->next->piror = p->piror;
    free(p);
    return OK;
}

/* 查找双向列表位置 */
int ListIndex(TwoWayLinkList L, ElemType e) {
    if (L==NULL) return -1;
    TwoWayLinkList p = L->next;
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
int ListCycIndex(TwoWayLinkList L, ElemType e) {
    if (L==NULL) return -1;
    TwoWayLinkList p = L->next;
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
Status ListRemove(TwoWayLinkList *L, ElemType e) {
    if (*L==NULL) return ERROR;
    TwoWayLinkList p = (*L)->next, temp;
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
Status ListCycRemove(TwoWayLinkList *L, ElemType e) {
    if (*L==NULL) return ERROR;
    TwoWayLinkList p = (*L)->next;
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
void ListPrint(TwoWayLinkList L) {
    TwoWayLinkList p = L;
    if (L==NULL) return;
    while (p->next) {
        p=p->next;
        printf("%d ", p->data);
    }
    printf("\n");
}

/* 打印双向循环链表 */
void ListCycPrint(TwoWayLinkList L) {
    TwoWayLinkList p = L;
    if (L==NULL) return;
    while (p->next != L) {
        p=p->next;
        printf("%d ", p->data);
    }
    printf("\n");
}

