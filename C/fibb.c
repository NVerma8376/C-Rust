#include <stdio.h>

int main(void){
	int num;
	scanf("%d", &num);
	int a = 0;
	int b = 1;
	int c;

	for(int i=1; i <= num; i++){
		printf("%d \n", a);
		c = a+b;
		a = b;
		b = c;
	}


	return 0;
}
