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

void makeAMGraph(MGraph *G);
void DFSSeqTravese(MGraph G);

void makeLinkGraph(GraphLink *G);
void DFSLinkGraph(GraphLink G);

#endif /* DFS_h */
