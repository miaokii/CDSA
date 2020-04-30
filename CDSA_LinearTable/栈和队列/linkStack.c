//
//  linkStack.c
//  栈和队列
//
//  Created by miaokii on 2020/4/30.
//  Copyright © 2020 ly. All rights reserved.
//

#include "linkStack.h"
#include "stdlib.h"

/// 创建一个空栈
Status InitLinkStack(LinkStack *s) {
    s->top = NULL;
    s->count = 0;
    return OK;
}

/// 将栈置空
Status ClearLinkStack(LinkStack *s) {
    LinkList p, temp;
    p = s->top;
    while (p) {
        temp = p;
        p = p->next;
        free(temp);
    }
    
    s->count = 0;
    return OK;
}

/// 判断是否为空栈
Status LinkStackEmpty(LinkStack s) {
    if (s.count == 0) {
        return TRUE;
    }
    return FALSE;
}

/// 返回栈的长度
int LinkStackLength(LinkStack s) {
    return s.count;
}

/// 获取栈顶元素
Status GetLinkStackTop(LinkStack s, ElemType *e) {
    if (s.top == NULL) return ERROR;
    *e = s.top->data;
    return OK;
}

/// 向栈中插入一个元素，入栈
Status PushLinkStack(LinkStack *s, ElemType e) {
    // 新节点
    LinkList temp = (LinkList)malloc(sizeof(Node));
    // 新节点创建成功
    if (!temp) return ERROR;
    // 赋值
    temp->data = e;
    // 新节点的后继节点为当前栈的栈顶
    temp->next = s->top;
    // 修改栈顶
    s->top = temp;
    // +1
    s->count += 1;
    return OK;
}

/// 出栈
Status PopLinkStack(LinkStack *s, ElemType *e) {
    if (s->top == NULL || s->count == 0) return ERROR;
    LinkList temp = s->top;
    *e = temp->data;
    s->top = temp->next;
    s->count -= 1;
    free(temp);
    return OK;
}

/// 打印栈，从栈顶到栈底
void LinkStackPrint(LinkStack s) {
    if (LinkStackEmpty(s)) return;
    LinkList temp = s.top;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
