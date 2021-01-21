//
//  twoWayCycleLinkList.h
//  双向链表
//
//  Created by miaokii on 2021/1/21.
//  Copyright © 2021 ly. All rights reserved.
//

#ifndef twoWayCycleLinkList_h
#define twoWayCycleLinkList_h

#include <stdio.h>
#include "publicDefine.h"

typedef struct TwoWayNode {
    ElemType data;
    /// 前驱
    struct TwoWayNode * piror;
    /// 后继
    struct TwoWayNode * next;
}TwoWayNode, *TwoWayLinkList;

/// 创建双向链表
/// @param L L
Status ListCreate(TwoWayLinkList *L);

/// 创建双向循环列表
/// @param L L
Status CycListCreate(TwoWayLinkList *L);

/// 双向链表插入
/// @param L L
/// @param i 位置
/// @param e 元素
Status ListInsert(TwoWayLinkList *L, int i, ElemType e);

/// 双向循环链表插入
/// @param L L
/// @param i 位置
/// @param e 元素
Status ListCycInsert(TwoWayLinkList *L, int i, ElemType e);

/// 双向链表删除节点
/// @param L L
/// @param i 删除位置
/// @param e 删除的节点
Status ListDelete(TwoWayLinkList *L, int i, ElemType *e);

/// 删除双向循环链表的节点
/// @param L L
/// @param i 删除位置
/// @param e 删除的节点
Status ListCycDelete(TwoWayLinkList *L, int i, ElemType *e);

/// 查找双向列表位置
/// @param L L
/// @param e  查找元素
int ListIndex(TwoWayLinkList L, ElemType e);

/// 查找双向循环链表节点位置
/// @param L L
/// @param e  查找元素
int ListCycIndex(TwoWayLinkList L, ElemType e);

/// 删除指定节点
/// @param L L
/// @param e 删除的节点
Status ListRemove(TwoWayLinkList *L, ElemType e);

/// 删除双向链表制定节点
/// @param L L
/// @param e 删除的节点
Status ListCycRemove(TwoWayLinkList *L, ElemType e);

/// 打印双向链表
/// @param L L
void ListPrint(TwoWayLinkList L);

/// 打印双向循环链表
/// @param L L
void ListCycPrint(TwoWayLinkList L);

#endif /* twoWayCycleLinkList_h */
