//
//  链表栈.h
//  栈和队列
//
//  Created by miaokii on 2020/4/30.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef ____h
#define ____h

#include <stdio.h>
#include "publicDefine.h"
#include "链表.h"

typedef struct {
    /// 栈顶
    LinkList top;
    /// 栈元素个数
    int count;
} LinkStack;

/// 创建一个空栈
Status InitLinkStack(LinkStack *s);

/// 将栈置空
Status ClearLinkStack(LinkStack *s);

/// 判断是否为空栈
Status LinkStackEmpty(LinkStack s);

/// 返回栈的长度
int LinkStackLength(LinkStack s);

/// 获取栈顶元素
Status GetLinkStackTop(LinkStack s, ElemType *e);

/// 向栈中插入一个元素，入栈
Status PushLinkStack(LinkStack *s, ElemType e);

/// 出栈
Status PopLinkStack(LinkStack *s, ElemType *e);

/// 打印栈，从栈底到栈顶
void LinkStackPrint(LinkStack s);

#endif /* ____h */
