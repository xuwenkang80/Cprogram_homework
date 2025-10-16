#include <stdio.h>

int main() {
    int c1, c2;  // 使用int以正确处理EOF
    
    printf("请输入两个字符: ");
    
    c1 = getchar();
    if(c1 == EOF) {
        printf("读取错误或文件结束\n");
        return 1;
    }
    
    c2 = getchar();
    if(c2 == EOF) {
        printf("读取错误或文件结束\n");
        return 1;
    }
    
    // 输出结果
    printf("\n--- 输出结果 ---\n");
    printf("putchar输出: ");
    putchar(c1);
    putchar(' ');
    putchar(c2);
    
    printf("\nprintf字符输出: %c %c", c1, c2);
    printf("\nASCII码值: %d %d", c1, c2);
    printf("\n十六进制: 0x%02X 0x%02X\n", c1, c2);
    
    // 清除缓冲区
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);
    
    return 0;
}
