#include <stdio.h>
#include <math.h>

double x,y;

int main(){
	scanf("%lf",&x);
	if(x<1){y = x;}
	else if(x >= 1 && x < 10){y = 2*x-1;}
	else if(x>=10){y = 3*x-11;}
	else{printf("undifined");}
	printf("%.2f\n",y);
	return 0;
}
