//
//  main.c
//  栈和队列
//
//  Created by Miaokii on 2020/4/21.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "顺序栈.h"
#include "链表栈.h"

int main(int argc, const char * argv[]) {
    
    printf("======= 顺序栈 =======\n");
    
    SeqStack Stack1;
    InitSeqStack(&Stack1);
    
    ElemType e;
    for (int i = 1; i < 10; i++) {
        e = arc4random() % 100;
        printf("入栈：%d\n", e);
        PushSeqStack(&Stack1, e);
    }
    
    printf("打印栈stack1：");
    SeqStackPrint(Stack1);
    
    printf("stack1长度：%d\n", SeqStackLength(Stack1));
    printf("stack1为空？：%d", SeqStackEmpty(Stack1));
    
    GetSeqStackTop(Stack1, &e);
    printf("\n获取栈顶元素：%d", e);
    
    PopSeqStack(&Stack1, &e);
    printf("\n出栈：%d", e);
    
    GetSeqStackTop(Stack1, &e);
    printf("\n获取栈顶元素：%d", e);
    
    printf("\nstack1长度：%d\n", SeqStackLength(Stack1));
    
    ClearSeqStack(&Stack1);
    printf("将栈置空");
    
    printf("打印栈：");
    SeqStackPrint(Stack1);
    
    printf("======= 链表栈 =======\n");
    
    
    
    printf("\n");
    return 0;
}
