//
//  main.c
//  CDSA_LinearTable
//
//  Created by miaokii on 2020/4/10.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "顺序表.h"

int main(int argc, const char * argv[]) {
    
    Seqlist L;
    ElemType e;
    Status iStatus;
    
    Seqlist La;
    Seqlist Lb;
    Seqlist Lc;
    
    int a[] = {1, 2, 3, 6, 8, 10, 23};
    int b[] = {2, 5, 6, 7, 9};
    
    // 初始化顺序表
    InitList_Sq(&L);
    InitList_Sq(&La);
    InitList_Sq(&Lb);
    InitList_Sq(&Lc);
    
    printf("顺序表\n");
    for (int i = 0; i < 7; i++) {
        ListInsert_Sq(&La, i+1, a[i]);
    }
    for (int i = 0; i < 5; i++) {
        ListInsert_Sq(&Lb, i+1, b[i]);
    }
    ListPrint_Sq(La);
    ListPrint_Sq(Lb);
    
    MergeList_Sq(La, Lb, &Lc);
    ListPrint_Sq(Lc);
    
//    test();
    
//    printf("在6的位置插入10\n");
//    ListInsert_Sq(&L, 6, 10);
//    ListPrint_Sq(L);
//
//    printf("删除1位置的元素\n");
//    ListDele_Sq(&L, 1, &e);
//    printf("删除元素为：%d\n", e);
//    ListPrint_Sq(L);
//
//    printf("查找元素2的位置：%d\n", ListLocate_Sq(L, 2));
        
    return 0;
}

/*
    自增自减运算符
    前变后不变
 
    int i = 1;
 // 表达式的值是2，i是2
    ++i;
 // 表达式的值是2，i是3
    i++;
 
 */
