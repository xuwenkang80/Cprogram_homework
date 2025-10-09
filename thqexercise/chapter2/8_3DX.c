//DX版本增加了非法输入检测


#include <stdio.h>
#include <string.h>

int main() {
    int numbers[10];
    int max;
    int i;
    char input[100];

    printf("请输入10个整数：\n");
    
    for (i = 0; i < 10; i++) {
        while (1) {
            printf("第%d个数: ", i + 1);
            
            // 读取整行输入
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("读取输入失败！\n");
                continue;
            }
            
            // 尝试从字符串中解析整数
            if (sscanf(input, "%d", &numbers[i]) == 1) {
                break; // 成功读取，退出循环
            } else {
                printf("输入错误！请输入一个整数: ");
            }
        }
    }

    max = numbers[0];
    for (i = 1; i < 10; i++) {
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    printf("\n输入的10个数是：");
    for (i = 0; i < 10; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n最大值是：%d\n", max);

    return 0;
}
