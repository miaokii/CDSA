//
//  顺序表.c
//  顺序表
//
//  Created by miaokii on 2020/4/30.
//  Copyright © 2020 ly. All rights reserved.
//

#include "seqlist.h"

/**
    初始化顺序表 Seqlist
    操作结果：构造一个空的线性表L
 */
Status InitList_Sq(Seqlist *L) {
    // 分配LIST_INIT_SIZE大小的连续空间
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    // 分配错误返回
    if (!L->elem) return ERROR;
    // 初始长度0
    L->length = 0;
    // 当前分配的空间大小
    L->listSize = LIST_INIT_SIZE;
    return OK;
}

/**
    向顺序表插入元素
    初始条件：L已经存在，且1<=i<=ListLength_Sq(L)+1
    操作结果：在L中第i个位置之前插入新元素e，L长度 + 1
 */
Status ListInsert_Sq(Seqlist* L, int i, ElemType e) {
    if (!L->elem) return ERROR;
    // 在第i个位置之前插入新元素，边界条件
    if (i < 1 || i > L->length + 1) return ERROR;
    // 超过最大容量
    if (L->length >= L->listSize) {
        // 增加内存分配
        ElemType * newbase = (ElemType *)realloc(L->elem, (L->listSize + LIST_INCREMENT) * sizeof(ElemType));
        // 内存分配失败
        if (!newbase) return ERROR;
        // 新的内存基地址
        L->elem = newbase;
        // 内存容量增大
        L->listSize += LIST_INCREMENT;
    }
    // 插入位置
    ElemType * q = &(L->elem[i-1]);
    // 插入位置及之后的元素后移
    for(ElemType * p = &(L->elem[L->length - 1]); p >= q; --p) *(p + 1) = *p;
    // 插入e
    *q = e;
    
    /*
    for (int j = L->length; j >= i; j--) {
        L->elem[j] = L->elem[j-1];
    }
    L->elem[i - 1] = e;
     */
    // 长度增加
    L->length += 1;
    return OK;
}

/**
    顺序表取值
    初始条件：L存在，并且 1 < i < L->length
    操作结果：返回 i元素 e
 */
Status ListGet_Sq(Seqlist L, int i, ElemType * e) {
    // 边界条件
    if (i < 1 || i > L.length) return ERROR;
    // 将第i-1个元素存储在e
    *e = L.elem[i - 1];
    return OK;
}

/**
    查找顺序表元素
    初始条件：L存在
    操作结果：返回L中元素值为e的元素的位置，若不存在返回0
 */
int ListLocate_Sq(Seqlist L, ElemType e) {
    if (L.length == 0) return 0;
    int i;
    for (i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            return i + 1;
        }
    }
    return 0;
}


/**
    顺序表删除元素
    初始条件：L存在，并且 1 < i < L->length
    操作结果：删除并返回e
 */
Status ListDele_Sq(Seqlist * L, int i, ElemType * e) {
    if (!L->elem) return ERROR;
    // 边界条件
    if (i<1 || i>L->length) return ERROR;
    // 将i后的元素前移
//    *e = L->elem[i-1];
//    for (int j = i; j < L->length; j ++) {
//        L->elem[j - 1] = L->elem[j];
//    }
    
    // 被删除元素的位置
    ElemType * p = &(L->elem[i-1]);
    // 保存被删除的元素
    *e = *p;
//    for (ElemType * q = p; q < &(L->elem[L->length-1]); q ++) *q = *(q+1);
    // 被删除元素之后的元素前移
    for (++p; p <= &(L->elem[L->length-1]); ++p) *(p-1) = *p;
//    for (p; p <= &(L->elem[L->length-1]); ++p) *(p-1) = *p;
    
    L->length -= 1;
    return OK;
}

/**
    长度
 */
int listLength_Sq(Seqlist L) {
    return L.length;
}

/**
    判断顺序表是否为空表
 */
Status ListEmpth_Sq(Seqlist L) {
    return L.length == 0;
}

/**
    清空顺序表
 */
Status ListClear_Sq(Seqlist * L) {
    L->length = 0;
    return OK;
}

/**
    打印顺序表
 */
void ListPrint_Sq(Seqlist L) {
    for (int i = 0; i < L.length; i ++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

void SwapList_Sq(Seqlist *L, int i, int j) {
    if (L && i < L->length && j < L->length) {
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

/*
    合并两个有序顺序表
    初始条件：La，Lb有序
    操作结果：合并后Lc也有序
 */
Status MergeList_Sq(Seqlist La, Seqlist Lb, Seqlist * Lc) {
    ElemType * pa = La.elem;
    ElemType * pb = Lb.elem;
    
    Lc->listSize = La.length + Lb.length;
    // 存储空间分配
    ElemType * pc = Lc->elem = (ElemType *)malloc(sizeof(Lc->listSize * sizeof(ElemType)));
    
    if (!Lc->elem) return ERROR;
    // La最后一个元素地址
    ElemType * pa_last = La.elem + La.length - 1;
    // Lb最后一个元素地址
    ElemType * pb_last = Lb.elem + Lb.length - 1;
    
    // 合并
    while (pa <= pa_last && pb <= pb_last) {
        // 比较pa，pb的值
        if (*pa <= *pb) {
//            *pc = *pa;
//            pc += 1;
//            pa += 1;
            
            // 去除重复
            if (*pa == *pb) {
                pb += 1;
            }
            
            *pc++ = *pa++;
            Lc->length++;
        } else {
            *pc++ = *pb++;
            Lc->length++;
        }
    }
    
    // 插入La剩余元素
    while (pa <= pa_last) {
        *pc++ = *pa++;
        Lc->length++;
    }
    // 插入Lb剩余元素
    while (pb <= pb_last) {
        *pc++ = *pb++;
        Lc->length++;
    }
    return OK;
}

void test() {
    int i = 1;
    printf("i=%d\n", i);
    printf("++i=%d，i=%d\n", ++i, i);
    printf("i++=%d，i=%d\n", i++, i);
    
    int a[3] = {1, 100, 1000};
    int *pa = a;
    // * 和 ++ 同等优先级，按照结合顺序运算
    // 先执行 *pa = 10，再执行 pa++
    // *pa++ = 10;
    
    // 先执行pa++，pa++这个表达式的值没变，但是pa已经自加1，所以pa指向的是第二个元素了
    // 后执行赋值，pa++的地址仍然是pa，所以改变的是第一个元素a[0]
    *(pa++) = 10;
    
    printf("*pa=%d\n",*pa);
    printf("a[0]=%d\n", a[0]);
    printf("a[1]=%d\n", a[1]);
}
