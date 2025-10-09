/*
6.请编程序将“China”译成密码，密码规律是：用原来的字母后面第4个字母代替原来
的字母。例如,字母“A”后面第4个字母是“E”,用“E”代替“A”。因此,“China”应译为
“Glmre”。请编一程序，用赋初值的方法使cl，c2，c3，c4，c5这5个变量的值分别为′C’，
'h',"i',n','a',经过运算,使cl,c2,c3,c4,c5分别变为'G',1',m',r',e'。分别用putchar
函数和printf函数输出这5个字符。
*/

#include <stdio.h>

int main() {
    // 方法1：使用赋初值的方法
    char c1 = 'C', c2 = 'h', c3 = 'i', c4 = 'n', c5 = 'a';
    
    printf("原始字符：\n");
    printf("c1 = %c, c2 = %c, c3 = %c, c4 = %c, c5 = %c\n", 
           c1, c2, c3, c4, c5);
    
    // 进行密码转换（每个字母后移4位）
    c1 = c1 + 4;
    c2 = c2 + 4;
    c3 = c3 + 4;
    c4 = c4 + 4;
    c5 = c5 + 4;
    
    printf("\n转换后的密码：\n");
    
    // 使用putchar函数输出
    printf("使用putchar函数输出：");
    putchar(c1);
    putchar(c2);
    putchar(c3);
    putchar(c4);
    putchar(c5);
    printf("\n");
    
    // 使用printf函数输出
    printf("使用printf函数输出：%c%c%c%c%c\n", c1, c2, c3, c4, c5);
    
    printf("\n详细分析：\n");
    printf("C -> %c (ASCII: %d -> %d)\n", c1, 'C', c1);
    printf("h -> %c (ASCII: %d -> %d)\n", c2, 'h', c2);
    printf("i -> %c (ASCII: %d -> %d)\n", c3, 'i', c3);
    printf("n -> %c (ASCII: %d -> %d)\n", c4, 'n', c4);
    printf("a -> %c (ASCII: %d -> %d)\n", c5, 'a', c5);
    
    return 0;
}
