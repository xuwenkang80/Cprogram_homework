#include <stdio.h>
#include <stdlib.h>

// 全局变量记录递归深度
int depth = 0;

// 递归函数，每次调用消耗一定栈空间（局部变量）
void test_stack_size() {
    // 在栈上分配一些内存（模拟局部变量）
    char buffer[1024]; // 每次调用消耗1KB栈空间
    depth++;
    
    // 打印当前栈使用情况
    if (depth % 100 == 0) {
        printf("递归深度: %d, 栈使用量: %d KB\n", depth, depth);
    }
    
    // 继续递归（直到栈溢出）
    test_stack_size();
}

int main() {
    printf("开始测试栈大小...\n");
    printf("每次递归消耗1KB栈空间\n\n");
    
    // 设置信号处理，优雅地处理栈溢出
    signal(SIGSEGV, [](int sig) {
        printf("\n=== 栈溢出发生！ ===\n");
        printf("最大递归深度: %d\n", depth);
        printf("估算栈大小: %d KB ≈ %.2f MB\n", depth, depth / 1024.0);
        exit(0);
    });
    
    test_stack_size();
    return 0;
}
