
//
//  AOV.c
//  图
//
//  Created by miaokii on 2020/5/11.
//  Copyright © 2020 ly. All rights reserved.
//

#include "AOV.h"
#include "DFS.h"
#include "stdlib.h"
#include "SeqGroup.h"

#define MaxEdge  20
#define MaxVex  14

/// 创建一个邻接矩阵
/// @param G G
void aov_make_seq_graph(MGraph *G) {
    
    G->numEdges = MaxEdge;
    G->numNodes = MaxVex;
    
    for (int i = 0; i < G->numNodes; i++) {
        G->vexs[i] = 65 + i;
    }
    
    for (int i = 0; i < G->numNodes; i++) {
        for (int j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = 0;
        }
    }
    
    G->arc[0][4]=1;
    G->arc[0][5]=1;
    G->arc[0][11]=1;
    G->arc[1][2]=1;
    G->arc[1][4]=1;
    G->arc[1][8]=1;
    G->arc[2][5]=1;
    G->arc[2][6]=1;
    G->arc[2][9]=1;
    G->arc[3][2]=1;
    G->arc[3][13]=1;
    G->arc[4][7]=1;
    G->arc[5][8]=1;
    G->arc[5][12]=1;
    G->arc[6][5]=1;
    G->arc[8][7]=1;
    G->arc[9][10]=1;
    G->arc[9][11]=1;
    G->arc[10][13]=1;
    G->arc[12][9]=1;
}

/// 创建一个邻接表
void aov_make_link_graph(LinkGraph *GL){
    
    MGraph MG;
    aov_make_seq_graph(&MG);
    
    // 创建
    *GL = (LinkGraph)malloc(sizeof(LinkGraph));
    EdgeNode * e;
    
    (*GL)->arc_num = MG.numEdges;
    (*GL)->node_num = MG.numNodes;
    
    for (int i = 0; i < MG.numNodes; i++) {
        (*GL)->adjList[i].data = MG.vexs[i];
        (*GL)->adjList[i].in = 0;
        (*GL)->adjList[i].firstEdge = NULL;
    }
    
    for (int i = 0; i < MG.numEdges; i++) {
        for (int j = 0; j < MG.numEdges; j++) {
            if (MG.arc[i][j] == 1) {
                // 边表节点
                e = (EdgeNode *)malloc(sizeof(EdgeNode));
                // 边表节点的下标
                e->adjvex = j;
                // 该节点的next
                e->next = (*GL)->adjList[i].firstEdge;
                // 当前节点的下一个节点
                (*GL)->adjList[i].firstEdge = e;
                // 入度+1
                (*GL)->adjList[j].in += 1;
            }
        }
    }
}

/// 拓扑排序
Status aov_top_logical_sort(LinkGraph GL){
    //
    EdgeNode *e;
    // 存储入度为0的顶点
    int * stack = (int *)malloc(sizeof(int) * GL->node_num);
    // 栈顶
    int top = 0;
    // 统计顶点个数
    int count = 0;
    // 控制
    int i, k;
    // 栈顶元素
    int gettop;
    
    // 1、将入度为0的顶点入栈
    for (i = 0; i < GL->node_num; i++) {
        // 入栈
        if (GL->adjList[i].in == 0) {
            stack[++top] = i;
        }
    }
    printf("top = %d\n", top);
    
    // 2、循环栈结构
    while (top != 0) {
        // 出栈
        gettop = stack[top--];
        printf("%c -> ", GL->adjList[gettop].data);
        // 输出顶点数+1
        count++;
        // 遍历与栈顶相连接的弧
        for (e = GL->adjList[gettop].firstEdge; e; e = e->next) {
            // 与gettop相连接的顶点
            k = e->adjvex;
            // 将k的入度-1
            // 判断入度为0的话加入到栈
//            GL->adjList[k].in -= 1;
//            if (!GL->adjList[k].in)
//                stack[++top] = k;

            if (!(--GL->adjList[k].in)) {
                stack[++top] = k;
            }
        }
    }
    
    printf("\n");
    // 判断是否所有节点都已经输出，否则没有拓扑排序
    if (count < GL->node_num)
        return FALSE;
    return TRUE;
}

Status TopologicalSort(LinkGraph GL) {
    EdgeNode * e;
    //
    int i, k;
    // 获取栈顶元素值
    int gettop;
    int top = 0;
    // 统计输出的顶点个数
    int count = 0;
    int * stack = (int *)malloc(GL->node_num * sizeof(int));
    
    // 1、遍历邻接表，顶点表
    for (i=0; i < GL->node_num; i++) {
        if (GL->adjList[i].in == 0) {
            stack[++top] = i;
        }
    }
    printf("top = %d\n", top);
    
    // 2、循环栈结构（当栈中没有元素，循环终止）
    while (top != 0) {
        // 1、出栈
        gettop = stack[top--];
        printf("%d -> ", GL->adjList[gettop].data);
        // 2、统计
        count++;
        // 3、
        for (e = GL->adjList[gettop].firstEdge; e; e = e->next) {
            // gettop连接的顶点
            k = e->adjvex;
            // gettop连接顶点入度减1，如果度为0，加入到栈
            if (!(--GL->adjList[k].in)) {
                stack[++top] = k;
            }
        }
    }
    
    //
    printf("\n");
    
    //
    if (count < GL->node_num)
        return ERROR;
    return OK;
}

