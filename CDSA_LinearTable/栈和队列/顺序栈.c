//
//  顺序栈.c
//  栈和队列
//
//  Created by miaokii on 2020/4/30.
//  Copyright © 2020 ly. All rights reserved.
//

#include "顺序栈.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

/// 创建一个空栈
Status InitSeqStack(SeqStack *s) {
    /*
     顺序表中的元素不用初始化，用的时候初始化
     */
    s->top = -1;
    return OK;
}

/// 将栈置空
Status ClearSeqStack(SeqStack *s) {
    // 不需要将data清空
    s->top = -1;
    return OK;
}

/// 判断是否为空栈
Status SeqStackEmpty(SeqStack s) {
    if (s.top == -1)
        return TRUE;
    else
        return FALSE;
}

/// 返回栈的长度
int SeqStackLength(SeqStack s) {
    return s.top + 1;
}

/// 获取栈顶元素
Status GetSeqStackTop(SeqStack s, ElemType *e) {
    if (s.top == -1) return ERROR;
    *e = s.data[s.top];
    return OK;
}

/// 向栈中插入一个元素，入栈
Status PushSeqStack(SeqStack *s, ElemType e) {
    // 满了
    if (s->top == MAXSIZE - 1) return ERROR;
    s->top += 1;
    s->data[s->top] = e;
    return OK;
}

/// 出栈
Status PopSeqStack(SeqStack *s, ElemType *e) {
    // 空栈
    if (s->top == -1) return ERROR;
    *e = s->data[s->top];
    s->top -= 1;
    return OK;
}

/// 打印栈，从栈底到栈顶
void SeqStackPrint(SeqStack s) {
    int i = 0;
    while (i <= s.top) {
        printf("%d ", s.data[i++]);
    }
    printf("\n");
}

