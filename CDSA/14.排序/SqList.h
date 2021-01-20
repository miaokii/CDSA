//
//  SqList.h
//  排序
//
//  Created by miaokii on 2020/5/18.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef SqList_h
#define SqList_h

#include <stdio.h>
#include "publicDefine.h"

#define Sq_MaxSize 100

typedef struct {
    // 0位置用作哨兵或临时变量
    ElemType elem[Sq_MaxSize + 1];
    // 顺序表长度
    int length;
}SqList;

Status init_sqlist(SqList *L);

/// 交换两个元素
/// @param L L
/// @param i i
/// @param j j
void swap_sqlist(SqList *L, int i, int j);

void print_sqlist(SqList L);

#endif /* SqList_h */
