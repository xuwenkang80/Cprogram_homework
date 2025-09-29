#include <stdio.h>

// 函数：返回三个数中的最大值
int findMax(int x, int y, int z) {
	return (x>y)?((x>z)?x:z):((y>z)?y:z);

/*    if (x >= y && x >= z) {
        return x;
    } else if (y >= x && y >= z) {
        return y;
    } else {
        return z;
    }
*/
}

int main() {
    int a, b, c;
    
    printf("请输入三个整数: ");
    scanf("%d %d %d", &a, &b, &c);
    
    int max = findMax(a, b, c);
    printf("三个数中的最大值是: %d\n", max);
    
    return 0;
}
