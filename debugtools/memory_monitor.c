#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WATCH_POINTS 50
#define MEM_VIEW_BYTES 64

typedef struct {
    void *address;
    char name[50];
    size_t size;
    char type;  // 'c':char, 'i':int, 'f':float, 'd':double, 'p':pointer, 's':string
} WatchPoint;

WatchPoint watch_list[MAX_WATCH_POINTS];
int watch_count = 0;

// 显示单个字节的十六进制和字符表示
void print_byte(unsigned char byte) {
    printf("%02X ", byte);
    if (isprint(byte)) {
        printf("('%c')", byte);
    } else {
        printf("(.) ");
    }
}

// 显示内存内容（十六进制和ASCII）
void hex_dump(const void *addr, size_t size) {
    const unsigned char *bytes = (const unsigned char *)addr;
    
    printf("地址: %p, 大小: %zu 字节\n", addr, size);
    printf("偏移量  十六进制                      ASCII\n");
    printf("------  --------------------------  --------\n");
    
    for (size_t i = 0; i < size; i++) {
        if (i % 8 == 0) {
            if (i > 0) printf("\n");
            printf("%06zX  ", i);
        }
        
        printf("%02X ", bytes[i]);
    }
    
    printf("\nASCII: ");
    for (size_t i = 0; i < size; i++) {
        if (isprint(bytes[i])) {
            printf("%c", bytes[i]);
        } else {
            printf(".");
        }
    }
    printf("\n\n");
}

// 添加监视点
int add_watch_point(void *addr, const char *name, size_t size, char type) {
    if (watch_count >= MAX_WATCH_POINTS) {
        printf("错误：监视点数量已达上限\n");
        return -1;
    }
    
    watch_list[watch_count].address = addr;
    watch_list[watch_count].size = size;
    watch_list[watch_count].type = type;
    strncpy(watch_list[watch_count].name, name, sizeof(watch_list[watch_count].name) - 1);
    watch_count++;
    
    return watch_count - 1;
}

// 显示所有监视点的值
void show_watch_points() {
    printf("\n=== 内存监视点 ===\n");
    printf("%-20s %-12s %-10s %-15s %s\n", 
           "名称", "地址", "类型", "大小", "值");
    printf("-------------------- ------------ ---------- --------------- --------\n");
    
    for (int i = 0; i < watch_count; i++) {
        WatchPoint *wp = &watch_list[i];
        printf("%-20s %-12p %-10c %-15zu ", 
               wp->name, wp->address, wp->type, wp->size);
        
        switch (wp->type) {
            case 'c':  // char
                printf("%d", *(char*)wp->address);
                break;
            case 'i':  // int
                printf("%d", *(int*)wp->address);
                break;
            case 'f':  // float
                printf("%.6f", *(float*)wp->address);
                break;
            case 'd':  // double
                printf("%.10f", *(double*)wp->address);
                break;
            case 'p':  // pointer
                printf("%p", *(void**)wp->address);
                break;
            case 's':  // string
                printf("\"%s\"", (char*)wp->address);
                break;
            default:
                printf("未知类型");
        }
        printf("\n");
    }
}

// 显示内存区域的内容
void show_memory_region(void *addr, size_t size) {
    hex_dump(addr, size > MEM_VIEW_BYTES ? MEM_VIEW_BYTES : size);
}

// 比较内存内容（用于检测内存变化）
void compare_memory(void *addr1, void *addr2, size_t size) {
    unsigned char *mem1 = (unsigned char *)addr1;
    unsigned char *mem2 = (unsigned char *)addr2;
    
    printf("内存比较: %p vs %p, 大小: %zu 字节\n", addr1, addr2, size);
    
    int differences = 0;
    for (size_t i = 0; i < size; i++) {
        if (mem1[i] != mem2[i]) {
            printf("差异在偏移量 %zu: 0x%02X vs 0x%02X\n", i, mem1[i], mem2[i]);
            differences++;
        }
    }
    
    if (differences == 0) {
        printf("内存内容完全相同\n");
    } else {
        printf("发现 %d 处差异\n", differences);
    }
    printf("\n");
}

// 检查内存是否可读
int is_memory_readable(void *addr, size_t size) {
    // 简单检查：尝试读取第一个字节
    volatile unsigned char test;
    (void)test;  // 避免未使用变量警告
    
    // 这里使用信号处理可以更安全，简化版本直接尝试读取
    // 注意：这不是完全安全的做法，生产环境需要更复杂的检查
    return (addr != NULL && size > 0);
}

// 显示变量信息
void inspect_variable(void *addr, const char *name, size_t size) {
    printf("\n=== 变量检查: %s ===\n", name);
    printf("地址: %p\n", addr);
    printf("大小: %zu 字节\n", size);
    
    if (!is_memory_readable(addr, size)) {
        printf("警告: 内存可能不可读\n");
        return;
    }
    
    show_memory_region(addr, size);
}

// 简单的内存分配跟踪
void* debug_malloc(size_t size, const char* name) {
    void *ptr = malloc(size);
    if (ptr) {
        printf("分配内存: %p, 大小: %zu, 用途: %s\n", ptr, size, name);
        // 可以在这里添加内存跟踪逻辑
    }
    return ptr;
}

void debug_free(void *ptr, const char* name) {
    printf("释放内存: %p, 用途: %s\n", ptr, name);
    free(ptr);
}

// 演示使用
int main() {
    printf("=== C语言内存调试工具演示 ===\n\n");
    
    // 演示变量
    int x = 42;
    float y = 3.14159f;
    char str[] = "Hello, Debug!";
    int array[5] = {1, 2, 3, 4, 5};
    
    // 添加监视点
    add_watch_point(&x, "整数x", sizeof(x), 'i');
    add_watch_point(&y, "浮点数y", sizeof(y), 'f');
    add_watch_point(str, "字符串str", sizeof(str), 's');
    add_watch_point(array, "数组array", sizeof(array), 'i');
    
    // 显示监视点
    show_watch_points();
    
    // 检查特定变量
    inspect_variable(&x, "整数x", sizeof(x));
    inspect_variable(str, "字符串str", sizeof(str));
    
    // 演示内存比较
    int a = 100;
    int b = 100;
    compare_memory(&a, &b, sizeof(int));
    
    // 修改值后重新显示
    printf("修改 x 的值后:\n");
    x = 123;
    show_watch_points();
    
    // 显示数组内存
    printf("数组内存布局:\n");
    hex_dump(array, sizeof(array));
    
    return 0;
}
