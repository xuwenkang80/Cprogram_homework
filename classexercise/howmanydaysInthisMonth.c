#include <stdio.h>
#include <stdbool.h>

// 函数声明
bool is_leap_year(int year);
int get_days_in_month(int year, int month);

int main() {
    int year, month;
    
    printf("=== 月份天数查询程序 ===\n");
    
    // 输入年份和月份
    printf("请输入年份: ");
    scanf("%d", &year);
    
    printf("请输入月份 (1-12): ");
    scanf("%d", &month);
    
    // 验证输入的有效性
    if (year < 1) {
        printf("错误：年份必须大于0\n");
        return 1;
    }
    
    if (month < 1 || month > 12) {
        printf("错误：月份必须在1-12之间\n");
        return 1;
    }
    
    // 获取天数并显示结果
    int days = get_days_in_month(year, month);
    
    printf("\n=== 查询结果 ===\n");
    printf("年份: %d\n", year);
    printf("月份: %d\n", month);
    
    // 显示月份名称
    char *month_names[] = {
        "一月", "二月", "三月", "四月", "五月", "六月",
        "七月", "八月", "九月", "十月", "十一月", "十二月"
    };
    printf("月份名称: %s\n", month_names[month - 1]);
    
    // 显示闰年信息
    if (month == 2) {
        if (is_leap_year(year)) {
            printf("闰年: 是\n");
        } else {
            printf("闰年: 否\n");
        }
    }
    
    printf("天数: %d天\n", days);
    
    return 0;
}

// 判断是否为闰年
bool is_leap_year(int year) {
    // 闰年规则：
    // 1. 能被4整除但不能被100整除的是闰年
    // 2. 能被400整除的也是闰年
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 获取指定年份月份的天数
int get_days_in_month(int year, int month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;  // 大月
        case 4: case 6: case 9: case 11:
            return 30;  // 小月
        case 2:
            return is_leap_year(year) ? 29 : 28;  // 二月
        default:
            return -1;  // 无效月份
    }
}
