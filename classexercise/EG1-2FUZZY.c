//输入一个三位数，使其输出为逆序
//此程序由于scanf中变量名前缺少%因此无法正常运行

#include <stdio.h>

int main() {
    int num, reversed;
    
    printf("请输入一个三位整数：");
    scanf("%d", num);
    
    if (num < 100 || num > 999) {
        printf("请输入一个有效的三位整数！\n");
        return 1;
    }
    
    reversed = (num % 10) * 100;    // 获取个位数并放到百位
    reversed += (num / 10 % 10) * 10; // 获取十位数并放到十位
    reversed += num / 100;           // 获取百位数并放到个位
    
    printf("原数字：%d\n", num);
    printf("逆序数字：%d\n", reversed);
    
    return 0;
}
