#include <stdio.h>

unsigned long long factorial(int n){
	if(n == 0 ||n == 1){return 1;}
	else{return factorial(n-1)*n;}
}

int main(){
	unsigned long long sum;
	for(int i = 1;i <= 20;i++)
	{
		sum += factorial(i);
	}
	printf("%llu\n",sum);
	return 0;
}
