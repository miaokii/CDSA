//
//  BFS.c
//  图
//
//  Created by miaokii on 2020/5/8.
//  Copyright © 2020 ly. All rights reserved.
//

#include "BFS.h"
#include "seqQueue.h"

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
    
    ElemType e;
    for (int i = 0; i < G.numNodes; i++) {
        if (!bfs_visited[i]) {
            bfs_visited[i] = TRUE;
            printf("%c ", G.vexs[i]);
            
            // 入队
            EnterQueue(&Q, i);
            while (!QueueEmpty(Q)) {
                // 出队
                DeleteQueue(&Q, &e);
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
}


void BFS_Link_Graph(GraphLink G) {
    
}
