//
//  linkList.h
//  链表
//
//  Created by miaokii on 2020/4/30.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef linkList_h
#define linkList_h

#include "publicDefine.h"

/* 节点定义 */
typedef struct Node{
    /// 数据域
    ElemType data;
    /// 指针域
    struct Node * next;
}Node, * LinkList;

/*  * LinkList  等价于  typedef struct Node * LinkList */
// typedef struct Node * LinkList;

/// 初始化链表
Status InitLinkList(LinkList *L);

/// 打印链表
void LinkListPrint(LinkList L);

/// 单链表插入
///
/// - 初始条件：L已经存在，且 1 < i
///
/// - 操作结果：L第i个位置插入新节点e
/// @param L 带插入链表
/// @param i 插入位置
/// @param e 插入元素
Status LinkListInsert(LinkList *L, int i, ElemType e);

/// 单链表取值
///
/// - 初始条件：L存在，且1<=i<=length
///
/// - 操作结果：通过e返回第i个元素
///
/// @param L 链表
/// @param i 元素位置
/// @param e 取到的元素赋值通过e返回
Status LinkListGetElem(LinkList L, int i, ElemType *e);

/// 删除单链表元素
///
/// - 初始条件：L存在，且1<=i<=length
///
/// - 操作结果：删除L第i个元素，并返回e的值
///
/// @param L 链表
/// @param i 删除位置
/// @param e 删除元素通过e返回
Status LinkListDelete(LinkList *L, int i, ElemType *e);

/// 清空链表
Status LinkListClear(LinkList *L);

/// 单链表前插法
/// @param n 随机产生n个元素值，建立带有头结点的单链表L
void LinkListCreateHead(LinkList *L, int n);

/// 单链表后插法
/// @param n 随机产生n个元素值，建立带有头结点的单链表L
void LinkListCreateTail(LinkList *L, int n);

#endif /* linkList_h */
