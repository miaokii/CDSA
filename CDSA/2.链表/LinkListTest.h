//
//  LinkListTest.h
//  2.链表
//
//  Created by miaokii on 2021/1/26.
//  Copyright © 2021 ly. All rights reserved.
//

#ifndef LinkListTest_h
#define LinkListTest_h
#include "linkList.h"

#include <stdio.h>


/// 合并两个有序链表
///
/// @param La 链表a
/// @param Lb 链表b
///
/// 已知两个链表A和B分别表示两个集合，其元素递增排列，将AB合并，不允许有相同元素，不占用其他空间
/// eg：La = {1, 3, 5, 6, 7, 9}; Lb = {2, 4, 5, 6, 8, 10}; 输出La = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
void Merge(LinkList *La, LinkList *Lb);

/// 两个集合的交集
/// @param La 链表a
/// @param Lb 链表b
///
/// 已知两个链表A和B分别表示两个集合，其元素递增排列，求A与B的交集，并存储在A链表中
/// eg：La = {2,4,6,8}; Lb = {4,6,8,10}; 输出La = {4,6,8}
void Intersection(LinkList *La, LinkList Lb);

/// 旋转链表
/// @param L 链表
/// 将链表中所有节点的链接方向"原地旋转"，不使用其他空间
/// eg：L={0,2,4,6,8,10}，逆转后：L = {10,8,6,4,2,0}
/// 使用头插法再插入一遍
void Reverse(LinkList *L);

/// 删除有序链表区间内的值
/// @param L 链表
/// @param mink 区间左
/// @param maxk 区间又
void DeleteRangeList(LinkList *L, ElemType mink, ElemType maxk);

/// 循环移动p个位置
/// @param L 链表
/// @param count  链表长度
/// @param m 移动长度，m<0向右移动，否则向左移动
/// eg：L={1, 2, 3, 4, 5, 6} m=-1  =>  {2,3,4,5,6,1}
/// eg：L={1, 2, 3, 4, 5, 6} m=3  =>  {4,5,6,1,2,3}
void Translate(LinkList *L, int count, int m);

/// 寻找主元素
/// @param list 链表
/// @param n 链表长度
int MainElement(ElemType * list, int n);

/// 删除链表中绝对值相同的元素，只保留第一次出现的元素
/// @param L 链表
/// @param n 长度
void deleteAbsRepeatNode(LinkList *L, int n);

#endif /* LinkListTest_h */
