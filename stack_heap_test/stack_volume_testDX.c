#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit rlim;
    
    printf("=== Raspberry Pi 栈信息查询 ===\n");
    
    // 获取栈大小限制
    if (getrlimit(RLIMIT_STACK, &rlim) == 0) {
        printf("当前栈大小限制: %.2f MB\n", rlim.rlim_cur / (1024.0 * 1024.0));
        printf("最大栈大小限制: %.2f MB\n", rlim.rlim_max / (1024.0 * 1024.0));
        
        // Raspberry Pi 通常有 8MB 栈
        printf("\n预计实际栈大小: 8MB (Linux默认)\n");
    } else {
        printf("无法获取栈限制信息\n");
    }
    
    // 获取内存页面大小
    long page_size = sysconf(_SC_PAGESIZE);
    printf("系统页面大小: %ld KB\n", page_size / 1024);
    
    // 显示栈增长方向
    int a, b;
    if (&a > &b) {
        printf("栈增长方向: 向低地址增长 ✓\n");
    } else {
        printf("栈增长方向: 向高地址增长\n");
    }
    
    printf("栈变量地址示例:\n");
    printf("变量a地址: %p\n", &a);
    printf("变量b地址: %p\n", &b);
    
    return 0;
}
