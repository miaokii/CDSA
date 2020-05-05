//
//  SeqGroup.c
//  图
//
//  Created by Miaokii on 2020/5/5.
//  Copyright © 2020 ly. All rights reserved.
//

#include "SeqGroup.h"

void CreateMGraph(MGraph *G) {
    int i, j, k, w;
    printf("输入顶点数和边数：\n");
    // 1、输入顶点和边数
    scanf("%d,%d", &G->numNodes, &G->numEdges);
    printf("顶点数：%d，边数：%d\n", G->numNodes, G->numEdges);
    
    // 2、输入顶点信息/顶点表
    printf("请输入顶点：\n");
    rewind(stdin);
    for (i = 0; i < G->numNodes; i++) {
        scanf("%c", &G->vexs[i]);
    }
    
    // 3、初始化矩阵
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; j++) {
            G->arc[i][j] = INFINITY;
        }
    }
    
    // 4、输入边的信息
    for (k = 0; k < G->numNodes; k++) {
        printf("输入边（vi,vj）下标i，下标j，权w\n");
        scanf("%d,%d,%d", &i, &j, &w);
        
        G->arc[i][j] = w;
        // 无向图的结构对称
        G->arc[j][i] = w;
    }
}

/* 打印图 */
void printMGroup(MGraph G) {
    printf("节点\n");
    for (int i = 0; i < G.numNodes; i++) {
        printf("v%d：%d  ", i, G.vexs[i]);
    }
    printf("\n节点关系：\n");
    for (int i = 0; i < G.numNodes; i++) {
        printf("\n");
        for (int j = 0; j < G.numNodes; j++) {
            printf("%d  ", G.arc[i][j]);
        }
    }
    printf("\n");
}
