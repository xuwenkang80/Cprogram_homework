#include <stdio.h>
#include <math.h>

int IsCompleteNumber(int n){
	printf("%d its factors are 1",n);
	int factor_sum = 1;
	for(int i=2;i<=n-1;i++)
	{
		if(n%i == 0){printf(",%d",i);}
		factor_sum += i;
	}
	if(factor_sum == n){printf("  %d is a Complete Number!",n);}
	printf("\n");
	return 0;
}


int main(){
	for(int i=1;i<=1000;i++){IsCompleteNumber(i);}
	return 0;
}

