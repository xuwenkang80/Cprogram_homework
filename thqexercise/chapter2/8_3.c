//8_3程序：输入10个数，然后输出其中最大的一个数

#include <stdio.h>

int main() {
    int num, max;
    int i;

    printf("请输入10个整数：\n");
    
    // 输入第一个数并设为最大值
    printf("第1个数: ");
    scanf("%d", &max);
    
    // 输入剩余9个数并比较
    for (i = 2; i <= 10; i++) {
        printf("第%d个数: ", i);
        scanf("%d", &num);
        
        if (num > max) {
            max = num;
        }
    }

    printf("最大值是：%d\n", max);

    return 0;
}
