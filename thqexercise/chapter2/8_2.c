#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;    // 系数
    double discriminant; // 判别式
    double x1, x2;     // 根
    double realPart, imagPart; // 复根的实部和虚部

    // 输入二次方程的系数
    printf("请输入一元二次方程的系数 (a, b, c): ");
    scanf("%lf %lf %lf", &a, &b, &c);

    // 检查a是否为0（确保是二次方程）
    if (a == 0) {
        printf("错误：这不是一元二次方程（a不能为0）\n");
        return 1;
    }

    // 计算判别式
    discriminant = b * b - 4 * a * c;

    printf("方程: %.2fx² + %.2fx + %.2f = 0\n", a, b, c);
    printf("判别式: %.2f\n", discriminant);

    // 根据判别式的值分类讨论
    if (discriminant > 0) {
        // 两个不相等的实根
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        x2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("两个不相等的实根:\n");
        printf("x1 = %.2f\n", x1);
        printf("x2 = %.2f\n", x2);
    }
    else if (discriminant == 0) {
        // 两个相等的实根（重根）
        x1 = -b / (2 * a);
        printf("两个相等的实根（重根）:\n");
        printf("x1 = x2 = %.2f\n", x1);
    }
    else {
        // 两个共轭复根
        realPart = -b / (2 * a);
        imagPart = sqrt(-discriminant) / (2 * a);
        printf("两个共轭复根:\n");
        printf("x1 = %.2f + %.2fi\n", realPart, imagPart);
        printf("x2 = %.2f - %.2fi\n", realPart, imagPart);
    }

    return 0;
}
