//
//  main.c
//  去除重复字母
//
//  Created by Miaokii on 2020/4/20.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "stdlib.h"

char * removeDuplicateLetters(char *s) {
    if (s == NULL || strlen(s) == 0) return "";
    if (strlen(s) == 1) return s;
    
    // 记录字母出现的次数
    char record[26] = {0};
    // s长度
    int len = (int)strlen(s);
    // 记录最后的结果
    char * stack = (char *)malloc(sizeof(char) * len  * 2);
    memset(stack, 0, len * 2 * sizeof(char));
    // 栈为空
    int top = -1;
    // 1、统计字母串线的次数
    int i = 0;
    for (i = 0; i < len; i ++) {
        record[s[i] - 'a'] = 0;
    }
    
    // 2、遍历字符串s
    for (int i = 0; i < len; i++) {
        // 标记当前字母是否存在stack里面
        int isExist = 0;
        // 字符串已经在stack里面存储了
        for (int j = 0; j <= top; j ++) {
            if(s[i] == stack[j]){
                isExist = 1;
                break;
            }
        }
        
        if(isExist == 1) {
            record[s[i] - 'a']--;
        } else {
            // 栈不为空、栈顶元素大于当前元素、
            while (top > -1 && stack[top] > s[i] && record[stack[top] - 'a'] > 1) {
                // 跳出该元素，频次减一
                record[stack[top] - 'a']--;
                // 出栈
                top--;
            }
            top++;
            stack[top] = s[i];
        }
    }
    stack[++top] = '\0';
    return stack;
}

int main(int argc, const char * argv[]) {
    
    char * str = "bcabc";
    char * un = removeDuplicateLetters(str);
    printf("%s", un);
    printf("\n");
    
    return 0;
}
