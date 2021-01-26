//
//  LinkListTest.c
//  2.链表
//
//  Created by miaokii on 2021/1/26.
//  Copyright © 2021 ly. All rights reserved.
//

#include "LinkListTest.h"
#include "stdlib.h"

/// 合并两个有序链表
///
/// @param La 链表a
/// @param Lb 链表b
///
/// 已知两个链表A和B分别表示两个集合，其元素递增排列，将AB合并，不允许有相同元素，不占用其他空间
/// eg：La = {1, 3, 5, 6, 7, 9}; Lb = {2, 4, 5, 6, 8, 10}; 输出La = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
void Merge(LinkList *La, LinkList *Lb) {
    
    if ((*La)==NULL || (*Lb)==NULL)
        return;
    
    LinkList pa = (*La)->next;
    LinkList pb = (*Lb)->next;
    
    // pa前一个节点
    LinkList prepa = *La;
    // pb前一个节点
    LinkList prepb = *Lb;
    
    LinkList temp;
    
    while (pa && pb) {
        ElemType a = pa->data;
        ElemType b = pb->data;
        // 如果a>b，将b插入到a之前，比较b的下一个
        if (a > b) {
            // temp赋值
            temp = pb;
            // 更改pa的前一个节点的后继节点为temp，即插入temp到La
            prepa->next = temp;
            // 更改prepb的后继节点为pb的next
            prepb->next = temp->next;
            // 更改pb
            pb = prepb->next;
            // 连接起a链表
            prepa->next->next = pa;
            // 更改pa前节点
            prepa = prepa->next;
        }
        // a=b，删除b，比较b的下一个，同时a后移
        else if (a == b) {
            // 设置删除节点
            temp = pb;
            // 删除temp后连接起lb
            prepb->next=pb->next;
            // 设置当前当次比较节点
            pb = prepb->next;
            // 设置a的前节点
            prepa = pa;
            // 设置a节点
            pa = prepa->next;
            // 释放
            free(temp);
        }
        // a<b，比较a的下一个
        else {
            // 设置a的前节点
            prepa = pa;
            // 设置a节点
            pa = prepa->next;
        }
    }
    
    // 剩余节点，pa本身就是prepa的后继，所以可以直接连接
    prepa->next = pb ? pb : pa;
}

/// 两个集合的交集
/// @param La 链表a
/// @param Lb 链表b
///
/// 已知两个链表A和B分别表示两个集合，其元素递增排列，求A与B的交集，并存储在A链表中
/// eg：La = {2,4,6,8}; Lb = {4,6,8,10}; 输出La = {4,6,8}
void Intersection(LinkList *La, LinkList Lb) {
    if ((*La)==NULL || Lb==NULL)
        return;
    LinkList pa = (*La)->next;
    LinkList pb = Lb->next;
    
    LinkList prea = (*La);
    LinkList temp;
    
    while (pa) {
        // 如果a<b，删除a，pa后移
        // 如果pb已经到结尾，说明pa剩余元素和pb没有相等的了，交集为空
        // 所以删除pb所有元素
        if (pb==NULL || pa->data < pb->data) {
            temp = pa;
            // 连接temp前后
            prea->next = pa->next;
            // 释放pa
            free(temp);
            // 设置pa
            pa = prea->next;
        }
        // 如果ab相等，同时后移
        else if (pa->data == pb->data) {
            // pa前驱
            prea = pa;
            // pa后移
            pa = prea->next;
            // pb后移
            pb = pb ->next;
        }
        // 如果b<a，pb后移
        else {
            pb = pb->next;
        }
    }
}

/// 旋转链表
/// @param L 链表
/// 将链表中所有节点的链接方向"原地旋转"，不使用其他空间
/// eg：L={0,2,4,6,8,10}，逆转后：L = {10,8,6,4,2,0}
/// 使用头插法再插入一遍
void Reverse(LinkList *L) {
    if ((*L)==NULL)
        return;
    
    // 记录L
    LinkList p = (*L)->next;
    // 将L设置空，并不删除元素，然后将p依次头插到L中
    (*L)->next = NULL;
    LinkList temp;
    
    while (p) {
        temp = p;
        // p下一个
        p = p->next;
        // 首次插入时，L的next为null，此时temp就是尾节点
        // 否则next就是首元节点的next
        temp->next = (*L)->next;
        // 改变头节点
        (*L)->next = temp;
    }
}

/// 删除有序链表区间内的值
/// @param L 链表
/// @param mink 区间左
/// @param maxk 区间右
void DeleteRangeList(LinkList *L, ElemType mink, ElemType maxk) {
    if ((*L)==NULL)
        return;
    LinkList p = (*L)->next;
    /* // 方法1：直接判断 元素，删除区间内的元素
    LinkList prep = *L;
    while (p) {
        // 删除
        if (p->data >= mink && p->data <= maxk) {
            LinkList temp = p;
            prep->next = temp->next;
            free(temp);
        } else if (p->data > maxk) {
            break;
        } else {
            prep = p;
        }
        p = prep->next;
    }
     */
    
    // 方法2：找到开始删除的位置，到结束位置，之间的全部删除
    LinkList minpre = *L;
    while (p) {
        // 找出小于mink的最后一个节点，也就是开始删除的前一个节点
        if (p->next && p->next->data >= mink && p->data < mink) {
            minpre = p;
        }
        // 找到删除结束的前一个节点的位置，就是p
        else if (p->data > maxk) {
            break;
        }
        p = p->next;
    }
    
    // minpre到p之间的所有节点都要删除
    LinkList q = minpre->next;
    while (q && q != p) {
        minpre->next = q->next;
        free(q);
        q = minpre->next;
    }
}

/// 循环移动p个位置
/// @param L 链表
/// @param count  链表长度
/// @param m 移动长度，m<0向右移动，否则向左移动
/// eg：L={1, 2, 3, 4, 5, 6} m=-1  =>  {2,3,4,5,6,1} 相当于m=5
/// eg：L={1, 2, 3, 4, 5, 6} m=3  =>  {4,5,6,1,2,3}
void Translate(LinkList *L, int count, int m) {
    if ((*L)==NULL || m == 0)
        return;
    
    LinkList p = (*L)->next;
    LinkList prep = *L;
    // 移动的距离
    int l = abs(m)%count;
    // 向右移动和向右移动关系
    if (m > 0) {
        l = count-l;
    }
    
    while (l>0) {
        prep = p;
        p = prep->next;
        l--;
    }
    prep->next = NULL;
    LinkList q = p;
    while (q->next) {
        q = q->next;
    }
    q->next = (*L)->next;
    (*L)->next = p;
}

/// 寻找主元素
/// @param list 链表
/// @param n 链表长度
int MainElement(ElemType * list, int n) {
    return 1;
}

/// 删除链表中绝对值相同的元素，只保留第一次出现的元素
/// @param L 链表
/// @param n 长度
void deleteAbsRepeatNode(LinkList *L, int n){
    
}
