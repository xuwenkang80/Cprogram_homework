#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char num[10];

int main(){
	scanf("%s", num);
	printf("%d\r\n",strlen(num));
	strrev(num);
	puts(num);
	return 0;
}
