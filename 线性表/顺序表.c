#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10
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

/*
    向顺序表插入元素
    初始条件：L已经存在，且1<=i<=ListLength_Sq(L)+1
    操作结果：在L中第i个位置之前插入新元素e，L长度 + 1
 */
Status ListInsert_Sq(Sqlist* L, int i, ElemType e) {
    if (!L->elem) return Error;
    // 在第i个位置之前插入新元素，边界条件
    if (i < 1 || i > L->length + 1) return Error;
    // 超过最大容量
    if (L->length >= L->listSize) {
        // 增加内存分配
        ElemType * newbase = (ElemType *)realloc(L->elem, (L->listSize + LIST_INCREMENT) * sizeof(ElemType));
        // 内存分配失败
        if (!newbase) return Error;
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

/*
    顺序表取值
    初始条件：L存在，并且 1 < i < L->length
    操作结果：返回 i元素 e
 */
Status ListGet_Sq(Sqlist L, int i, ElemType * e) {
    // 边界条件
    if (i < 1 || i > L.length) return Error;
    // 将第i-1个元素存储在e
    *e = L.elem[i - 1];
    return OK;
}

/*
    查找顺序表元素
    初始条件：L存在
    操作结果：返回L中元素值为e的元素的位置，若不存在返回0
 */
int ListLocate_Sq(Sqlist L, ElemType e) {
    if (L.length == 0) return 0;
    int i;
    for (i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            return i + 1;
        }
    }
    return 0;
}


/*
    顺序表删除元素
    初始条件：L存在，并且 1 < i < L->length
    操作结果：删除并返回e
 */
Status ListDele_Sq(Sqlist * L, int i, ElemType * e) {
    if (!L->elem) return Error;
    // 边界条件
    if (i<1 || i>L->length) return Error;
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

/*
    长度
 */
int listLength_Sq(Sqlist L) {
    return L.length;
}

/*
    判断顺序表是否为空表
 */
Status ListEmpth_Sq(Sqlist L) {
    return L.length == 0;
}

/*
    清空顺序表
 */
Status ListClear_Sq(Sqlist * L) {
    L->length = 0;
    return OK;
}

/*
    打印顺序表
 */
void ListPrint_Sq(Sqlist L) {
    for (int i = 0; i < L.length; i ++) {
        printf("%d ", L.elem[i]);
    }
    printf("\n");
}

/*
    合并两个有序顺序表
    初始条件：La，Lb有序
    操作结果：合并后Lc也有序
 */
Status MergeList_Sq(Sqlist La, Sqlist Lb, Sqlist * Lc) {
    ElemType * pa = La.elem;
    ElemType * pb = Lb.elem;
    
    Lc->listSize = La.length + Lb.length;
    // 存储空间分配
    ElemType * pc = Lc->elem = (ElemType *)malloc(sizeof(Lc->listSize * sizeof(ElemType)));
    
    if (!Lc->elem) return Error;
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
    // printf("++i=%d，i=%d\n", ++i, i);
    // printf("i++=%d，i=%d\n", i++, i);
    
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


int main(int argc, const char * argv[]) {
    
    Sqlist L;
    ElemType e;
    Status iStatus;
    
    Sqlist La;
    Sqlist Lb;
    Sqlist Lc;
    
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
