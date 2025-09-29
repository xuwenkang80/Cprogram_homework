#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


// 函数声明
int isPrimeOptimized(int n);
void sieveOfEratosthenes(int n);
void generateFirstNPrimes(int n);

// 优化的素数判断函数
int isPrimeOptimized(int n) {
    // 处理小数字
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    
    // 检查形如 6k±1 的因子
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

// 埃拉托斯特尼筛法
void sieveOfEratosthenes(int n) {
    if (n < 2) {
        printf("没有素数\n");
        return;
    }
    
    // 创建标记数组，初始都标记为素数（1表示素数，0表示非素数）
    int *isPrime = (int*)malloc((n + 1) * sizeof(int));
    
    if (isPrime == NULL) {
        printf("内存分配失败\n");
        return;
    }
    
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

// 生成前N个素数
void generateFirstNPrimes(int n) {
    if (n <= 0) {
        printf("请输入正整数\n");
        return;
    }
    
    printf("前 %d 个素数：\n", n);
    int count = 0;
    int num = 2;
    
    while (count < n) {
        if (isPrimeOptimized(num)) {
            printf("%d ", num);
            count++;
            if (count % 10 == 0) printf("\n");
        }
        num++;
    }
    printf("\n");
}

int main() {
    int choice, n;
    clock_t start, end;
    double cpu_time_used;
    
    printf("素数计算程序\n");
    printf("1. 判断单个数字是否为素数\n");
    printf("2. 输出范围内的素数\n");
    printf("3. 使用筛法生成素数\n");
    printf("4. 生成前N个素数\n");
    printf("请选择功能：");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            printf("请输入一个整数：");
            scanf("%d", &n);
            start = clock();
            if (isPrimeOptimized(n)) {
                printf("%d 是素数\n", n);
            } else {
                printf("%d 不是素数\n", n);
            }
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("计算时间：%f 秒\n", cpu_time_used);
            break;
            
        case 2:
            printf("请输入上限：");
            scanf("%d", &n);
            if (n < 2) {
                printf("没有素数\n");
                break;
            }
            start = clock();
            printf("2 到 %d 之间的素数：\n", n);
            int count = 0;
            for (int i = 2; i <= n; i++) {
                if (isPrimeOptimized(i)) {
                    printf("%d ", i);
                    count++;
                    if (count % 10 == 0) printf("\n");
                }
            }
            end = clock();
            printf("\n总共 %d 个素数\n", count);
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("计算时间：%f 秒\n", cpu_time_used);
            break;
            
        case 3:
            printf("请输入上限：");
            scanf("%d", &n);
            start = clock();
            sieveOfEratosthenes(n);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("计算时间：%f 秒\n", cpu_time_used);
            break;
            
        case 4:
            printf("请输入要生成的素数个数：");
            scanf("%d", &n);
            start = clock();
            generateFirstNPrimes(n);
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("计算时间：%f 秒\n", cpu_time_used);
            break;
            
        default:
            printf("无效选择！\n");
    }
    
    return 0;
}
