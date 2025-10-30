#include <stdio.h>
#include <math.h>

int IsNarcissusNumber(int n){
if(n<100 || n>999){return 0;}
if(pow(n%10,3) + pow(n/100,3) + pow(n/10%10,3) == n){return 1;}
}

int main(){
	for(int i=100;i<=999;i++)
	{
		if(IsNarcissusNumber(i) == 1){printf("%d\n",i);}
	}
	return 0;
}
