//
//  seqQueue.c
//  栈和队列
//
//  Created by miaokii on 2020/5/8.
//  Copyright © 2020 ly. All rights reserved.
//

#include "seqQueue.h"

/* 初始化一个空队列Q */
Status InitQueue(SeqQueue *Q){
    Q->front=0;
    Q->rear=0;
    return  OK;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(SeqQueue Q){
    if(Q.front==Q.rear) /* 队列空的标志 */
        return TRUE;
    else
        return FALSE;
}

/* 若队列未满，则插入元素e为Q新的队尾元素 */
Status EnterQueue(SeqQueue *Q,int e){
    if ((Q->rear+1)%MAXSIZE == Q->front)    /* 队列满的判断 */
    return ERROR;
    Q->data[Q->rear]=e;            /* 将元素e赋值给队尾 */
    Q->rear=(Q->rear+1)%MAXSIZE;/* rear指针向后移一位置， */
    /* 若到最后则转到数组头部 */
    return  OK;
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
Status DeleteQueue(SeqQueue *Q,int *e){
    if (Q->front == Q->rear)            /* 队列空的判断 */
        return ERROR;
    *e=Q->data[Q->front];                /* 将队头元素赋值给e */
    Q->front=(Q->front+1)%MAXSIZE;    /* front指针向后移一位置， */
    /* 若到最后则转到数组头部 */
    return  OK;
}

void PrintSeqQueue(SeqQueue Q) {
    int i = 0;
    while ((i+Q.front) != Q.rear) {
        printf("%d ", Q.data[i+Q.front]);
        i = (i+1)%MAXSIZE;
    }
    printf("\n");
}
