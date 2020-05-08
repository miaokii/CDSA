//
//  BFS.c
//  图
//
//  Created by miaokii on 2020/5/8.
//  Copyright © 2020 ly. All rights reserved.
//

#include "seqQueue.h"
#include "BFS.h"

typedef int BOOL;

/// 访问的标记数组
BOOL bfs_visited[MAXVEX];

void BFS_Seq_Graph(MGraph G) {
    SeqQueue Q;
    InitQueue(&Q);
    
    // 初始化标记数组
    for (int i = 0; i < G.numNodes; i++) {
        bfs_visited[i] = FALSE;
    }
    
    // 非连通图执行多次，联通图之执行一次
    for (int i = 0; i < G.numNodes; i++) {
        if (!bfs_visited[i]) {
            bfs_visited[i] = TRUE;
            printf("%c", G.vexs[i]);
            
            // 入队
            EnterQueue(&Q, i);
            while (!QueueEmpty(Q)) {
                // 出队
                DeleteQueue(&Q, &i);
                for (int j = 0; j < G.numNodes; j++) {
                    if (G.arc[i][j] == 1 && !bfs_visited[j]){
                        bfs_visited[j] = TRUE;
                        printf("%c", G.vexs[j]);
                        EnterQueue(&Q, j);
                    }
                }
            }
        }
    }
    printf("\n");
}


void BFS_Link_Graph(GraphLink G) {
    EdgeNode * p;
    
    SeqQueue Q;
    InitQueue(&Q);
    
    /// 初始化访问状态
    for (int i = 0; i < G->node_num; i++) {
        bfs_visited[i] = FALSE;
    }
    
    for (int i = 0; i < G->node_num; i++) {
        // 当前节点未访问
        if (!bfs_visited[i]) {
            printf("%c ", G->adjList[i].data);
            EnterQueue(&Q, i);
            while (!QueueEmpty(Q)) {
                DeleteQueue(&Q, &i);
                p = G->adjList[i].firstEdg;
                while (p) {
                    if (!bfs_visited[p->adj_vex_index]) {
                        bfs_visited[p->adj_vex_index] = TRUE;
                        printf("%c ", G->adjList[p->adj_vex_index].data);
                        EnterQueue(&Q, p->adj_vex_index);
                    }
                    p = p->next;
                }
            }
        }
    }
    printf("\n");
}
