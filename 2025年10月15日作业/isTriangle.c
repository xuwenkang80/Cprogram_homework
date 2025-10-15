#include <stdio.h>

#include <stdlib.h>

int a, b, c; //定义三角形三边长a,b,c

int main() {
    scanf("%d%d%d", & a, & b, & c);

    if (a + b > c && a + c > b && b + c > a && a > 0 && b > 0 && c > 0) {
        {
            if (a == b && a == c) {
                printf("等边三角形");
            } else if (a == b || a == c || b == c) {
                printf("等腰三角形");
            } else {
                printf("一般三角形");
            }
        }

    } else {
        printf("不是三角形");
    }
}
