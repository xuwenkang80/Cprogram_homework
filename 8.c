#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    double delta, x1, x2;
    
    // 输入系数
    printf("请输入一元二次方程的系数：\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("c = ");
    scanf("%lf", &c);
    
    // 判断是否为二次方程
    if (a == 0) {
        printf("错误：这不是一个二次方程（a不能为0）\n");
        return 1;
    }
    
    // 计算判别式
    delta = b * b - 4 * a * c;
    
    // 根据判别式的值判断根的情况
    if (delta > 0) {
        // 有两个不相等的实根
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);
        printf("方程有两个不相等的实根：\n");
        printf("x1 = %.2f\n", x1);
        printf("x2 = %.2f\n", x2);
    } 
    else if (delta == 0) {
        // 有两个相等的实根（重根）
        x1 = -b / (2 * a);
        printf("方程有两个相等的实根：\n");
        printf("x1 = x2 = %.2f\n", x1);
    } 
    else {
        // 无实根（有复数根）
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-delta) / (2 * a);
        printf("方程无实根，有复数根：\n");
        printf("x1 = %.2f + %.2fi\n", realPart, imaginaryPart);
        printf("x2 = %.2f - %.2fi\n", realPart, imaginaryPart);
    }
    
    return 0;
}
