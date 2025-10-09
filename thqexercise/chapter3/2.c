/*
2.存款利息的计算。有1000元，想存5年，可按以下5种办法存:
(1)一次存5年期。
(2)先存2年期，到期后将本息再存3年期。
(3)先存3年期，到期后将本息再存2年期。
(4)存1年期，到期后将本息再存1年期，连续存5次。
(5)存活期存款。活期利息每一季度结算一次。
2017年的银行存款利息如下:
1年期定期存款利息为1.5%;
2年期定期存款利息为2.1%;
3年期定期存款利息为2.75%;
5年期定期存款利息为3%；
活期存款利息为0.35%(活期存款每一季度结算一次利息）。
如果r为年利率，为存款年数，则计算本息和的公式如下：
1年期本息和：P=1000*(1+r);
n年期本息和:P=1000*(1+n*r);
存n次1年期的本息和：P=1000*(1十r)^n;
活期存款本息和：P=1000*(1+r/4)
说明：1000*(1+r/4）是一个季度的本息和。
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	//定义变量
	double principal = 1000.0;
	double interest_1y = 0.015;
	double interest_2y = 0.021;
	double interest_3y = 0.0275;
	double interest_5y = 0.03;
	double interest_current = 0.0035;

	double result1,
	       result2,
	       result3,
	       result4,
	       result5;

	//计算过程
	result1 = principal * (1 + 5 * interest_5y);

	double after2y = principal * (1 + 2 * interest_2y);
	result2 = after2y * (1 + 3 * interest_3y);

        double after_3y = principal * (1 + 3 * interest_3y);
	result3 = after_3y * (1 + 2 * interest_2y);

	result4 = principal * pow(1 + interest_1y, 5);

	result5 = principal * pow(1 + interest_current/4, 20);

	//结果输出
 	printf("存款利息计算结果（本金：1000元，存款期限：5年）\n");
	printf("==============================================\n");
	printf("(1) 一次存5年期：%.2f元\n", result1);
	printf("(2) 先存2年再存3年：%.2f元\n", result2);
 	printf("(3) 先存3年再存2年：%.2f元\n", result3);
	printf("(4) 连续存5次1年期：%.2f元\n", result4);
	printf("(5) 存活期存款：%.2f元\n", result5);
	printf("\n");
    
        // 找出最佳存款方式
        double max_result = result1;
        int best_method = 1;
      	
	if (result2 > max_result) {
        	max_result = result2;
        	best_method = 2;
    	}
        if (result3 > max_result) {
        	max_result = result3;
        	best_method = 3;
    	}
        if (result4 > max_result) {
        	max_result = result4;
        	best_method = 4;
        }
    	if (result5 > max_result) {
        	max_result = result5;
        	best_method = 5;
        }
    
    	printf("最佳存款方式是：方法(%d)，最终本息和为：%.2f元\n", best_method, max_result);
    
    	return 0;

}
