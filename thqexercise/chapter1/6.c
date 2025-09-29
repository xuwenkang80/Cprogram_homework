#include <stdio.h>

int first,second,third;


int main(){
        scanf("请输入第一个值=%d\n",&first);
        scanf("请输入第二个值=%d\n",&second);
        scanf("请输入第三个值=%d\n",&third);

        int maxium = max(first,second,third);
        printf("最大的数是%d\n",maxium);

}

int max(int a,int b,int c){
	if(a>b)
	{
		if(a>c){return a;}
		else{return c;}
	}
	else
	{
		if(b>c){return b;}
		else{return c;}
	}
}
