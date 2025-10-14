#include <stdio.h>
#include <stdlib.h>

// 埃拉托斯特尼筛法
void sieveOfEratosthenes(int n) {
    // 创建标记数组，初始都标记为素数（1表示素数，0表示非素数）
    int *isPrime = (int*)malloc((n + 1) * sizeof(int));
    
    // 初始化数组，0和1不是素数
    for (int i = 0; i <= n; i++) {
        isPrime[i] = 1;
    }
    isPrime[0] = isPrime[1] = 0;
    
    // 筛法过程
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            // 标记i的所有倍数为非素数
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = 0;
            }
        }
    }
    
    // 输出结果
    printf("1 到 %d 之间的素数有：\n", n);
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            printf("%d ", i);
            count++;
            if (count % 10 == 0) printf("\n");
        }
    }
    printf("\n总共找到 %d 个素数\n", count);
    
    free(isPrime);
}

int main() {
    int n;
    printf("请输入上限：");
    scanf("%d", &n);
    
    sieveOfEratosthenes(n);
    return 0;
}
