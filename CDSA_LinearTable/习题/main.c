//
//  main.c
//  习题
//
//  Created by miaokii on 2020/4/14.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "math.h"

#define Error -1;
#define OK 0;

typedef int ElemType;
typedef int Status;

typedef struct Node {
    ElemType data;
    struct Node * next;
}Node, *LinkList;

/* 使用数组 初始化列表 */
Status InitList(LinkList *L, ElemType * vals, int count) {
    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL) return Error;
    (*L)->next = NULL;
    
    LinkList temp;
    LinkList tail = *L;
    for (int i = 0; i < count; i++) {
        temp = (LinkList)malloc(sizeof(Node));
        temp->data = vals[i];
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
    }
    return OK;
}

void ListInsert(LinkList *L, int i, ElemType e) {
    if (*L==NULL || i < 1) return;
    LinkList p = (*L)->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    LinkList temp = (LinkList)malloc(sizeof(Node));
    if (temp==NULL) return;
    temp->data = e;
    temp->next = p->next;
    p->next = temp;
    return;
}

void ListDelete(LinkList *L, ElemType e) {
    if ((*L) == NULL) return;
    LinkList p = *L;
    while (p->next && p->next->data != e) {
        p = p->next;
    }
    if (p->next == NULL) return;
    p->next = p->next->next;
    free(p);
}

void ListPrint(LinkList L) {
    if (L==NULL) return;
    LinkList p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/*
    1、已知两个链表A和B分别表示两个集合，其元素递增排列，将AB合并，不允许有相同元素，不占用其他空间
       eg：La = {1, 3, 5, 6, 7, 9}; Lb = {2, 4, 5, 6, 8, 10}; 输出La = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
 */

void Merge(LinkList *La, LinkList *Lb) {
    if ((*La)==NULL || Lb==NULL) return;
    LinkList pa = (*La)->next ;
    LinkList pb = (*Lb)->next;
    LinkList temp;
    // 存储当前pa节点的前一个节点
    LinkList prea = (*La);
    // 存储当前pb节点的前一个节点
    LinkList preb = (*Lb);
    while (pa && pb) {
        // pb < pa，插入到pa的前面，也就是prea后面
        if (pa->data > pb->data) {
            // prea后继为pb
            prea->next = pb;
            // 更改preb的下一个节点
            preb->next = pb->next;
            // 更改pb为下一个节点
            pb = pb->next;
            // 将新加入节点的下一个节点设置为pa
            prea->next->next = pa;
            // 改变pa的前一个节点为刚才加入的节点
            prea = prea->next;
            preb = preb->next;
        }
        // 相等，删除掉pb，并且同时后移
        else if (pa->data == pb->data) {
            prea = pa;
            pa = pa->next;
            temp = pb;
            preb->next = pb->next;
            pb = pb->next;
            // 删除
            free(temp);
        }
        // 更改pa
        else {
            prea = pa;
            pa = pa->next;
        }
    }
    // 拼接剩余节点
    prea->next = pb ? pb : pa;
}

/*
    2、  已知两个链表A和B分别表示两个集合，其元素递增排列，求A与B的交集，并存储在A链表中
        eg：La = {2,4,6,8}; Lb = {4,6,8,10}; 输出La = {4,6,8}
 */
void Intersection(LinkList *La, LinkList Lb) {
    if ((*La) == NULL || Lb == NULL) return;
    LinkList pa = (*La)->next;
    LinkList pb = Lb->next;
    LinkList temp, prea = *La;
    // 因为通过La返回，所以遍历完La
    while (pa) {
        // 如果pb到链尾，或者 a < b时，删除a节点
        if ( pb == NULL || pa->data < pb->data) {
            temp = pa;
            prea->next = pa->next;
            pa = pa->next;
            free(temp);
        }
        // 相等的时候同时移动到下一个节点
        else if (pa->data == pb->data) {
            prea = pa;
            pa = pa->next;
            pb = pb->next;
        }
        // b < a 移动pb
        else {
            pb = pb->next;
        }
    }
}

/*
    3、将链表中所有节点的链接方向"原地旋转"，不使用其他空间
        eg：L={0,2,4,6,8,10}，逆转后：L = {10,8,6,4,2,0}
        使用头插法再插入一遍
 */
void Reverse(LinkList *L) {

    if (*L == NULL) return;
    LinkList p = (*L)->next;
    LinkList new;
    (*L)->next = NULL;
    while (p) {
        // 新插入的节点
        new = p;
        // p指向下一个
        p = p->next;
        // 当插入第一个的时候，这个节点就是尾节点，next = null，否则，next就是首元节点的next
//        new->next = ((*L)->next == new) ? NULL : (*L)->next ;
        new->next = (*L)->next;
        // 改变头节点
        (*L)->next = new;
    }


//    if (*L == NULL) return;
//    LinkList p = (*L)->next;
//    LinkList next;
//    (*L)->next = NULL;
//    while (p) {
//        next = p->next;
//        p->next = (*L)->next;
//        (*L)->next = p;
//        p = next;
//    }
}

/*
    4、删除递增有序链表中值⼤于等于mink且⼩于等于maxk(mink,maxk是给定的两个参数,其值可以和表中的元素相同,也可以不同)的所有元素
 */
void DeleteRangeList(LinkList *L, ElemType mink, ElemType maxk) {
    if (*L == NULL) return;
    LinkList p = (*L)->next;
    LinkList pre = *L;
    while (p) {
        if (p->data >= mink && p->data <= maxk) {
            pre->next = p->next;
            free(p);
        } else {
            pre = p;
        }
        p = p->next;
    }
}

void DeleteRangeList1(LinkList *L, ElemType mink, ElemType maxk) {
    LinkList p = (*L)->next;
    LinkList minPre = *L;
    
    while (p) {
        // 寻找 小于mink的最后一个节点，也就是开始删除的前一个节点
        if (p->next && p->next->data >= mink && p->data < mink) {
            minPre = p;
        }
        // p就是删除区域的结尾的下一个节点
        // 此时，minPre-p之间的所有节点都应该删除
        else if (p->data > maxk) {
            break;
        }
        p = p->next;
    }
    
    LinkList q = minPre->next;
    while (q && q != p) {
        minPre->next = q->next;
        free(q);
        q = q->next;
    }
}

/*
    5、设将n(n>1)个整数存放到一维数组R中, 试设计一个在时间和空间两方面都尽可能高效的算法
        将R中保存的序列循环左移p个位置(0<p<n)个位置, 即将R中的数据由(x0,x1,......,xn-1)
        变换为(xp,xp+1,...,xn-1,x0,x1,...,xp-1).
    
    例如: pre[10] = {0,1,2,3,4,5,6,7,8,9},
         n = 10,p = 3;
         pre[10] = {3,4,5,6,7,8,9,0,1,2}
 */

void Translate(ElemType * list, int count, int m) {
    LinkList La;
    InitList(&La, list, count);
    LinkList temp, p = La->next;
    int mov = abs(m%count);
    // p > 0，右移p位，否则左移p位
    if (m > 0) {
        while (mov++ != count - 1) {
            p = p->next;
        }
        temp = p->next;
        p->next = NULL;
        p = temp;
        while (p->next) {
            p = p->next;
        }
        p->next = La->next;
        La->next = temp;
    } else {
        LinkList p = La->next;
        while (--mov > 0) {
            p = p->next;
        }
        temp = p->next;
        p->next = NULL;
        p = temp;
        while (p->next) {
            p = p->next;
        }
        p->next = La->next;
        La->next = temp;
    }
    mov = 0;
    for (p = La->next; p; list[mov++] = p->data, free(p), La->next = p, p = p->next);
    free(p);
    La->next = NULL;
    free(La);
}

/*
    思路：[a0, a1, ..., ap-1, ap, ap+1, ..., an-2, an-1]  (n, p)  ->  [ap, ap+1, ..., an-2, an-1, a0, a1, ..., ap-2, ap-1]
        先整体反转 -> [an-1, an-2, ..., ap+1, ap, ap-1, ..., a1, a0]
        从n-p处分割成两个数组：[an-1, an-2, ..., a]
        
 */

void ReverseArr(ElemType * arr, int l, int r) {
    int i = l, j = r;
    ElemType temp;
    while (i < j) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

void TranslateArr(ElemType * arr, int count, int m) {
    int mov = abs(m%count);
    ReverseArr(arr, 0, count-1);
    if (m > 0) {
        ReverseArr(arr, 0, mov-1);
        ReverseArr(arr, mov, count-1);
    } else {
        ReverseArr(arr, 0, count-mov-1);
        ReverseArr(arr, count-mov, count-1);
    }
}

/*
    6、寻找主元素，如果数组中某个元素出现的次数多余数组元素个数的一半，这个元素就是主元素
    思路：1、如果主元素存在，则个数一定大于数组元素一半
        2、 如果用
 */
int MainElement(ElemType * list, int n) {
    int count = 1;
    int key = list[0];
    
    for ( int i = 1; i < n; i++) {
        if (list[i] == key) count++;
        else {
            if (count > 0) count--;
            else {
                key = list[i];
                count = 1;
            }
        }
    }
     
    if (count > 0) {
        for (int i = count = 0; i < n; i++) {
            if (list[i] == key) count++;
        }
    }
    
    if (count > n/2) return key;
    return -1;
}


int main(int argc, const char * argv[]) {
    
    LinkList La;
    LinkList Lb;
    ElemType a[] = {3, 3, 6, 8, 3, 93};
    ElemType b[] = {2, 3, 5, 9, 12};
    int counta = sizeof(a) / sizeof(ElemType);
    int countb = sizeof(b) / sizeof(ElemType);
    InitList(&La, a, counta);
    InitList(&Lb, a, counta);
    printf("链表a：");
    ListPrint(La);
    printf("链表b：");
    ListPrint(Lb);

//    Merge(&La, &Lb);
//    printf("合并ab：");
//    ListPrint(La);

//    Intersection(&La, Lb);
//    printf("ab交集：");
//    ListPrint(La);
//
//    Reverse(&La);
//    printf("反转a：");
//    ListPrint(La);
    
    int mink = 2, maxk = 10;
    DeleteRangeList(&La, mink, maxk);
    DeleteRangeList1(&Lb, mink, maxk);
    printf("删除La大于%d，小于%d的节点：", mink, maxk);
    ListPrint(La);
    printf("删除Lb大于%d，小于%d的节点：", mink, maxk);
    ListPrint(Lb);
    
    ElemType c[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int countc = sizeof(c)/sizeof(ElemType);
    printf("数组c：");
    for (int i = 0; i < countc; printf("%d ", c[i]), i++);
    printf("\n");
    
//    int mov = -12;
//    Translate(c, countc, mov);
//    printf("\nc移动%d：", mov);
//    for (int i = 0; i < countc; printf("%d ", c[i]), i++);
//    mov = 12;
//    Translate(c, countc, mov);
//    printf("\nc移动%d：", mov);
//    for (int i = 0; i < countc; printf("%d ", c[i]), i++);
    
//    TranslateArr(c, countc, mov);
//    printf("\nc移动%d：", mov);
//    for (int i = 0; i < countc; printf("%d ", c[i]), i++);
//    mov = 12;
//    TranslateArr(c, countc, mov);
//    printf("\nc移动%d：", mov);
//    for (int i = 0; i < countc; printf("%d ", c[i]), i++);
    
    printf("数组La的主元素为：");
    printf("%d\n", MainElement(a, counta));
    
    printf("\n");
    return 0;
}
