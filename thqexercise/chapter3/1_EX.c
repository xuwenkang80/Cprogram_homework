/*
Extra:为何在printf中使用growth_percentage和&growth_percentage是一样的结果

为什么可能看起来"一样"？
内存布局巧合：地址值可能恰好与你要打印的数值在内存中的表示相似
小端序系统：在x86/x64系统中，地址的低位字节可能与你期望的浮点数值有部分重叠
编译器优化：不同的编译器可能产生不同的结果

永远不要混用！使用 &growth_percentage 是未定义行为，可能：

打印出随机值
导致程序崩溃
在某些平台上有看似"正确"的结果（但这只是巧合）
*/


#include <stdio.h>

int main() {
    double growth_percentage = 96.71;
    
    printf("正确用法（值）: %.2f\n", growth_percentage);
    printf("错误用法（地址）: %.2f\n", &growth_percentage);  // 未定义行为
    
    // 查看实际的内存地址
    printf("growth_percentage的内存地址: %p\n", &growth_percentage);
    printf("growth_percentage的实际值: %f\n", growth_percentage);
    
    return 0;
}
