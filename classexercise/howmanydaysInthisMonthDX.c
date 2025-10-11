//DX版本更加精简
#include <stdio.h>

int main() {
    int year, month, days;
    
    printf("请输入年份: ");
    scanf("%d", &year);
    printf("请输入月份 (1-12): ");
    scanf("%d", &month);
    
    // 判断闰年
    int is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    
    // 判断天数
    switch(month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            days = 31; break;
        case 4: case 6: case 9: case 11:
            days = 30; break;
        case 2:
            days = is_leap ? 29 : 28; break;
        default:
            printf("月份输入错误！\n");
            return 1;
    }
    
    printf("%d年%d月有%d天\n", year, month, days);
    return 0;
}
