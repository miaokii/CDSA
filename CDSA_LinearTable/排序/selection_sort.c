//
//  selection_sort.c
//  排序
//
//  Created by miaokii on 2020/5/18.
//  Copyright © 2020 ly. All rights reserved.
//

#include "selection_sort.h"

/// 选择排序 O(n^2)
/// @param L L
void select_sort_simple(SqList *L) {
    int i, j, min;
    for (i = 1; i < L->length; i++) {
        min = i;
        for (j = i + 1; j <= L->length; j++) {
            if (L->elem[min] > L->elem[j])
                min = j;
        }
        
        if (i != min) {
            swap_sqlist(L, i, min);
        }
    }
}
