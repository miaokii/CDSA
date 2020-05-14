//
//  AOV.h
//  图
//
//  Created by miaokii on 2020/5/11.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef AOV_h
#define AOV_h

#include <stdio.h>
#include "LinkGroup.h"

/*
 拓扑排序
 有一个表示工程的有向图中，用顶点表示活动，用弧表示活动之间的优先关系，这样的有向图为顶点表示活动的网，称之为AOV网（Activity On Vertex Network）
 
 G=(V,E)是一个具有n个顶点的有向图，V中的顶点序列号为V1，V2，...，Vn，若满足从顶点Vi到Vj有一条路径，则在顶点序列Vi必须在Vj之前，成这样的顶点序列为拓扑序列
 拓扑排序是对一个有向图构造拓扑序列的过程
 
 - 如果网中的全部顶点被输出，则说明图中不存在环
 - 如果输出的顶点数少了，说明网中存在环
 
 思路：从AOV网中找到一个入度为0的顶点输出，然后删除该节点，同时删除以该节点为尾的弧。重复此步骤，知道输出全部顶点或者AOV网中不存在入度为0的点
 
 实现：用一个栈来存储AOV网中入度为0的顶点
    - 栈存储入度为0的点
    - 遍历AOV网中的顶点，判断度为0全部入栈
 */


/// 创建一个邻接表
void aov_make_link_graph(LinkGraph *GL);

/// 拓扑排序
/// 分析：将入度为0的点入栈，时间复杂度O(n)
/// 之后while循环，每个顶点入栈，出栈，入度-1，
/// 共执行e次
/// 时间复杂度为 O(n+e)
Status aov_top_logical_sort(LinkGraph GL);

#endif /* AOV_h */
