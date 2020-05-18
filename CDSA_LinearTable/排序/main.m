//
//  main.m
//  排序
//
//  Created by miaokii on 2020/5/18.
//  Copyright © 2020 ly. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SqList.h"
#import "stdlib.h"
#import "bubble.h"
#import "selection_sort.h"


int main(int argc, const char * argv[]) {
    SqList L;
    ElemType eles[] = {3, 1, 9, 4, 2, 8, 6, 5, 11, 20, 12};
    int count = sizeof(eles)/sizeof(int);
    for (int i = 1; i <= count; i++) {
        L.elem[i] = eles[i-1];
    }
    L.length = count;
    printf("待排序数组：");
    print_sqlist(L);
    
//    bubble_sort_simple(&L);
    bubble_sort_bubble_optimalize(&L);
    printf("冒泡排序：");
    
//    select_sort_simple(&L);
//    printf("选择排序：");
    
    
    
    print_sqlist(L);
    
    return 0;
}
