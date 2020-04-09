#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define OK 1
#define Error -1

typedef int Status;
typedef int ElemType;

// 顺序表结构
typedef struct {
    // 存储空间的基地址
    ElemType * elem;
    // 当前长度 
    int length;
    // 总的存储容量
    int listSize;
} Sqlist;

/* 
    初始化顺序表 Sqlist
    操作结果：构造一个空的线性表L
 */
Status InitList_Sq(Sqlist *L) {
    // 分配LIST_INIT_SIZE大小的连续空间
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    // 分配错误返回
    if (!L->elem) return Error;
    // 初始长度0
    L->length = 0;
    // 当前分配的空间大小
    L->listSize = LIST_INIT_SIZE;
    return OK;
}

int main() {
    return 0;
}