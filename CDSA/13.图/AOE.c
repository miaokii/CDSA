
//
//  AOE.c
//  图
//
//  Created by miaokii on 2020/5/11.
//  Copyright © 2020 ly. All rights reserved.
//

#include "AOE.h"
#include "LinkGroup.h"
#include "DFS.h"
#include "stdlib.h"

#define MaxEdge  13
#define MaxNode  10

/// 使用邻接矩阵生成邻接表
void aoe_make_seq_graph(MGraph *MG) {
    MG->numNodes = MaxNode;
    MG->numEdges = MaxEdge;
    
    // 初始化节点
    for (int i = 0; i < MaxNode; i++) {
        MG->vexs[i] = 65 + i;
    }
    
    // 初始化权值
    for (int i = 0; i < MaxNode; i++) {
        for (int j = 0; j < MaxNode; j++) {
            if (i == j)
                MG->arc[i][j] = 0;
            else
                MG->arc[i][j] = INFINITY;
        }
    }
    
    // 节点关系，设置权重
    MG->arc[0][1]=3;
    MG->arc[0][2]=4;
    MG->arc[1][3]=5;
    MG->arc[1][4]=6;
    MG->arc[2][3]=8;
    MG->arc[2][5]=7;
    MG->arc[3][4]=3;
    MG->arc[4][6]=9;
    MG->arc[4][7]=4;
    MG->arc[5][7]=6;
    MG->arc[6][9]=2;
    MG->arc[7][8]=5;
    MG->arc[8][9]=3;
}

void aoe_make_link_graph(LinkGraph *GL) {
    MGraph MG;
    aoe_make_seq_graph(&MG);
    
    *GL = (LinkGraph)malloc(sizeof(LinkGraph));
    (*GL)->arc_num = MG.numEdges;
    (*GL)->node_num = MG.numNodes;
    
    for (int i = 0; i < MG.numNodes; i++) {
        (*GL)->adjList[i].data = MG.vexs[i];
        (*GL)->adjList[i].in = 0;
        (*GL)->adjList[i].firstEdge = NULL;
    }
    
    EdgeNode * temp;
    for (int i = 0; i < MG.numNodes; i++) {
        for (int j = 0; j < MG.numNodes; j++) {
            if (MG.arc[i][j] != 0 && MG.arc[i][j] < INFINITY) {
                temp = (EdgeNode *)malloc(sizeof(EdgeNode));
                temp->adjvex = j;
                temp->weight = MG.arc[i][j];
                temp->next = (*GL)->adjList[i].firstEdge;
                (*GL)->adjList[i].firstEdge = temp;
                (*GL)->adjList[j].in += 1;
            }
        }
    }
}

/* 关于AOE网图存储的属性 */
int * etv, *ltv;    /* 最早发生时间/最晚发生时间 */
int * stack2;       /* 用于存储拓扑序列的栈 */
int top2;           /* stack2栈顶 */

/*
 etv计算：
    当k=0, etv[k] = 0
    当k!=0且<Vi,Vk>属于P[k]，P[k]表示所有到达顶点Vk的弧的集合
        etv[k] = max(etv[i] + len<Vi, Vk>)
 */

/* 拓扑排序，此时可以计算出etv数组 */
Status aov_sort(LinkGraph G) {
    
    EdgeNode *e;
    // 输出顶点的个数，判断是否存在回路
    int count = 0;
    // 栈顶
    int top = 0, gettop;
    // 存储入度为0的顶点
    int * stack = (int *)malloc(sizeof(int) * G->node_num);
    
    // 遍历顶点表，判断入度，为0，将序号入栈
    for (int i = 0; i < G->arc_num; i++) {
        if (G->adjList[i].in == 0) {
            stack[++top] = i;
        }
    }
    
    // stack2 栈顶
    top2 = 0;
    // 初始化序列栈
    stack2 = (int *)malloc(sizeof(int) * G->node_num);
    // 初始化etv
    etv = (int *)malloc(sizeof(int) * G->node_num);
    for (int i = 0; i < G->node_num; i++) {
        etv[i] = 0;
    }
    while (top != 0) {
        // 存储在栈顶的 顶点序号
        gettop = stack[top--];
        printf("%c -> ", G->adjList[gettop].data);
        count ++;
        
        // 将弹出的顶点序号入到排序栈
        stack2[++top2] = gettop;
        
        for (e = G->adjList[gettop].firstEdge; e; e = e->next) {
            // 将gettop顶点的连接顶点的入度-1，如果-1后入度为0，加入到栈
            if (!(--G->adjList[e->adjvex].in)) {
                stack[++top] = e->adjvex;
            }
            
            // 各顶点事件的最早发生时间etv值
            if (etv[gettop] + e->weight > etv[e->adjvex]) {
                etv[e->adjvex] = etv[gettop] + e->weight;
            }
        }
    }
    printf("\n");
    
    if (count < G->node_num)
        return ERROR;
    else
        return OK;
    
}

void aoe_critical_path(LinkGraph G) {
    aov_sort(G);
    
    int gettop, k, ete, lte;
    EdgeNode *e;
    
    printf("etv：\n");
    for (int i = 0; i < G->node_num; i++) {
        printf("etv[%d] = %d\n", i, etv[i]);
    }
    printf("\n");
    
    // 事件最晚发生时间
    ltv = (int *)malloc(sizeof(int) * G->node_num);
    // 初始化ltv
    for (int i = 0; i < G->node_num; i++) {
        ltv[i] = etv[G->node_num - 1];
    }
    
    while (top2 != 0) {
        gettop = stack2[top2--];
        for (e = G->adjList[gettop].firstEdge; e; e = e->next) {
            k = e->adjvex;
            if (ltv[k] - e->weight < ltv[gettop]) {
                ltv[gettop] = ltv[k] - e->weight;
            }
        }
    }
    
    printf("ltv：\n");
    for (int i = 0; i < G->node_num; i++) {
        printf("ltv[%d] = %d\n", i, ltv[i]);
    }
    printf("\n");
    
    for (int j = 0; j< G->node_num; j++) {
        for (e = G->adjList[j].firstEdge; e; e = e->next) {
            k = e->adjvex;
            ete = etv[j];
            lte = ltv[k] - e->weight;
            if (ete == lte) {
                printf("<%c-%c> length: %d\n", G->adjList[j].data, G->adjList[k].data, e->weight);
            }
        }
    }
}

// 求关键路径
void CriticalPath(LinkGraph GL) {
    EdgeNode *e;
    int i, gettop, k, j;
    int ele, lte;
    int top2;
//    TopologicalSort(GL);
    
    int * etv = (int *)malloc(GL->node_num * sizeof(int));
    int * ltv = (int *)malloc(GL->node_num * sizeof(int));
    
    // 1、打印etv事件
    for (int i = 0; i < GL->node_num; i++) {
        printf("etv[%d] = %d", i, etv[i]);
    }
    printf("\n");
    
    // 2、lte
    for (int i = 0; i < GL->node_num; i++) {
        ltv[i] = etv[GL->node_num - i];
    }
    
    // 3、
}
