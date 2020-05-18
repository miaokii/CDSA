//
//  SqList.c
//  排序
//
//  Created by miaokii on 2020/5/18.
//  Copyright © 2020 ly. All rights reserved.
//

#include "SqList.h"
#include "stdlib.h"

Status init_sqlist(SqList *L) {
    return OK;
}

void swap_sqlist(SqList *L, int i, int j) {
    if (L && i <= L->length && j <= L->length) {
//        ElemType temp = L->elem[i];
//        L->elem[i] = L->elem[j];
//        L->elem[j] = temp;
        
        L->elem[i] += L->elem[j];
        L->elem[j] = L->elem[i] - L->elem[j];
        L->elem[i] = L->elem[i] - L->elem[j];

//        L->elem[i] = L->elem[i] ^ L->elem[j];
//        L->elem[j] = L->elem[i] ^ L->elem[j];
//        L->elem[i] = L->elem[i] ^ L->elem[j];
    }
}

void print_sqlist(SqList L) {
    for (int i = 1; i <= L.length; i ++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}
