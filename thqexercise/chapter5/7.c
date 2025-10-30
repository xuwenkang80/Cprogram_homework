#include <stdio.h>

int main(){
	long double sum = 0.0L;
	for(int i = 1;i<=100;i++){sum+=i;}
	for(int i = 1;i<=50;i++){sum+=i*i;}
	for(int i = 1;i<=100;i++){sum+=1.0L/i;}
	printf("%.15Lf\n",sum);
	return 0;

}
