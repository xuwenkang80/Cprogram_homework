#include <stdio.h>

int year[120];

int main()
{
	for(int i=0;i<10000;i++)
	{
		if(((i+1900)%4==0&&(i+1900)%100!=0)||((i+1900)%100==0&&(i+1900)%400==0)){printf("%d是一个闰年！\n",i+1900);}
	}
	return 0;
}
