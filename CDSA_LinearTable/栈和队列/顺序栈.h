//
//  顺序栈.h
//  栈和队列
//
//  Created by miaokii on 2020/4/30.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef ____h
#define ____h

#include <stdio.h>
#include "publicDefine.h"


// MARK: - 使用顺序表结构实现栈
typedef struct {
    /// 顺序表
    ElemType data[MAXSIZE];
    /// 栈顶指针
    int top;
}SeqStack;

/// 创建一个空栈
Status InitSeqStack(SeqStack *s);

/// 将栈置空
Status ClearSeqStack(SeqStack *s);

/// 判断是否为空栈
Status SeqStackEmpty(SeqStack s);

/// 返回栈的长度
int SeqStackLength(SeqStack s);

/// 获取栈顶元素
Status GetSeqStackTop(SeqStack s, ElemType *e);

/// 向栈中插入一个元素，入栈
Status PushSeqStack(SeqStack *s, ElemType e);

/// 出栈
Status PopSeqStack(SeqStack *s, ElemType *e);

/// 打印栈，从栈底到栈顶
void SeqStackPrint(SeqStack s);

#endif /* ____h */
