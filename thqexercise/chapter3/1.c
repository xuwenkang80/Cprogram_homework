/*
	假如我国国民生产总值的年增长率为7%，计算10年后我国国民生产总值
	与现在相比增长多少百分比。计算公式为
		p = (1+r)^n
*/

#include <stdio.h>
#include <math.h>

double p;
double r = 0.07;
int n = 10;


int main(){
	p = pow(1+r,n);
	double growth_percentage = (p - 1) * 100;
	printf("10年后我国国民生产总值与现在相比增长%.2f%%\n",growth_percentage);
	return 0;
}
