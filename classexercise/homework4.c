#include <stdio.h>

int main() {
    int n;
    
    // 获取输入
    scanf("%d", &n);
    
    // 输出平行四边形
    for (int i = 0; i < n; i++) {
        // 打印空格
        for (int j = 0; j < n - i - 1; j++) {
            printf(" ");
        }
        // 打印星号
        for (int j = 0; j < n; j++) {
            printf("*");
        }
        // 换行
        printf("\n");
    }
    
    return 0;
}
