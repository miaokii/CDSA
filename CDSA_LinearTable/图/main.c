//
//  main.c
//  图
//
//  Created by miaokii on 2020/4/29.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "SeqGroup.h"
#include "LinkGroup.h"
#include "DFS.h"
#include "BFS.h"
#include "seqQueue.h"

/**
 图：由顶点的有穷非空集合和顶点的集合组成
    G(V,E) G表示为图，V是图G中的顶点集合，E是图G的边的集合
 完全图：任意顶点之间都有直接连接
 
 存储图（邻接矩阵）：
    顶点数组：存储顶点值
    二维数组：存储顶点之间的关系
 */


void seqGroupTest() {
    MGraph G;
    CreateMGraph(&G);
    printMGroup(G);
}

void linkGroupTest() {
    GraphLink G;
    CreateGraph(&G);
    putGraph(G);
}

void dfs_seq_group() {
    MGraph G;
    makeAMGraph(&G);
    DFSSeqTravese(G);
    printf("\n");
}

void dfs_link_group() {
    GraphLink G;
    makeLinkGraph(&G);
    putGraph(G);
    
    printf("\n");
    DFSLinkGraph(G);
    printf("\n");
}

void bfs_seq_group() {
    MGraph G;
    makeAMGraph(&G);
    BFS_Seq_Graph(G);
}

void bfs_link_group() {
    GraphLink G;
    makeLinkGraph(&G);
    BFS_Link_Graph(G);
}

int main(int argc, const char * argv[]) {
    seqGroupTest();
    linkGroupTest();
    dfs_seq_group();
    dfs_link_group();
    bfs_seq_group();
    bfs_link_group();
    return 0;
}
