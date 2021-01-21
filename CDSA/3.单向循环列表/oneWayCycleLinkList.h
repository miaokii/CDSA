//
//  oneWayCycleLinkList.h
//  3.单项循环链表
//
//  Created by miaokii on 2021/1/21.
//  Copyright © 2021 ly. All rights reserved.
//

#ifndef oneWayCycleLinkList_h
#define oneWayCycleLinkList_h

#include <stdio.h>
#include "linkList.h"

/// 初始化
/// @param L 链表
Status OneWayCycLinkListInit(LinkList *L);

/// 插入
/// @param L 链表
/// @param i 插入位置
/// @param e 插入元素
Status InsertList(LinkList *L, int i, ElemType e);

/// 删除
/// @param L 链表
/// @param i 删除位置
/// @param e 删除的元素
Status DeleteList(LinkList *L, int i, ElemType *e);

/// 查找元素
/// @param L 链表
/// @param i 查找位置
/// @param e 找到的元素
Status FindList(LinkList L, int i, ElemType *e);

/// 查找位置
/// @param L 链表
/// @param i 位置
/// @param e 元素值
Status FindIndex(LinkList L, int *i, ElemType e);

/// 打印链表
/// @param L 链表
void ListPrint(LinkList L);

#endif /* oneWayCycleLinkList_h */
