//
//  linkList.h
//  链表
//
//  Created by miaokii on 2020/4/30.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef linkList_h
#define linkList_h

#include <stdio.h>
#include "publicDefine.h"

// MARK: - 一个整型链表
/* 节点定义 */
typedef struct Node {
    /// 数据域
    ElemType data;
    /// 指针域
    struct Node * next;
}Node, * LinkList;

/// 初始化链表
Status InitList(LinkList *L);

/// 打印链表
void ListPrint(LinkList L);

/// 单链表插入
///
/// - 初始条件：L已经存在，且 1 < i
///
/// - 操作结果：L第i个位置插入新节点e
/// @param L 带插入链表
/// @param i 插入位置
/// @param e 插入元素
Status ListInsert(LinkList *L, int i, ElemType e);

/// 单链表取值
///
/// - 初始条件：L存在，且1<=i<=length
///
/// - 操作结果：通过e返回第i个元素
///
/// @param L 链表
/// @param i 元素位置
/// @param e 取到的元素赋值通过e返回
Status GetElem(LinkList L, int i, ElemType *e);

/// 删除单链表元素
///
/// - 初始条件：L存在，且1<=i<=length
///
/// - 操作结果：删除L第i个元素，并返回e的值
///
/// @param L 链表
/// @param i 删除位置
/// @param e 删除元素通过e返回
Status ListDelete(LinkList *L, int i, ElemType *e);

/// 清空链表
Status ListClear(LinkList *L);

/// 单链表前插法
/// @param n 随机产生n个元素值，建立带有头结点的单链表L
void ListCreateHead(LinkList *L, int n);

/// 单链表后插法
/// @param n 随机产生n个元素值，建立带有头结点的单链表L
void ListCreateTail(LinkList *L, int n);


#endif /* linkList_h */
