#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double x,y;

int main(){
	scanf("%lf%lf",&x,&y);
	x = abs(x);
	y = abs(y);
	double distance_square = pow(x-2,2)+pow(y-2,2);
	if(distance_square <= 1){printf("10\n");}
	else{printf("0\n");}
	return 0;
}
