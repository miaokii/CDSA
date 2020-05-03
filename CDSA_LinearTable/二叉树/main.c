//
//  main.c
//  二叉树
//
//  Created by miaokii on 2020/4/24.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "math.h"

/**
 树：n个节点构成的集合
 度：节点拥有子树的个数
 叶子（终端节点）：度为0的节点、
 兄弟节点：同属于一个双亲节点
 节点高度：到叶子结点最长路径的长度
 深度：节点到根节点的路径边数
 
 二叉树：有且只有一个根节点
        每个节点最多有两个子树
 满二叉树：
 完全二叉树：
 */



#define OK 1
#define ERROR 0
#define TRUE 1
#define FLASE 0

#define MAXSIZE 100
#define MAX_TREE_SIZE 100

typedef int Status;
typedef int CElemType;
typedef CElemType SqBiTree[MAX_TREE_SIZE];
CElemType Nil = 0;

typedef struct {
    // 节点层号
    int level;
    // 序号（满二叉树规则）
    int order;
} Position;

/**
 1、初始化
 */
Status InitBiTree(SqBiTree T) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        T[i] = Nil;
    }
    return OK;
}

/**
 2、插入二叉树
 */
Status CreateBiTree(SqBiTree T) {
    int i = 0;
    while (i < 10) {
        T[i] = i + 1;
        
        // 如果父节点不存在，就不能插入
        if (i != 0 && T[(i+1)/2-1] == Nil && T[i] != Nil) {
            printf("出现无父节点%d\n：", T[i]);
            return ERROR;
        }
        
        while (i < MAX_TREE_SIZE) {
            T[i] = Nil;
            i++;
        }
    }
    return OK;
}

/**
 3、清空二叉树
    清空二叉树和创建二叉树是一样的
 */
#define ClearBiTree InitBiTree

/**
 4、二叉树判空
 */
Status BiTreeEmpty(SqBiTree T) {
    if (T[0] == Nil) {
        return true;
    }
    return FALSE;
}

/**
 5、获取二叉树的深度
 */
int BiTreeDepth(SqBiTree T) {
    // 找到最后一个节点
    int j = -1
    int i;
    for (i = MAX_TREE_SIZE; i >= 0; i--) {
        if (T[i] == Nil) break;
        
        do {
            j++;
        } while ((pow(2, j) <= i));
    }
    return j;
}

/**
 6、处于e位置上的节点
 */
CElemType value(SqBiTree T, Position e) {
    // level -> 层
    // order -> 序号
    
    printf("%d\n", (int)pow(2, e.level - 1));
    printf("%d\n", e.order);
    
    return T[(int)pow(2, e.level-1) + e.order-2];
}

/**
 7、对某个节点进行赋值
 */
Status Assign(SqBiTree T, Position e, CElemType value) {
    int i = (int)pow(2, e.level - 1) + e.order - 2
    if (value != Nil && T[(i+1)/2-1] == nil)
        return ERROR;
    T[i] = value;
    return OK;
}

/**
 8、获得节点的左/右孩子、双亲节点
 */

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
