#include <stdio.h>

int main() {
    double profit, bonus = 0.0;
    
    scanf("%lf", &profit);
    
    double limits[] = {0, 10, 20, 40, 60, 100, 1000000};  // 利润区间上限
    double rates[] = {0.10, 0.075, 0.05, 0.03, 0.015, 0.01};  // 提成率
    
    double p = profit / 10000.0;
    
    for (int i = 1; i < 6; i++) {
        if (p <= limits[i]) {
            bonus += (p - limits[i-1]) * rates[i-1];
            break;
        } else {
            bonus += (limits[i] - limits[i-1]) * rates[i-1];
        }
    }
    
    if (p > 100) {
        bonus += (p - 100) * 0.01;
    }
    
    bonus *= 10000;
    
    printf("bonus=%.6f\n", bonus);
    return 0;
}
