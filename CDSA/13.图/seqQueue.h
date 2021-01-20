//
//  seqQueue.h
//  栈和队列
//
//  Created by miaokii on 2020/5/8.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef seqQueue_h
#define seqQueue_h

#include <stdio.h>
#include "publicDefine.h"

/* 循环队列的顺序存储结构 */
typedef struct {
    int data[MAXSIZE];
    /// 头指针
    int front;
    /// 尾指针，若队列不空，指向队列尾元素的下一个位置
    int rear;
}SeqQueue;

/* 初始化一个空队列Q */
Status InitQueue(SeqQueue *Q);

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(SeqQueue Q);

/* 若队列未满，则插入元素e为Q新的队尾元素 */
Status EnterQueue(SeqQueue *Q,int e);

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
Status DeleteQueue(SeqQueue *Q,int *e);

void PrintSeqQueue(SeqQueue Q);

#endif /* seqQueue_h */
