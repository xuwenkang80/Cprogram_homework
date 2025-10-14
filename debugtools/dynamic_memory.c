#include <stdio.h>
#include <stdlib.h>

int main() {
    int size;
    printf("请输入数组大小: ");
    scanf("%d", &size);
    
    // 动态分配数组
    int *array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        printf("内存分配失败!\n");
        return 1;
    }
    
    // 初始化并打印数组
    printf("数组内容: ");
    for (int i = 0; i < size; i++) {
        array[i] = i * 2;  // 存入偶数值
        printf("%d ", array[i]);
    }
    printf("\n");
    
    // 释放内存
    free(array);
    printf("内存已释放\n");
    
    return 0;
}
