//
//  main.c
//  栈和队列
//
//  Created by Miaokii on 2020/4/21.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "time.h"


#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0
/// 存储空间默认分配大小
#define MAXSIZE 20

typedef int Status;
typedef int ElemType;

// MARK: - 使用顺序表结构实现栈
typedef struct {
    ElemType data[MAXSIZE];
    /// 栈顶指针
    int top;
}SqStack;

/// 创建一个空栈
Status InitStack(SqStack *s) {
    /*
     顺序表中的元素不用初始化，用的时候初始化
     */
    s->top = -1;
    return OK;
}

/// 将栈置空
Status ClearStack(SqStack *s) {
    // 不需要将data清空
    s->top = -1;
    return OK;
}

/// 判断是否为空栈
Status StackEmpty(SqStack s) {
    if (s.top == -1)
        return TRUE;
    else
        return FALSE;
}

/// 返回栈的长度
int StackLength(SqStack s) {
    return s.top + 1;
}

/// 获取栈顶元素
Status GetTop(SqStack s, ElemType *e) {
    if (s.top == -1) return ERROR;
    *e = s.data[s.top];
    return OK;
}

/// 向栈中插入一个元素，入栈
Status PushStack(SqStack *s, ElemType e) {
    // 满了
    if (s->top == MAXSIZE - 1) return ERROR;
    s->top += 1;
    s->data[s->top] = e;
    return OK;
}

/// 出栈
Status PopStack(SqStack *s, ElemType *e) {
    // 空栈
    if (s->top == -1) return ERROR;
    *e = s->data[s->top];
    s->top -= 1;
    return OK;
}

/// 打印栈，从栈底到栈顶
void StackPrint(SqStack s) {
    int i = 0;
    while (i <= s.top) {
        printf("%d ", s.data[i]);
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
