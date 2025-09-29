#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <execinfo.h>  // 用于获取调用栈

#define STACK_PER_CALL 2048

int max_depth = 0;
int crash_depth = 0;

void print_stack_trace(void) {
    void *array[10];
    size_t size;
    
    // 获取调用栈
    size = backtrace(array, 10);
    
    printf("\n调用栈跟踪（崩溃时的函数调用序列）:\n");
    backtrace_symbols_fd(array, size, STDOUT_FILENO);
}

void stack_overflow_handler(int sig) {
    printf("\n💥 栈溢出崩溃！信号: %d (Segmentation fault)\n", sig);
    printf("崩溃时的递归深度: %d\n", crash_depth);
    
    int stack_used_kb = (crash_depth * STACK_PER_CALL) / 1024;
    float stack_used_mb = stack_used_kb / 1024.0;
    
    printf("估算栈使用量: %d KB ≈ %.2f MB\n", stack_used_kb, stack_used_mb);
    printf("系统栈大小: 8.00 MB\n");
    printf("栈空间使用率: %.1f%%\n", (stack_used_mb / 8.0) * 100);
    printf("保护机制: 操作系统在栈底部设置了保护页面，提前检测溢出\n");
    
    // 打印调用栈跟踪（可选）
    // print_stack_trace();
    
    exit(0);
}

void recursive_function(int level) {
    char local_variables[STACK_PER_CALL];
    memset(local_variables, level % 256, sizeof(local_variables));
    
    max_depth = level;
    crash_depth = level;
    
    if (level % 50 == 0) {
        int stack_used_kb = (level * STACK_PER_CALL) / 1024;
        float stack_used_mb = stack_used_kb / 1024.0;
        float percentage = (stack_used_mb / 8.0) * 100;
        
        printf("深度: %5d, 栈使用: %4d KB (%5.1f%%) \n", 
               level, stack_used_kb, percentage);
        
        // 刷新输出缓冲区，确保及时显示
        fflush(stdout);
    }
    
    recursive_function(level + 1);
}

int main() {
    printf("🔍 Raspberry Pi 栈大小压力测试 - 详细分析版\n");
    printf("==========================================\n");
    printf("系统栈大小: 8.00 MB\n");
    printf("每次递归消耗: %d 字节\n", STACK_PER_CALL);
    printf("预期崩溃点: 3900-4100 次递归之间\n");
    printf("==========================================\n\n");
    
    printf("测试目的:\n");
    printf("1. 验证栈的实际大小限制\n");
    printf("2. 观察栈溢出保护机制\n");
    printf("3. 理解栈的内存布局\n\n");
    
    printf("按回车键开始测试...");
    getchar();
    
    // 设置信号处理
    signal(SIGSEGV, stack_overflow_handler);
    
    printf("开始测试...\n");
    printf("深度      栈使用量    使用率\n");
    printf("-----    ---------    ------\n");
    
    recursive_function(1);
    
    printf("\n测试意外结束，最大深度: %d\n", max_depth);
    return 0;
}
