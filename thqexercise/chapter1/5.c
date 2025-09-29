#include <stdio.h>

int spaces[] = {0,2,4,6};

int main(){
	for(int i=0;i<4;i++){
		for(int j=0;j<spaces[i];j++){
			printf(" ");
		}
		printf("*****\n");
	}
	return 0;
}
