//
//  main.c
//  1.顺序表
//
//  Created by miaokii on 2021/1/20.
//  Copyright © 2021 ly. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "seqlist.h"

int main(int argc, const char * argv[]) {
    
    Seqlist L;
    ElemType e;
    Status iStatus;
    
    // 初始化顺序表
    iStatus = InitList_Sq(&L);
    printf("初始化顺序表L%s\n", desStatus(iStatus));
    
    e = 2;
    iStatus = ListInsert_Sq(&L, 1, e);
    printf("在顺序表L中%d位置插入元素%d%s\n", 1, e, desStatus(iStatus));
    e = 3;
    iStatus = ListInsert_Sq(&L, 1, e);
    printf("在顺序表L中%d位置插入元素%d%s\n", 1, e, desStatus(iStatus));
    
    ElemType list[] = {2, 4, 6, 5, 7};
    for (int i = 0; i < sizeof(list)/sizeof(ElemType); i++) {
        ListInsert_Sq(&L, L.length+1, list[i]);
    }
    
    iStatus = ListGet_Sq(L, 5, &e);
    printf("获取顺序表L中5位置的值：%d\n",e);
    
    int index = ListLocate_Sq(L, e);
    printf("获取顺序表L中%d元素的位置：%d\n", e, index);
    
    printf("删除前顺序表L：\n");
    ListPrint_Sq(L);
    
    iStatus = ListDele_Sq(&L, 3, &e);
    printf("删除顺序表L中3位置的元素：%d\n", e);
    
    printf("删除后顺序表L：\n");
    ListPrint_Sq(L);
    
    printf("交换顺序表L中3与5位置的元素\n");
    SwapList_Sq(&L, 3, 5);
    ListPrint_Sq(L);
    
    printf("顺序表L长度：%d\n", listLength_Sq(L));
    
    printf("顺序表L是为空：%s\n", ListEmpth_Sq(L) == 1 ? "是" : "否");
    
    printf("清空顺序表L：%s\n", desStatus(ListClear_Sq(&L)));
    
    printf("顺序表L是为空：%s\n", ListEmpth_Sq(L) == 1 ? "是" : "否");
    
    printf("\n\n合并有序顺序表La，Lb到Lc\n");
    Seqlist La;
    Seqlist Lb;
    Seqlist Lc;
    InitList_Sq(&La);
    InitList_Sq(&Lb);
    InitList_Sq(&Lc);
    
    ElemType a[] = {1, 2, 3, 6, 8, 10, 23};
    ElemType b[] = {2, 5, 6, 7, 9};
    
    for (int i = 0; i < sizeof(a)/sizeof(ElemType); i++) {
        ListInsert_Sq(&La, i+1, a[i]);
    }
    for (int i = 0; i < sizeof(b)/sizeof(ElemType); i++) {
        ListInsert_Sq(&Lb, i+1, b[i]);
    }
    printf("顺序表La：\n");
    ListPrint_Sq(La);
    
    printf("顺序表Lb：\n");
    ListPrint_Sq(Lb);
    
    MergeList_Sq(La, Lb, &Lc);
    
    printf("合并后顺序表Lc：\n");
    ListPrint_Sq(Lc);
    
    return 0;
}
  
