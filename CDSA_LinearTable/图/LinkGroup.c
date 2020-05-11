//
//  LinkGroup.c
//  图
//
//  Created by Miaokii on 2020/5/5.
//  Copyright © 2020 ly. All rights reserved.
//

#include "LinkGroup.h"
#include "stdlib.h"

/* 邻接表的链式存 */

void CreateGraph(LinkGraph *g) {
    
    *g = (Graph *)malloc(sizeof(Graph));
    
    int i, j, k;
    EdgeNode *p;
    
    // 1、获取顶点，边是否有向
    printf("输入顶点数目,边数和有向？：\n");
    scanf("%d %d %d", &(*g)->node_num, &(*g)->arc_num, &(*g)->is_directed);
    
    // 2、顶点表
    printf("请输入顶点信息\n");
    for (i = 0; i < (*g)->node_num; i++) {
        getchar();
        scanf("%c", &(*g)->adjList[i].data);
        (*g)->adjList[i].firstEdge = NULL;
    }
    
    // 2、输入节点信息
    printf("输入边信息：\n");
    for (k = 0; k < (*g)->arc_num; k++) {
        getchar();
        scanf("%d %d", &i, &j);
        
        // 1、新建节点
        p = (EdgeNode *)malloc(sizeof(EdgeNode));
        // 2、弧的下标
        p->adjvex = j;
        // 3、头插法插入节点
        p->next = (*g)->adjList[i].firstEdge;
        (*g)->adjList[i].firstEdge = p;
        
        // 4、如果是无向图
        if (!(*g)->is_directed) {
            // 1、新建节点
            p = (EdgeNode *)malloc(sizeof(EdgeNode));
            // 2、弧的下标
            p->adjvex = i;
            // 3、头插法插入节点
            p->next = (*g)->adjList[j].firstEdge;
            (*g)->adjList[j].firstEdge = p;
        }
    }
}

void putGraph(LinkGraph G) {
    printf("邻接表中存储的信息：\n");
    for (int i = 0; i < G->node_num; i++) {
        printf("v%d: %c  ", i, G->adjList[i].data);
        EdgeNode * p = G->adjList[i].firstEdge;
        while (p) {
            printf("   ->%c", G->adjList[p->adjvex].data);
            p = p->next;
        }
        printf("\n");
    }
}
