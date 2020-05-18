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
#include "publicDefine.h"

/* 邻接表的链式存 */
#define M 100

/* 边表节点 */
typedef struct EdgeNode{
    /// 邻接点域，存储顶点对应的下标
    int adjvex;
    /// 权重值，非网图不需要
    int weight;
    /// 指向下一个邻接点
    struct EdgeNode * next;
} EdgeNode;

/* 顶点节点表 */
typedef struct vNode {
    /// 顶点的值
    ElemType data;
    /// 顶点的下一个是谁
    EdgeNode * firstEdge;
    /// 顶点的入度
    int in;
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
    Bool is_directed;
}Graph, *LinkGraph;

/// 创建一个邻接表
/// @param g 表
void CreateGraph(LinkGraph *g);

/// 打印邻接表
/// @param G 表
void putGraph(LinkGraph G);

#endif /* LinkGroup_h */
