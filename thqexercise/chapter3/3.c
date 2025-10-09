/*
购房从银行贷了一笔款d，准备每月还款额为p，月利率为r，计算多少月能还清。设
d为300000元，p为6000元，r为1%。对求得的月份取小数点后一位，对第2位按四舍五
人处理。
*/


#include <stdio.h>
#include <math.h>

int main() {
    double d = 300000.0;  // 贷款总额
    double p = 6000.0;    // 每月还款额
    double r = 0.01;      // 月利率
    
    // 使用等额本息还款法的还款期限计算公式：
    // n = -log(1 - d*r/p) / log(1 + r)
    
    double n = -log(1 - d * r / p) / log(1 + r);
    
    // 对结果进行四舍五入处理（保留一位小数，第二位四舍五入）
    n = round(n * 10) / 10.0;
    
    printf("贷款信息：\n");
    printf("贷款总额：%.2f元\n", d);
    printf("每月还款额：%.2f元\n", p);
    printf("月利率：%.1f%%\n", r * 100);
    printf("\n");
    printf("还款期限计算结果：%.1f个月\n", n);
    
    // 转换为年月的形式显示
    int years = (int)n / 12;
    int months = (int)n % 12;
    double decimal_months = n - (int)n;
    
    printf("相当于：%d年%d个月", years, months);
    if (decimal_months > 0) {
        printf("零%.1f个月", decimal_months);
    }
    printf("\n");
    
    return 0;
}
