#include <stdio.h>
#include <inttypes.h>

int64_t addition(int64_t, int64_t);
int64_t substract(int64_t, int64_t);
int64_t times(int64_t, int64_t);
int64_t divide(int64_t, int64_t);

int main() 
{
	int64_t a,b;
	char op;
	
	printf("Saisire votre opération sous la forme : a op b\n");
	scanf("%ld %c %ld",&a,&op,&b);
	
	printf("a= %ld, op= %c, b= %ld\n",a,op,b); 

	switch (op)
	{
		case '+' : printf("%ld\n", addition(a,b));break;
		case '-' : printf("%ld\n", substract(a,b));break;
		case '*' : printf("%ld\n", times(a,b));break;
		case '/' : printf("%ld\n", divide(a,b));break;
		default: printf("erreur op\n");
	}
	
	return 0;
}
