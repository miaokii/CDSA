
//
//  AOE.c
//  图
//
//  Created by miaokii on 2020/5/11.
//  Copyright © 2020 ly. All rights reserved.
//

#include "AOE.h"
#include "LinkGroup.h"
#include "DFS.h"
#include "stdlib.h"

/*
 
 在一个表示工程的带权有向图中，用顶点表示事件，用有向边表示活动，用边
 上的权值表示活动的持续时间，这种有向图的边表表示活动的网，称为AOE网
 （Activity On Edge Network）
 
 - 没有入边的顶点称始点或源地点
 - 没有出边的顶点成为终点或汇点
 
 - 路径上的各个活动所持续的时间总和称为路径长度
 - 从源点到汇点的具有最大的路径叫关键路径
 - 在关键路径上的活动叫关键活动
 
 - etv：事件最早发生时间/顶点Vk的最早发生时间
 - ltv：事件最晚发生时间/每个顶点对应事件最晚需要开始的事件，超出此事件将会延误整个工期
 - ete：活动的最早开工时间/弧Ak最早发生时间
 - lte：活动最晚开工时间/弧Ak最晚发生时间/不推迟工期的最晚开工时间
 
 */

// 求关键路径
void CriticalPath(LinkGraph GL) {
    EdgeNode *e;
    int i, gettop, k, j;
    int ele, lte;
    int top2;
    TopologicalSort(GL);
    
    int * etv = (int *)malloc(GL->node_num * sizeof(int));
    int * ltv = (int *)malloc(GL->node_num * sizeof(int));
    
    // 1、打印etv事件
    for (int i = 0; i < GL->node_num; i++) {
        printf("etv[%d] = %d", i, etv[i]);
    }
    printf("\n");
    
    // 2、lte
    for (int i = 0; i < GL->node_num; i++) {
        ltv[i] = etv[GL->node_num - i];
    }
    
    // 3、
}
