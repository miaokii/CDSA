//
//  bubble.h
//  排序
//
//  Created by miaokii on 2020/5/18.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef bubble_h
#define bubble_h

#include <stdio.h>
#include "SqList.h"


/// 冒泡排序-交换排序
/// @param L L
void bubble_sort_simple(SqList * L);

/// 冒泡排序，比较相邻的元素
/// @param L L
void bubble_sort_bubble(SqList *L);

/// 冒泡排序优化，省略不必要的排序
/// 当原序列部分有序的时候
/// @param L L
void bubble_sort_bubble_optimalize(SqList *L);

#endif /* bubble_h */
