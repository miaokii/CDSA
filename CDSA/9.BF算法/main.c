//
//  main.c
//  BF
//
//  Created by miaokii on 2020/4/20.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "string.h"

#define MAXSIZE 40

typedef int Status;
typedef int ElemType;
typedef char String[MAXSIZE + 1];

Status StrAssign(String T, char * chars) {
    int i;
    if (strlen(chars) < MAXSIZE) {
        
    }
}

void StrPrint(String T) {
    int i;
    for (i = 1; i <= T[0]; i++) {
        printf("%c", T[i]);
    }
    printf("\n");
}

int Index_BF(String S, String T, int pos) {
    // 主串索引
    int i = pos;
    // 模式串索引
    int j = 1;
    
    while (i < S[0] && j <= T[0]) {
        if (S[i] == T[j]) {
            i++;
            j++;
        } else {
            // 回朔i
            i = i - j + 1 + 1
            // 回朔j
            j = 1
        }
    }
    
    // 每一个字符都匹配完了
    if (j > T[0]) {
        return i - T[0];
    }
    // 没找到
    return -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
