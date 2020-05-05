//
//  SeqGroup.h
//  图
//
//  Created by Miaokii on 2020/5/5.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef SeqGroup_h
#define SeqGroup_h

#include <stdio.h>


/* 最大顶点数 */
#define MAXVEX 100
/* ∞ */
#define INFINITY 0

typedef int Status;
typedef char VertexType;
typedef int EdgeType;

/* 邻接矩阵存储 */
typedef struct {
    /* 顶点集合 */
    VertexType vexs[MAXVEX];
    /* 邻接矩阵 表边 */
    EdgeType arc[MAXVEX][MAXVEX];
    /* 当前图中的顶点数和边数 */
    int numNodes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G);
/* 打印图 */
void printMGroup(MGraph G);


#endif /* SeqGroup_h */
