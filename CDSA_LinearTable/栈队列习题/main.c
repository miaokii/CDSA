//
//  main.c
//  栈队列习题
//
//  Created by miaokii on 2020/4/21.
//  Copyright © 2020 ly. All rights reserved.
//

#include <stdio.h>
#include "stdlib.h"
#include "string.h"

/** 1、进制转换
 */

/** 2、杨辉三角
 */
int ** generate(int numRows, int * returnSize) {
    *returnSize = numRows;
    int **res = (int **)malloc(sizeof(int) * numRows);
    
    for (int i = 0; i < numRows; i++) {
        res[i] = (int *)malloc(sizeof(sizeof(int) * i + 1));
        res[i][0] = 1;
        res[i][i] = 1;
        
        for (int j = 1; j < i; j++) {
            res[i][j] = res[i-1][j-1] + res[i-1][j];
        }
    }
    return res;
}

/** 3、爬楼梯递归法
 递归方程：f(n) = f(n-1) + f(n-2)
 结束条件：f(1) = 1 f(2) = 2
 */
int ClimbStaries_1(int n) {
    if (n < 1) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    else {
        return ClimbStaries_1(n-1) + ClimbStaries_1(n-2);
    }
}

/** 4、爬楼梯 动态规划法
 */
int ClimbStaries_2(int n) {
    if (n == 1) return 1;
    int* sum = (int *)malloc(sizeof(int) * n + 1);
    sum[0] = 0;
    sum[1] = 1;
    sum[2] = 2;
    
    for (int i = 3; i <= n; i++) {
        sum[i] = sum[i-1] + sum[i-2];
    }
    return sum[n];
}

/** 5、每日温度
    根据每日气温列表，从新生成一个列表，对应位置的输入是你需要在等待多久温度才会升高到超过该日的天数。如果之后温度都不会升高，在该位置用0代替
    eg：tem = [73, 74, 75, 71, 69, 72, 76, 73]
        ->    [1, 1, 1, 4, 2, 1, 1, 0, 0]
 */
/**
    1⃣️暴力法
 */
int * dailyTem_1(int * T, int size, int * returnSize) {
    
    int * res = (int *)malloc(sizeof(int) * size);
    *returnSize = size;
    
    for (int i = 0; i < size - 1; i++) {
        // 如果和上一个元素相等，则该元素天数少1
        if (i > 0 && T[i] == T[i-1])
            res[i] = res[i-1] == 0 ? 0 : res[i-1] - 1;
        else {
            for (int j = i + 1; j < size; j++) {
                if (T[i] < T[j]) {
                    res[i] = j - 1;
                    break;
                }
                if (j == size - 1) {
                    res[i] = 0;
                }
            }
        }
    }
    return res;
}

/**
    2⃣️、后往前跳跃对比，前一个元素如果小于后一个元素，可以在后一个元素的值上+1
    减少遍历次数
    1、右到左遍历，最后一天默认等于0
    2、i [tSize - 2 ... 0]，从倒数第二天开始遍历，每次递减1
    3、j [i+1, TSzie]遍历，j += result[j]
        如果t[i] < t[j]，result = j - i
        如果reuslt[j]==0，没有值了
 */
int * dailyTem_2(int * T, int size, int * returnSize) {
    int * result = (int *)malloc(sizeof(int) * size);
    *returnSize = size;
    
    // 最后一个元素
    result[size - 1] = 0;
    
    for (int i = size - 2; i >= 0; i--) {
        for (int j = i + 1; j < size; j+= result[j]) {
            if (T[i] < T[j]) {
                result[i] = j - i;
                break;
            } else if (result[j] == 0) {
                result[i] = 0;
                break;
            }
        }
    }
    return result;
}

/**
    3⃣️、栈思路
 */
int * dailyTem_3(int * T, int size, int * returnSize) {
    int * result = (int *)malloc(sizeof(int) * size);
    int * stack_index = (int *)malloc(sizeof(int) * size);
    *returnSize = size;
    int top = 0;
    int tIndex;
    
    for (int i = 0; i < size; i++) {
        result[i] = 0;
    }
    
    for (int i = 0; i < size; i++) {
        while (top > 0 && T[i] > T[stack_index[top - 1]]) {
            // 栈顶
            tIndex = stack_index[top - 1];
            result[tIndex] = i - tIndex;
            top--;
        }
        stack_index[top] = i;
        top ++;
    }
    
    return result;
}

/**
    6、字符串编码
    s = "3[a]2[bc]" -> "aaabcbc"
    s = "3[a2[c]]"  -> "accaccacc"
    s = "2[abc]3[cd]ef" -> "abcabccdcdef"
 
 12[a]为例
 思路：1、遍历字符串s
        2、当前字符不为"]"，入栈stack     stack = 12[a
        3、当前字符为"]"，则：
            1、确定复制字符串：stack = "12[a"   -> a （出栈，[之前）
            2、找到复制数量：继续出栈到为空或者  上限栈顶，下限数字
            3、转换数量为整形："12\0" -> 12;
            4、复制：a复制12份
            5、字符串+'\0'结尾
 */
char * decodeString(char* s) {
    int len = (int)strlen(s);
    int stackSize = 50;
    char * stack = (char *)malloc(stackSize * sizeof(char));
    int top = -1;
    
    // 遍历字符串
    for (int i = 0; i < len; i ++) {
        // 入栈
        if (s[i] != ']') {
            if (top == stackSize - 1) {
                stackSize += 50;
                stack = realloc(stack, stackSize * sizeof(char));
            }
            stack[++top] = s[i];
        } else {
            int tempSize = 10;
            char * temp = (char *)malloc(tempSize * sizeof(char));
            int topOfTemp = -1;
            // 弹出
            while (stack[top] != '[') {
                if (topOfTemp == tempSize - 1) {
                    tempSize += 10;
                    temp = realloc(temp, sizeof(char) * tempSize);
                }
                ++topOfTemp;
                temp[topOfTemp] = stack[top];
                top--;
            }
            
            char starOfInt[11];
            // 找下限
            int curTop = top;
            top--;
            // 循环次数
            while (top != -1 && stack[top] >= '0' && stack[top] <= '9') {
                top--;
            }
            // 上面这个循环结束，top要么在-1处，要么在循环次数的前一个字符，要加回来
            for (int j = top + 1; j < curTop; j++) {
                // 12
                starOfInt[j-(top+1)] = stack[j];
            }
            starOfInt[curTop-(top+1)] = '\0';
            
            // 将字符串数字转为数字 "12" -> 12
            int curNum = atoi(starOfInt);
            
            // 拷贝12份a到栈里面去
            // temp
            for (int k = 0; k < curNum; k++) {
                int kk = topOfTemp;
                while (kk != -1) {
                    
                    if (top == stackSize - 1) {
                        stackSize += 50;
                        stack = realloc(stack, stackSize * sizeof(char));
                    }
                    
                    ++top;
                    stack[top] = temp[kk];
                    kk--;
                }
            }
            free(temp);
            temp = NULL;
        }
    }
    // '\0'结尾
    char * ans = realloc(stack, (top + 1) * sizeof(char));
    ans[++top] = '\0';
    
    free(stack);
    return ans;
}


int main(int argc, const char * argv[]) {
    int sta = 5;
    printf("%d\n", ClimbStaries_1(sta));
    
    int c[] = {73, 74, 75, 71, 69, 72, 76, 73};
    int cCount = sizeof(c) / sizeof(int);
    
    int resCount;
    int *ts = dailyTem_3(c, cCount, &resCount);
    
    for (int i = 0; i < resCount; i++) {
        printf("%d ", ts[i]);
    }
    printf("\n");
    printf("%s", decodeString("2[ef4[acd]]"));
    printf("\n");
    
    return 0;
}
