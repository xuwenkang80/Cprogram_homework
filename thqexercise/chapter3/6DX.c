//DX版本为简化版

#include <stdio.h>

int main() {
    // 赋初值
    char c1 = 'C', c2 = 'h', c3 = 'i', c4 = 'n', c5 = 'a';
    
    // 密码转换
    c1 += 4;
    c2 += 4;
    c3 += 4;
    c4 += 4;
    c5 += 4;
    
    // 使用putchar输出
    printf("使用putchar输出：");
    putchar(c1);
    putchar(c2);
    putchar(c3);
    putchar(c4);
    putchar(c5);
    printf("\n");
    
    // 使用printf输出
    printf("使用printf输出：%c%c%c%c%c\n", c1, c2, c3, c4, c5);
    
    return 0;
}
