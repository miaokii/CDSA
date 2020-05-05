//
//  LinkGroup.h
//  图
//
//  Created by Miaokii on 2020/5/5.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef LinkGroup_h
#define LinkGroup_h

#include <stdio.h>

/* 邻接表存储 */

typedef int BOOL;
typedef char ElemType;

/* 邻接表的链式存 */

#define M 100
#define FALSE -1
#define TRUE 1

/* 邻接表节点 */
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

void CreateGraph(GraphLink *g);
void putGraph(GraphLink G);

#endif /* LinkGroup_h */
