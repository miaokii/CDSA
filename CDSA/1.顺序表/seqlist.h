//
//  顺序表.h
//  顺序表
//
//  Created by miaokii on 2020/4/30.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef Seqlist_h
#define Seqlist_h

#include "publicDefine.h"

/// 顺序表结构
typedef struct {
    // 存储空间的基地址，其实是一个数组结构，长度为listsize，数组中的元素类型为ElemType类型
    ElemType * elem;
    // 当前长度，即存储了值的elem数组长度
    int length;
    // 总的存储容量，总的长度，顺序表申请的时候长度需要确定，当到达最大长度时，在重新申请内存
    int listSize;
} Seqlist;

/**
    初始化顺序表 Seqlist
    操作结果：构造一个空的线性表L
 */
Status InitList_Sq(Seqlist *L);

/**
    向顺序表插入元素
    初始条件：L已经存在，且1<=i<=ListLength_Sq(L)+1
    操作结果：在L中第i个位置之前插入新元素e，L长度 + 1
 */
Status ListInsert_Sq(Seqlist* L, int i, ElemType e);

/**
    顺序表取值
    初始条件：L存在，并且 1 < i < L->length
    操作结果：返回 i元素 e
 */
Status ListGet_Sq(Seqlist L, int i, ElemType * e);

/**
    查找顺序表元素
    初始条件：L存在
    操作结果：返回L中元素值为e的元素的位置，若不存在返回0
 */
int ListLocate_Sq(Seqlist L, ElemType e);


/**
    顺序表删除元素
    初始条件：L存在，并且 1 < i < L->length
    操作结果：删除并返回e
 */
Status ListDele_Sq(Seqlist * L, int i, ElemType * e);

/**
    长度
 */
int listLength_Sq(Seqlist L);

/**
    判断顺序表是否为空表
 */
Status ListEmpth_Sq(Seqlist L);

/**
    清空顺序表
 */
Status ListClear_Sq(Seqlist * L);

/**
    打印顺序表
 */
void ListPrint_Sq(Seqlist L);

/// 交换顺序表中i，j两个位置的元素
/// @param L 顺序表
/// @param i i
/// @param j j
void SwapList_Sq(Seqlist *L, int i, int j);

/*
    合并两个有序顺序表
    初始条件：La，Lb有序
    操作结果：合并后Lc也有序
 */
Status MergeList_Sq(Seqlist La, Seqlist Lb, Seqlist * Lc);


#endif /* Seqlist_h */
