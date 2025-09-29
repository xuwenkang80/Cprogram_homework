#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

// 每次递归消耗的内存大小（字节）
#define STACK_PER_CALL 2048  // 增加到2KB，减少递归深度

int max_depth = 0;
int crash_depth = 0;

// 栈溢出处理函数
void stack_overflow_handler(int sig) {
    printf("\n💥 栈溢出崩溃！信号: %d\n", sig);
    printf("崩溃时的递归深度: %d\n", crash_depth);
    
    int stack_used_kb = (crash_depth * STACK_PER_CALL) / 1024;
    float stack_used_mb = stack_used_kb / 1024.0;
    
    printf("估算栈使用量: %d KB ≈ %.2f MB\n", stack_used_kb, stack_used_mb);
    printf("实际栈大小: 8.00 MB (从系统查询得知)\n");
    printf("栈空间使用率: %.1f%%\n", (stack_used_mb / 8.0) * 100);
    
    exit(0);
}

void recursive_function(int level) {
    // 在栈上分配内存（模拟函数调用的开销）
    char local_variables[STACK_PER_CALL];
    
    // 防止编译器优化掉未使用的变量
    memset(local_variables, level % 256, sizeof(local_variables));
    
    max_depth = level;
    crash_depth = level;
    
    if (level % 50 == 0) {  // 每50层打印一次
        int stack_used_kb = (level * STACK_PER_CALL) / 1024;
        float stack_used_mb = stack_used_kb / 1024.0;
        float percentage = (stack_used_mb / 8.0) * 100;
        
        printf("深度: %5d, 栈使用: %4d KB (%5.1f%%) \n", 
               level, stack_used_kb, percentage);
    }
    
    recursive_function(level + 1);
}

int main() {
    printf("🔍 Raspberry Pi 栈大小压力测试\n");
    printf("================================\n");
    printf("系统栈大小: 8.00 MB (从查询得知)\n");
    printf("每次递归消耗: %d 字节\n", STACK_PER_CALL);
    printf("预期崩溃点: 约 4000 次递归 (8MB / 2KB)\n");
    printf("================================\n\n");
    
    printf("注意：程序会故意导致栈溢出来测试极限\n");
    printf("按回车键开始测试...");
    getchar();  // 等待用户确认
    
    // 设置栈溢出处理
    signal(SIGSEGV, stack_overflow_handler);
    signal(SIGABRT, stack_overflow_handler);
    
    printf("开始测试...\n");
    printf("深度      栈使用量    使用率\n");
    printf("-----    ---------    ------\n");
    
    recursive_function(1);
    
    // 如果程序意外返回（不应该发生）
    printf("\n测试意外结束，最大深度: %d\n", max_depth);
    return 0;
}
