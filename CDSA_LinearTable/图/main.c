//
//  main.c
//  图
//
//  Created by miaokii on 2020/4/29.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"

/**
 图：由顶点的有穷非空集合和顶点的集合组成
    G(V,E) G表示为图，V是图G中的顶点集合，E是图G的边的集合
 完全图：任意顶点之间都有直接连接
 
 存储图（邻接矩阵）：
    顶点数组：存储顶点值
    二维数组：存储顶点之间的关系
 */

/* 最大顶点数 */
#define MAXVEX 100
/* ∞ */
#define INFINITY 65535

typedef int Status;
typedef char VertexType;
typedef int EdgeType;
typedef struct {
    /* 顶点集合 */
    VertexType vexs[MAXVEX];
    /* 邻接矩阵 表边 */
    EdgeType arc[MAXVEX][MAXVEX];
    /* 当前图中的顶点数和边数 */
    int numNodes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G) {
    int i, j, k, w;
    printf("输入顶点数和边数：\n");
    // 输入顶点和边数
    scanf("%d,%d", &G->numNodes, &G->numEdges);
    printf("顶点数：%d，边数：%d\n", G->numNodes, G->numEdges);
    
    // 输入顶点信息/顶点表
    for (i = 0; i < G->numNodes; i++) {
        scanf("%c", &G->vexs[i]);
    }
    
    // 初始化矩阵
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = INFINITY;
        }
    }
    
    // 输入边的信息
    for (k = 0; k < G->numNodes; k++) {
        printf("输入边（vi,vj）下标i，下标j，权w");
        
    }
    
}

/* 打印图 */
void printMGroup(MGraph G) {
    
}

/* 邻接表的链式存 */

typedef char ElemType;
typedef int BOOL;

#define M 100
#define FALSE -1
#define TRUE 1

/* 节点 */
typedef struct Node{
    /// 弧头的下标，被值向的下标
    int adj_vex_index;
    /// 权重值
    ElemType data;
    /// 边指针
    struct Node * next;
} EdgeNode;

/* 顶点节点表 */
typedef struct vNode {
    /// 顶点的权值
    ElemType data;
    /// 顶点的下一个是谁
    EdgeNode * firstEdg;
}VertexNode, Adjlist[M];

/* 总图的一些信息 */
typedef struct Graph {
    /// 顶点表
    Adjlist adjList;
    /// 边的个数
    int arc_num;
    /// 节点个数
    int node_num;
    /// 是不是有向图
    BOOL is_directed;
}Graph, *GraphLink;

void CreateGraph(GraphLink *g) {
    int i, j, k;
    EdgeNode *p;
    
    // 1、获取顶点，边是否有向
    printf("输入顶点数目，边数和有向？：\n");
    scanf("%d %d %d", &(*g)->node_num, &(*g)->arc_num, &(*g)->is_directed);
    
    // 2、顶点表
    for (i = 0; i < (*g)->node_num; i++) {
        getchar();
        scanf("%c", &(*g)->adjList[i].data);
        (*g)->adjList[i].firstEdg = NULL;
    }
    
    // 2、输入节点信息
    printf("输入边信息：\n");
    for (k = 0; k < (*g)->arc_num; k++) {
        getchar();
        scanf("%d %d", &i, &j);
        
        // 1、新建节点
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        // 2、弧的下标
    }
}


/* DFS遍历 */
// 标记访问数组
BOOL visited[MAXVEX];


void DFS(MGraph G, int i) {
    
}

void DFSTravese(MGraph G) {
    // 1、初始化
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }
    
    // 2、某个顶点
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
