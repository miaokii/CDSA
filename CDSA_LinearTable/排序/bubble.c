//
//  bubble.c
//  排序
//
//  Created by miaokii on 2020/5/18.
//  Copyright © 2020 ly. All rights reserved.
//

#include "bubble.h"


/// 冒泡/交换排序
///
/// @param L L
void bubble_sort_simple(SqList * L) {
    int i, j;
    for (i = 1; i <= L->length; i++) {
        for (j = i + 1; j <= L->length; j++) {
            // 将最小的向前交换
            if (L->elem[i] > L->elem[j]) {
                swap_sqlist(L, i, j);
            }
        }
    }
}

/// 冒泡排序
/// @param L L
void bubble_sort_bubble(SqList *L) {
    int i, j;
    for (i = L->length; i > 0; i--) {
        for (j = 1; j <= i; j++) {
            // 大的向后排，每次j循环找到本轮最大的放到最后
            if (L->elem[j] > L->elem[j+1]) {
                swap_sqlist(L, j, j+1);
            }
        }
    }
}

/// 冒泡排序优化
/// @param L L
void bubble_sort_bubble_optimalize(SqList *L) {
    int i, j;
    // flag作为标记
    Status flag = TRUE;
    // i：1->length
    // 如果flag为false退出循环，表示出现过一次j从length到i的过程，都没有交换的状态
    for (i = 1; i <= L->length && flag; i++) {
        flag = FALSE;
        for (j = L->length; j > i; j--) {
            // 小的的向前排，每次j循环找到本轮最小的放到最前
            if (L->elem[j] < L->elem[j-1]) {
                swap_sqlist(L, j, j-1);
                // 如果有交换的动作，改为true
                flag = TRUE;
            }
        }
    }
}
