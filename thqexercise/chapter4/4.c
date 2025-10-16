/*
有3个整数abc，从键盘输入，输出其中最大的数
*/


#include <stdio.h>
#include <stdlib.h>

int a,b,c; //定义abc

int main(){
	printf("请输入3个整数abc");
	scanf("%d%d%d",&a,&b,&c);

	if(a>=b && a>=c){
		printf("%d\n",a);
	}
	else if(b>=a && b>=c){
                printf("%d\n",b);
        }
	else if(c>=b && c>=a){
                printf("%d\n",c);
        }
	return 0;
}
