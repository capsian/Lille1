#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/* PILE */
void init();
void empiler(int64_t );
int64_t depiler();

int main() 
{
	init();

	int i;

	empiler(1);
	printf("1 = %d |\n",depiler());
	empiler(2);empiler(3);
	printf("2 = %d | 3 = %d\n",depiler(),depiler());
	empiler(4);empiler(5);empiler(6);
	printf("4 = %d | 5 = %d | 6 = %d\n",depiler(),depiler(),depiler());
	empiler(1);empiler(2);empiler(3);empiler(4);
	printf("1 = %d | 2 = %d | 3 = %d | 4 = %d \n",depiler(),depiler(),depiler(),depiler());

	printf("\n");

	for (i=0;i<4;i++)
	{
		printf("empiler %d |",i);
		empiler(i);
	}
	printf("\n");

	for (i=0;i<4;i++)
	{
		printf("%ld | ",depiler());
	}
	printf("\n");


	return 0;
}
