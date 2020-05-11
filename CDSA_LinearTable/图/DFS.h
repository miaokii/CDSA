//
//  DFS.h
//  图
//
//  Created by Miaokii on 2020/5/5.
//  Copyright © 2020 ly. All rights reserved.
//

#ifndef DFS_h
#define DFS_h

#include <stdio.h>
#include "SeqGroup.h"
#include "LinkGroup.h"

/* 深度优先遍历 */

/* 右手原则 */

/// 创建一个邻接矩阵
void makeAMGraph(MGraph *G);
/// 深度优先遍历邻接举证
void DFSSeqTravese(MGraph G);

/// 创建一个邻接表
void makeLinkGraph(LinkGraph *G);
/// 深度优先遍历邻接表
void DFSLinkGraph(LinkGraph G);

#endif /* DFS_h */
