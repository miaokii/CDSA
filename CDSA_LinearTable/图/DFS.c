//
//  DFS.c
//  图
//
//  Created by Miaokii on 2020/5/5.
//  Copyright © 2020 ly. All rights reserved.
//

#include "DFS.h"
#include "stdlib.h"

typedef int BOOL;
#define FALSE 0
#define TRUE 1

/// 访问的标记数组
BOOL visited[MAXVEX];

void makeAMGraph(MGraph *G) {
    int i, j;
    
    //1. 确定图的顶点数以及边数
    G->numEdges=15;
    G->numNodes=9;
    
    /*2.读入顶点信息，建立顶点表 */
    G->vexs[0]='A';
    G->vexs[1]='B';
    G->vexs[2]='C';
    G->vexs[3]='D';
    G->vexs[4]='E';
    G->vexs[5]='F';
    G->vexs[6]='G';
    G->vexs[7]='H';
    G->vexs[8]='I';
    
    /*3. 初始化图中的边表*/
    for (i = 0; i < G->numNodes; i++)
    {
        for ( j = 0; j < G->numNodes; j++)
        {
            G->arc[i][j]=0;
        }
    }
    
    /*4.将图中的连接信息输入到边表中*/
    G->arc[0][1]=1;
    G->arc[0][5]=1;
    
    G->arc[1][2]=1;
    G->arc[1][8]=1;
    G->arc[1][6]=1;
    
    G->arc[2][3]=1;
    G->arc[2][8]=1;
    
    G->arc[3][4]=1;
    G->arc[3][7]=1;
    G->arc[3][6]=1;
    G->arc[3][8]=1;
    
    G->arc[4][5]=1;
    G->arc[4][7]=1;
    
    G->arc[5][6]=1;
    
    G->arc[6][7]=1;
    
    /*5.无向图是对称矩阵.构成对称*/
    for(i = 0; i < G->numNodes; i++)
    {
        for(j = i; j < G->numNodes; j++)
        {
            G->arc[j][i] =G->arc[i][j];
        }
    }
}

void DFS(MGraph G, int i) {
    // i位置已经被访问
    visited[i] = TRUE;
    printf("%c", G.vexs[i]);
    
    // 遍历每个邻接顶点
    for (int j = 0; j < G.numNodes; j++) {
        if (G.arc[i][j] == 1 && !visited[j])
            DFS(G, j);
    }
}

void DFSSeqTravese(MGraph G) {
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }
    
    // 从某一个顶点开始便利
    for (int i = 0 ; i < G.numNodes; i++) {
        // 非连通图 处理
        if (!visited[i]) {
            DFS(G, i);
        }
    }
}


void makeLinkGraph(GraphLink *G) {
    MGraph Mg;
    makeAMGraph(&Mg);
    
    *G = (GraphLink)malloc(sizeof(GraphLink));
    (*G)->arc_num = Mg.numEdges;
    (*G)->node_num = Mg.numNodes;
    
    // 从邻接矩阵中输入顶点信息
    for (int i = 0; i < Mg.numNodes; i++) {
        // 顶点值
        (*G)->adjList[i].data = Mg.vexs[i];
        // 顶点边表初始化
        (*G)->adjList[i].firstEdg = NULL;
    }
    
    // 创建边表
    EdgeNode * node;
    for (int i = 0; i < Mg.numNodes; i++) {
        for (int j = 0; j < Mg.numNodes; j++) {
            // 如果这两个顶点有关联关系
            if (Mg.arc[i][j] == 1) {
                node = (EdgeNode *)malloc(sizeof(EdgeNode));
                // 头插法
                node->next = (*G)->adjList[i].firstEdg;
                node->adj_vex_index = j;
                (*G)->adjList[i].firstEdg = node;
                (*G)->adjList[j].in += 1;
            }
        }
    }
}

void dfs(GraphLink G, int i) {
    visited[i] = TRUE;
    printf("%c", G->adjList[i].data);
    
    EdgeNode * p;
    p = G->adjList[i].firstEdg;
    
    while (p) {
        if (!visited[p->adj_vex_index])
            dfs(G, p->adj_vex_index);
        p = p->next;
    }
    
//    for (int j = 0; j < G->node_num; j++) {
//        if (G->adjList[i].firstEdg->adj_vex_index == j && !visited[j]) {
//            dfs(G, j);
//        }
//    }
}

void DFSLinkGraph(GraphLink G) {
    // 初始化标记数组
    for (int i = 0; i < G->node_num; i++) {
        visited[i] = FALSE;
    }
    
    // 选择一个顶点开始遍历
    for (int i = 0 ; i < G->node_num; i++) {
        if (!visited[i])
            dfs(G, i);
    }
}
