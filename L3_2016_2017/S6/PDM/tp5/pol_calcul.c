#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/* PILE */
void init(int64_t *);
void empiler(int64_t );
int64_t depiler();

/* Operations */
int64_t addition(int64_t, int64_t);
int64_t substract(int64_t, int64_t);
int64_t times(int64_t, int64_t);
int64_t divide(int64_t, int64_t);

#define MAX_PILE 2
#define MAX_INPUT 100

int main() 
{
	int i;
	int64_t a,b,r;
	char c;

	int64_t* pile = NULL;	
	pile = malloc(sizeof(int64_t) * MAX_PILE);

	char* input = NULL;
	input = malloc(sizeof(char) * MAX_INPUT);
	
	init(pile); // init :  %r15 = &pile

	printf("Saisir votre opération en notation polonaise\n");
	scanf("%[^\n]s",input);
	
	for (i=0; i<MAX_INPUT; i++)
	{
		c = *(input+i);
		
		/* END */
		if ( c == '\0')
		{
			printf("Resultat = %ld\n",depiler());
			break;
		}

		/* OP */
		switch ( c)
		{
			case ' ' : continue;
			case '+' :
			{				
				b = depiler();
				a = depiler();
				r =  addition (a,b);
				empiler(r);
				break;
			}
			case '-':
			{
				b = depiler();
				a = depiler();
				r = substract(a,b);
				empiler(r);
				break;
			}
			case '*':
			{
				b = depiler();
				a = depiler();
				r = times(a,b);
				empiler(r);
				break;
			}
			case '/':
			{
				b = depiler();
				a = depiler();
				r = divide(a,b);
				empiler(r);
				break;
			}
			default:
			{
				r = c- 48;
				empiler(r);
			}
		}
	}

	//free(pile);
	free(input);

	return 0;
}
