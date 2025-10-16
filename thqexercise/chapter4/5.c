#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int a;

int main()
{
    printf("输入一个小于1000的整数：");
	scanf("%d",&a);
	
	
	while(a < 0 || a > 1000)
	{
		printf("输入一个小于1000的整数：");
		scanf("%d",&a);
	}
	
	a =  (int)sqrt(a);
	
	printf("%d\n",a);
	
    return 0;
}
