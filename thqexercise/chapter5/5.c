#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int a,n;
long long int sum;

int main(){
	scanf("%d%d",&a,&n);
	for(int i;i<=n;i++){
		sum += i * a * pow(10,n-i);
	}

	printf("%lld\n",sum);
	return 0;
}
