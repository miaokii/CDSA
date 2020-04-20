//
//  main.c
//  字符串匹配RK算法
//
//  Created by miaokii on 2020/4/20.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "string.h"

#define MAXSIZE 40
#define d 26

typedef int     Status;
typedef int     ElemType;
typedef char    String[MAXSIZE + 1];

/// 计算d的m-1次方
int getMaxValue(int m) {
    int h = 1;
    for (int i = 0; i < m-1; i++) {
        h = (h * d);
    }
    return h;
}

///
int isMathc(char *S, int i, char *P, int m) {
    int is, ip;
    for (is = i, ip = 0; is != m && ip != m; is++, ip++) {
        if (S[is] != P[ip]) {
            return 0;
        }
        return 1;
    }
    return 0;
}

/// Rabin & Karp
int RK(char *S, char *P) {
    // m子串长度
    int m = (int)strlen(P);
    // n主串长度
    int n = (int)strlen(S);
    
    // 模式串的hash值
    unsigned int A = 0;
    // 主串分解后的子串hash值
    unsigned int ST = 0;
    
    // 求子串的hash值，一起求出主串0-m的hash值
    for (int i = 0; i != m; i++) {
        A = (d * A + (P[i] - 'a'));
        ST = (d * A + (S[i] - 'a'));
    }
    
    int hValue = getMaxValue(m);
    for (int i = 0; i <= n-m; i++) {
        // 避免hash冲突，比较原串，二次确认
        if (A == ST) {
            if (isMathc(S, i, P, m)) {
                return i+1;
            }
        } else {
            ST = (ST - hValue * (S[i] - 'a')) * d + (S[i+m] - 'a');
        }
    }
    
    return 0;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
